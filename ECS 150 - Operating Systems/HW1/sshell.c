#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <wait.h>

#define TOKEN_MAX 32
#define CMDLINE_MAX 512
#define PATH_MAX 4096
/* Maximum number of commands accepted for piping */
#define CMD_MAX 4
/* An extra space is needed to delimit the array of arguments for execvp() */
#define ARG_MAX 17
/* Error Codes */
#define ERR_MISSING_CMD 1
#define ERR_ARG_MAX 2
#define ERR_MISSING_IN 3
#define ERR_MISSING_OUT 4
#define ERR_OPEN_IN 5
#define ERR_OPEN_OUT 6
#define ERR_MISPLACED_IN 7
#define ERR_MISPLACED_OUT 8
#define ERR_CANT_CD 9
#define ERR_CMD_DNE 10
#define ERR_DIR_DNE 11

/* Structure for parsing the command line into an easy to use format */
struct Command {
        int count;
        char input[PATH_MAX]; // name of file
        char output[PATH_MAX];
        char line[CMDLINE_MAX];
        char* arguments[CMD_MAX][ARG_MAX];
};

/* Functions which reset/initialize variables */
void clearCommand(struct Command *command)
{
        command->count = -1;
        strcpy(command->input, "");
        strcpy(command->output, "");
        strcpy(command->line, "");
        for (int i = 0; i < CMD_MAX; i++){
                for (int j = 0; j < ARG_MAX; j++){
                        if (command->arguments[i][j] != NULL){
                                free(command->arguments[i][j]);
                        }
                        command->arguments[i][j] = NULL;
                }
        }
}

/* Empties array of return statuses */
void clearStatus(int statuses[])
{
        for (int i = 0; i < CMD_MAX; i++){
                statuses[i] = 0;
        }
}

/* Helper function checks if a string is empty or just spaces */
int isEmpty(char *string)
{
        char *line = strdup(string);
        char *result = strtok(line, " \t\n");
        if (result == NULL){
                free(line);
                return 1;
        } else {
                free(line);
                return 0;
        }
}

/* Checks for too many arguments, otherwise fills out command.arguments */
int parseProgram(struct Command *command, char *program, int cmdnum)
{
        char *workingMem = strdup(program);
        char *workingProgram = workingMem;
        char *workingArg = strtok(workingProgram, " \t");
        command->arguments[cmdnum][0] = strdup(workingArg);
        for (int i = 1; i < ARG_MAX; i++){
                workingArg = strtok(NULL, " \t");
                if (workingArg == NULL){
                        command->arguments[cmdnum][i] = NULL;
                        free(workingMem);
                        return 0;
                }
                command->arguments[cmdnum][i] = strdup(workingArg);
                if (i == 16 && workingArg){
                        free(workingMem);
                        return ERR_ARG_MAX;
                }
        }
        free(workingMem);
        return -3;
}

