SHELL IMPLEMENTATION

Description:
This program is a demo replicate build of a the tsch/bash shell.
The shell will be able to run in batch mode, where the shell reads a file which contains multiple lines of commands and execute each command.
The shell will support a few internal built-in commands, redirection, pipes and background processes.

Internal commands:
help() - Display a manual of the shell.
exit() - Exit the shell.
cd()   - Change the current directory to the directory passed as an argument.
pwd()  - Display the current working directory.

Program Execution
The command line is executed with execv
If the command(s) in the user input line is the command's full path then the program will execute otherwise a helper function will build the full path for the command.
The shell will obtain the full path of a process if it wasn't inputted 
The shell supports pipes, stdin, stdout, as well as processes to be ran in the background indicated by an amperstand as the last character.
The shell support [process] [redirection] [file] and [process] [pipe] [process]