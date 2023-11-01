# sshell : Simple Shell
## Summary
This program, `sshell`, is a barebones version of a unix based shell. As a command lines
intrepeter, it parses the command line and supports redirecting and piping 
## Implementation
The implementation of this program follows these steps:
1. Parsing the options given as command arguments. Create struct of commands
to use later in execution.
2. create built in commands that are better run in the shell rather than an
external program.
3. created a linked list in a struct in order to build a stack. This stack is
then used to remember previous directories for commands `pushd` and `popd`.
4. Handle output and input redirection.
5. Handle multiple pipeline commands. 

### Parsing options
At the beginning of its execution, `sshell` takes in a command line. We parse
this command line by first removing the trailing new line and then calls the 
function `parseCommandLine` delimiting the string by pipes "|". After seperating
the line by pipes, we call `parseRedirect` and also seperate by "<" and ">". We
count the number of seperations and assign them to the number of commands. The
entire `Command` struct then gets populated.
### Built in commands
Once parsing is completed, we check to see if the first command is meant to be
built in. Through if statements of strcmp, we create the desired output for each
command.  
#### pushd and popd 
To implement the built in commands of `pushd` and `popd` we had to first create
a linked list in a struct called `DirNode`. In `pushd` we create a new node and
then run the `getcwd` command. We store the path of the new node and put it on
our linked list stack. For `popd` to work we first made sure the stack wasn't 
empty and then used `chdir` to go back to the path on the stack. After that we
moved the node head to point at the next node on the stack.
### Output/Input redirection and pipeline Commands
Originally we had the redirection and pipeline as different functions happening
at seperate times. This would not work for multiple pipes and redirection.
Instead, we combined them by having the parent create all the processes, pipes,
and redirects. We created an array of integers that would be used to manage the
file descriptors. We did not explicitly make ordered pairs, but planned them
as if they were. The parent created child process ids based on the number of 
commands present. We then checked for input and output redirection and opened
them. Pipes and child processes then get connected and created. We check if
the first child connects to any input, otherwise just pipe the output fd. The
last child checks to connect to any output and otherwise pipes for input from
the previous process. All processes in between are piped with the input of the
previous command and the output for the next command.
### Sources
https://stackoverflow.com/questions/8389033/implementation-of-multiple-pipes-in-c
https://www.youtube.com/watch?v=5fnVr-zH-SE&ab_channel=CodeVault
https://youtu.be/NkfIUo_Qq4c
https://stackoverflow.com/questions/2605130/redirecting-exec-output-to-a-buffer-or-file
https://www.geeksforgeeks.org/implement-a-stack-using-singly-linked-list/