/* Checks for any redirect errors, otherwise parses for commands and in/out */
int parseRedirect(struct Command *command, char *line, int cmdnum)
{
        char *workingMem = strdup(line);
        char *workingLine = workingMem;
        char *workingCMD;
        char *workingRedir;
        /* Check for input/output redirection assuming no multiple redirects */
        char *input = strstr(workingLine, "<");
        char *output = strstr(workingLine, ">");
        /* Separate command from possible redirect */
        workingCMD = strsep(&workingLine, "<>");
        if (isEmpty(workingCMD)){
                free(workingMem);
                return ERR_MISSING_CMD;
        }
        /* Parse command and check for too many arguments */
        int argError = parseProgram(command, workingCMD, cmdnum);
        if (argError){
                free(workingMem);
                return argError;
        }
        /* At this point, the command is 'valid'.
           Only redirects need to be checked */
        /* If there are no redirects then it's done */
        if (workingLine == NULL || (!input && !output)){
                free(workingMem);
                return 0;
        }
        /* Commands with redirects. Check for errors and set in/out targets */
        workingRedir = strtok(workingLine, " \t<>");
        if (cmdnum == 0){ /* First Command, which could also be the last */
                if (output && command->count != 1){
                        free(workingMem);
                        return ERR_MISPLACED_OUT;
                }
                if (workingRedir == NULL){
                        free(workingMem);
                        if (input){
                                return ERR_MISSING_IN;
                        }
                        if (output){
                                return ERR_MISSING_OUT;
                        }
                }
                if (input){
                        strcpy(command->input, workingRedir);
                }
                if (output){
                        strcpy(command->output, workingRedir);
                }
        } else if (command->count == cmdnum+1){ /* Last Command */
                if (input){
                        free(workingMem);
                        return ERR_MISPLACED_IN;
                }
                if (isEmpty(workingRedir)){
                        free(workingMem);
                        return ERR_MISSING_OUT;
                }
                strcpy(command->output, workingRedir);
        } else { /* Middle Commands */
                free(workingMem);
                if (input){
                        return ERR_MISPLACED_IN;
                } else if (output){
                        return ERR_MISPLACED_OUT;
                } else {
                        return -2;
                }
        }
        /* Check target files */
        if (strcmp(command->input, "")){
                /* Checks if file exists and can be read */
                if (access(command->input, R_OK)){
                        free(workingMem);
                        return ERR_OPEN_IN;
                }
        }
        if (strcmp(command->output, "")){
                /* If file doesn't exist, it can be created */
                if (access(command->output, F_OK)){
                        free(workingMem);
                        return 0;
                }
                /* If it does exist, write permission is checked */
                if (access(command->output, W_OK)){
                        free(workingMem);
                        return ERR_OPEN_OUT;
                }
        }
        /* The command has been parsed and everything is good so far */
        free(workingMem);
        return 0;
}

/* The command line can be visualized as: command | command | command,
where there can be n = [1, CMD_MAX] commands with n-1 pipes in between.
If n = 1, then the command needs to be checked for input redirection, '<'
and output redirection, '>'. If n > 1, then only the first command needs
to be parsed for '<' and only the last needs to be parsed for '>'.
In any case, once the valid redirects are separated from the commands,
you are left with programs which only need to be checked for invalid
redirects and then separated into arrays of arguments. */
int parseCommandLine(struct Command *command)
{
        char *workingMem = strdup(command->line);
        char *workingLine = workingMem;
        char *workingCMD;
        int error;
        for (int i = 0; i < CMD_MAX; i++){
                /* Extracts the next command to parse */
                workingCMD = strsep(&workingLine, "|");
                /* Checks for missing command */
                if (isEmpty(workingCMD)){
                        free(workingMem);
                        return ERR_MISSING_CMD;
                }
                /* Occurs when last command is extracted */
                if (workingLine == NULL){
                        command->count = i+1;
                        error = parseRedirect(command, workingCMD, i);
                        free(workingMem);
                        return error;
                }
                error = parseRedirect(command, workingCMD, i);
                if (error){
                        free(workingMem);
                        return error;
                }
        }
        free(workingMem);
        return 0;
}

/* Error Messages */
void printError(int ERRCode)
{
        switch (ERRCode) {
        case ERR_MISSING_CMD:
                fprintf(stderr, "%s\n", "Error: missing command");
                break;
        case ERR_ARG_MAX:
                fprintf(stderr, "%s\n", "Error: too many process arguments");
                break;
        case ERR_MISSING_IN:
                fprintf(stderr, "%s\n", "Error: no input file");
                break;
        case ERR_MISSING_OUT:
                fprintf(stderr, "%s\n", "Error: no output file");
                break;
        case ERR_OPEN_IN:
                fprintf(stderr, "%s\n", "Error: cannot open input file");
                break;
        case ERR_OPEN_OUT:
                fprintf(stderr, "%s\n", "Error: cannot open output file");
                break;
        case ERR_MISPLACED_IN:
                fprintf(stderr, "%s\n", "Error: mislocated input redirection");
                break;
        case ERR_MISPLACED_OUT:
                fprintf(stderr, "%s\n", "Error: mislocated output redirection");
                break;
        case ERR_CANT_CD:
                fprintf(stderr, "%s\n", "Error: cannot cd into directory");
                break;
        case ERR_CMD_DNE:
                fprintf(stderr, "%s\n", "Error: command not found");
                break;
        case ERR_DIR_DNE:
                fprintf(stderr, "%s\n", "Error: no such directory");
                break;
        default:
                fprintf(stderr, "%s%d\n", "Error: invalid error code ", ERRCode);
        }
}

