# sshell : Simple Shell

## Summary

This program, `sshell`, is a barebones version of a unix based shell that
supports some input and output redirection as well as piping. As a command line
interpreter, it parses the command line and its options and executes it.

## Implementation

The implementation of this program follows these steps:

1. Parsing the command line into a usable format and determining useful info
for execution, as well as catching any invalid command lines and returning a
relevant message about the parsing error.
2. Catches and executes built-in commands that must be implemented by the shell
rather than an external program.
3. Creates the necessary child processes to handle all the execution that is
needed for the program(s) which may have redirection and/or piping.
4. Waiting for the child processes to execute and collects them. Doing some
book keeping and cleaning before looping back to the start to accept a new
command line input to execute.

Collecting child processes, printing all the return messages and resetting
all the variables to be used for the next input in the shell.

### Parsing Command Lines and Parsing Errors

At the beginning of its execution, the shell `sshell` creates an empty `Command`
struct which it will use to store the parsed and unparsed command line as well
as meta data which will all enable program execution down the line. It also
creates an array to store the exit statuses of the programs it will run, but
this will only be used after execution finishes. Once these are initialized,
the shell waits for an input to pass to the three layer parsing function
`parseCommandLine` which parses the command line from left to right.

At the highest level, `parseCommandLine` splits the command line by pipe, `|`,
into command segments where it checks for missing commands for piping. This
allows it to determine an order to the command segments to pipe and how many
there are. It will then pass this segment and information, one segment at a
time, to `parseRedirect` for further parsing.

At the next to last level, `parseRedirect` splits the command segment by input
redirect, `<`, and output redirect, `>`, into a program and a file name (if
there is a redirect in the first place). This allows it to determine if there
is a redirect at all, if there is a missing command for redirection (which
is technically also a missing command for piping), if the redirect is illegal,
and if there is a redirect, whether the input/output file is valid. Before it
does all of this though, it must first pass the program and the program's
sequence number to `parseProgram` to check that the number of arguments does
not go past the max. This is to fall in line with the requirement that parsing
errors are reported first from left to right.

At the last level, `parseProgram` splits the program into tokens while also
removing any whitespace. This lets it check the number of tokens as well place
the tokens into `command->arguments[i][j]` which can support any number of
programs and fits the function `execvp`.

Throughout these functions, when a parsing error is detected, they will return
an error code which is then used by `printError` to display a matching error
message.

### Built-in Commands

Once parsing is complete, the shell checks if the first program argument
matches any of the built-in commands, which it will then execute. These
commands are executed seperately because the funcitonality they provide
cannot really be done by child processes, such as `exit`. The remaining
built-in commands exist to provide `Directory Stack` functionality. The
directory stack is implemented as a linked list of nodes where each node
stores a path and a pointer to the next node. The commands `pushd` and `popd`
create and manipulate these nodes while `dirs` traverses the nodes to print
them out. The commands `chdir` and `pwd` are operate independently from them
but are still related in directory functionality. Overall they wrap around and
add to `chdir` and `getcwd`. For all built-in functions, the `retStatus` is
filled in manually before printing the completion message and then either
looping or exiting.

### Child Creation and Execution

To execute regular commands the shell creates children to execute programs for
it. Before doing so, it must first prepare the necessary data so that the child
processes can fully operate. It first opens files descriptors for any input and
output files with `open` and with the `pipe` funciton opens a number of pipes
equal to one less than the number of programs that will need to be piped. With
the file descriptors created the shell creates the child processes with `fork`,
makes sure to assign a number to each child, telling it what program it will
run and the shell also notes down their process ids for later use.

Once the children exist, they will have copies of the `Command` data, copies
of the open file descriptors, and a number telling it which program to run.
Based on its unique assigned number the child processes check and connect to
their respective files and pipes and close the unused file descriptors.
Then they begin their execution with a call to `execvp` with matching arguments
from the command arguments. An integer catches `execvp`'s return value in case
the program/command it will run does not exist.

As the children executes, the shell/parent closes the open file descriptors on
its end so that the children can run smoothly and then it calls `waitpid` for
each child. It then waits for the children, collects their exit statuses, and
finally processes and stores them into `retStatus` for further use.

### Collection and Continuing

After the child processes execute, the program calls the `result` function and
prints out the statuses it had received from waiting. It then loops back to the
beginning where populated variables are reset and execution begins anew,
where it waits for a new command line to execute.

### Sources

[Implementing multi pipes](https://stackoverflow.com/questions/8389033/implementation-of-multiple-pipes-in-c)<br />
[Video for multiple pipes](https://youtu.be/NkfIUo_Qq4c)<br />
[Video for Redirecting Std output](https://www.youtube.com/watch?v=5fnVr-zH-SE&ab_channel=CodeVault)<br />
[Redirect output to a file](https://stackoverflow.com/questions/2605130/redirecting-exec-output-to-a-buffer-or-file)<br />
[Creating a linked list to use as a stack](https://www.geeksforgeeks.org/implement-a-stack-using-singly-linked-list/)<br />

