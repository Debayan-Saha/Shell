ASSIGNMENT 3
SUBMITTED BY DEBAYAN SAHA (2019113002)

How To Run (Once in correct directory):
    Run the following commands in the shell:
        $ make
        $ ./desh

Files and their uses:
    Headers:
        1.`header.h` contains all the system header files to be included
    C files:
        1. `execvp.c` contains the functions for foreground process and backgroud process. 
        2. `echo.c` includes the echo function.
        3. `cd.c` contains the functions for changing directory.
        4. `main.c` is the main program.
        5. `exit.c` exits the shell.
        6. `history.c` includes history of previous commands.
        7. `ls.c` includes ls functions.
        8. `repeat.c` includes the repeat function.
        9. `pinfo.c` includes pinfo function.
        10. `pwd.c` includes pwd function.
        11. `commands.c` includes function which handles the different commands
        12. `pipe.c` include function which handles the pipe 
        13. `jobs.c` include function which prints a list of all currently running background processes spawned by the shell in alphabetical order of the command name

The Shell program runs on an infinite loop and takes input from stdin using `fgets()`, which is further tokenized into semicolon-separated commands, which are run in order. Each command is separated with respect to the pipes(if any) by the function `execpipe` in `pipe.c` and then it sends it to the function `handlecommand` in `commands.c` where each command is tokenized separating the commands, flags(if any) and the arguments(if any).  `If-else` is used in order to select from the executable commands like rm,mkdir etc and other self-defined commands pwd, ls, cd, echo, pinfo, repeat and history.

Signal Handling
1. `Ctrl + C` interrupts any currently running foreground job
2. `Ctrl + D` logs out of shell 

Assumptions made:
    1. /proc filesystem is accessible as is to any standard linux user.
    2. Number of semicolon separated commands is maximum 50, with 2000 char as max length for each.
    3. username, hostname and cwd are 1000 characters at max.
    4. User can enter any amount of number for arguments in certain functions 
    5. Number of processes is maximum 100