/* Completion Message */
void result(struct Command *command, int statuses[])
{
        fprintf(stderr, "+ completed '");
        fprintf(stderr, "%s", command->line);
        fprintf(stderr, "' ");
        for (int i = 0; i < command->count; i++){
                fprintf(stderr, "[%d]", statuses[i]);
        }
        fprintf(stderr, "\n");
}

/* Functionality for the directory stack, implemented as a linked list */
struct DirNode {
        char path[PATH_MAX];
        struct DirNode *next;
};

int cd(struct Command *command)
{
        char *dirPath = command->arguments[0][1];
        int error = chdir(dirPath);
        if (error){
                return 1;
        } else {
                return 0;
        }
}

int pwd()
{
        char buffer[PATH_MAX];
        char *result = getcwd(buffer, sizeof(buffer));
        printf("%s\n", buffer);
        if (result == NULL){
                return 1;
        } else {
                return 0;
        }
}

int main(void)
{
        struct Command command;
        struct DirNode *dirStack = NULL;
        int retStatus[CMD_MAX];
        /* Initialization to guarantee behavior */
        for (int i = 0; i < CMD_MAX; i++){
                retStatus[i] = 0;
                for (int j = 0; j < ARG_MAX; j++){
                        command.arguments[i][j] = NULL;
                }
        }

        while (1) {
                char *nl;
                int status;

                /* Initialize/Reset necessary variables */
                clearCommand(&command);
                clearStatus(retStatus);

                /* Print prompt */
                printf("sshell@ucd$ ");
                fflush(stdout);

                /* Get command line */
                fgets(command.line, CMDLINE_MAX, stdin);

                /* Print command line if stdin is not provided by terminal */
                if (!isatty(STDIN_FILENO)) {
                        printf("%s", command.line);
                        fflush(stdout);
                }

                /* Remove trailing newline from command line */
                nl = strchr(command.line, '\n');
                if (nl)
                        *nl = '\0';

                if (isEmpty(command.line)){
                        continue;
                }

                /* Parse command line, searching for errors */
                int parseError = parseCommandLine(&command);
                if (parseError){
                        printError(parseError);
                        continue;
                }

                /* Builtin single argument commands */
                // exit
                if (!strcmp(command.arguments[0][0], "exit")) {
                        fprintf(stderr, "Bye...\n");
                        retStatus[0] = 0;
                        result(&command, retStatus);
                        break;
                }
                // cd
                if (!strcmp(command.arguments[0][0], "cd")) {
                        retStatus[0] = cd(&command);
                        if (retStatus[0]){
                                printError(ERR_CANT_CD);
                        }
                        result(&command, retStatus);
                        continue;
                }
                // pwd
                if (!strcmp(command.arguments[0][0], "pwd")) {
                        retStatus[0] = pwd();
                        result(&command, retStatus);
                        continue;
                }
                // dirs
                if (!strcmp(command.arguments[0][0], "dirs")) {
                        retStatus[0] = pwd();
                        struct DirNode *trackDir = dirStack;
                        while (trackDir != NULL) {
                                printf("%s\n", trackDir->path);
                                trackDir = trackDir->next;
                        }
                        result(&command, retStatus);
                        continue;
                }
                // pushd
                if (!strcmp(command.arguments[0][0], "pushd")) {
                        struct DirNode newNode;
                        char buffer[PATH_MAX];
                        getcwd(buffer, sizeof(buffer));
                        retStatus[0] = cd(&command);
                        if (retStatus[0] == 0){
                                strcpy(newNode.path, buffer);
                                dirStack = &newNode;
                        } else {
                                printError(ERR_DIR_DNE);
                        }
                        result(&command, retStatus);
                        continue;
                }
                // popd
                if (!strcmp(command.arguments[0][0], "popd")) {
                        if (dirStack == NULL) {
                                fprintf(stderr, "Error: directory stack empty\n");
                                retStatus[0] = 1;
                        } else {
                                retStatus[0] = chdir(dirStack->path);
                                dirStack = dirStack->next;
                        }
                        result(&command, retStatus);
                        continue;
                }

                /* Prepares for regular command execution */
                int commandNum = -1; /* Command that a child should run */
                int inputfd = -1; /* File descriptors */
                int outputfd = -1;
                int pipefd[2 * command.count];

                /* Child process ids */
                pid_t pid[command.count];
                for (int i = 0; i < command.count; i++){
                        pid[i] = 0;
                }

                /* Prepares file descriptors */
                /* Opens input */
                if (strcmp(command.input, "")){
                        inputfd = open(command.input, O_RDONLY);
                }
                /* Opens output */
                if (strcmp(command.output, "")){
                        outputfd = open(command.output, O_WRONLY | O_CREAT, 0644);
                }
                /* Cretes pipes for child processes */
                if (command.count > 1){
                        for (int i = 0; i < command.count; i++){
                                pipe(&pipefd[0 + (2 * i)]);
                        }
                }

                /* Execution */
                /* Creates child processes */
                for (int i = 0; i < command.count; i++){
                        pid[i] = fork();
                        if (pid[i] == 0){
                                commandNum = i;
                                break;
                        }
                        commandNum = -1;
                }

                /* Block of code which only the child processes execute */
                /* Child processes connect to their fds and execute commands */
                if (commandNum >= 0){
                        if (commandNum == 0){
                                /* First child connects to input if any */
                                if (inputfd >= 0){
                                        dup2(inputfd, STDIN_FILENO);
                                        close(inputfd);
                                }
                                if (command.count > 1){
                                        dup2(pipefd[1], STDOUT_FILENO);
                                }
                        }
                        if (commandNum == command.count-1){
                                /* Last child connects to output if any */
                                if (outputfd >= 0){
                                        dup2(outputfd, STDOUT_FILENO);
                                        close(outputfd);
                                }
                                /* Close unused input file desciptor */
                                if (inputfd >= 0){
                                        close(inputfd);
                                }
                                if (command.count > 1){
                                        dup2(pipefd[(commandNum-1)*2], STDIN_FILENO);
                                }
                        } else{
                                int readfd = 2*(commandNum-1);
                                int writefd = (2*commandNum)+1;
                                /* Get input from prev command */
                                dup2(pipefd[readfd],STDIN_FILENO);
                                /* Give output for next command */
                                dup2(pipefd[writefd], STDOUT_FILENO);
                                /* Close unused input/ouput file descriptors */
                                if (inputfd >= 0){
                                        close(inputfd);
                                }
                                if (outputfd >= 0){
                                        close(outputfd);
                                }
                        }
                        /* Child closes unused piped file descriptors */
                        for (int commandNum = 0; commandNum < 2 * command.count;commandNum++){
                                close(pipefd[commandNum]);
                        }
                        /* Child executes command, exiting no matter what */
                        int execError = execvp(command.arguments[commandNum][0]
                                        , command.arguments[commandNum]);
                        if (execError){
                                printError(ERR_CMD_DNE);
                                exit(1);
                        } else {
                                exit(-5);
                        }
                }

                /* Parent closes file descriptors so that children can run */
                /* Parent closes input/output on its end */
                if (inputfd >= 0){
                        close(inputfd);
                }
                if (outputfd >= 0){
                        close(outputfd);
                }
                /* Parent closes all pipes on its end */
                for (int i = 0; i < 2 * command.count; i++){
                        close(pipefd[i]);
                }

                /* Prints command result before looping back to start */
                /* Parent function collects exit status of children */
                for (int i = 0; i < command.count;i++){
                        waitpid(pid[i], &status, 0);
                        if (WIFEXITED(status)){
                                retStatus[i] = WEXITSTATUS(status);
                        } else {
                                retStatus[i] = status;
                        }
                }

                result(&command, retStatus);
        }
        /* Frees any remaining allocated memory */
        clearCommand(&command);
        return EXIT_SUCCESS;
}
