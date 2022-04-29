/*
Submitted by:
Abhilasha Saini
2019UEE5091

Q2
Create 2 programs:
(a) a client program who sorts 10 numbers using any sort algorithm
and a sever program who forks a child process
(b) and then executes the client using execvp command.

*/

/*
Solution 2 (b) : executes the client using execvp command.
The created child process does not have to run the same program as the parent process does. The exec type system calls allow a process to run any program files, which include a binary executable or a shell script. On this page, we only discuss one such system call: execvp(). The execvp() system call requires two arguments:

The first argument is a character string that contains the name of a file to be executed.
The second argument is a pointer to an array of character strings. More precisely, its type is char **, which is exactly identical to the argv array used in the main program:
int  main(int argc, char **argv)
Note that this argument must be terminated by a zero.
When execvp() is executed, the program file given by the first argument will be loaded into the caller's address space and over-write the program there. Then, the second argument will be provided to the program and starts the execution. As a result, once the specified program file starts its execution, the original program in the caller's address space is gone and is replaced by the new program.

execvp() returns a negative value if the execution fails (e.g., the request file does not exist)
*/

#include <stdio.h>
#include <sys/types.h>

void parse(char *line, char **argv)
{
    while (*line != '\0')
    { /* if not the end of line ....... */
        while (*line == ' ' || *line == '\t' || *line == '\n')
            *line++ = '\0'; /* replace white spaces with 0    */
        *argv++ = line;     /* save the argument position     */
        while (*line != '\0' && *line != ' ' &&
               *line != '\t' && *line != '\n')
            line++; /* skip the argument until ...    */
    }
    *argv = '\0'; /* mark the end of argument list  */
}

void execute(char **argv)
{
    pid_t pid;
    int status;

    if ((pid = fork()) < 0)
    { /* fork a child process           */
        printf("*** ERROR: forking child process failed\n");
        exit(1);
    }
    else if (pid == 0)
    { /* for the child process:         */
        if (execvp(*argv, argv) < 0)
        { /* execute the command  */
            printf("*** ERROR: exec failed\n");
            exit(1);
        }
    }
    else
    {                                /* for the parent:      */
        while (wait(&status) != pid) /* wait for completion  */
            ;
    }
}

void main(void)
{
    char line[1024]; /* the input line                 */
    char *argv[64];  /* the command line argument      */

    while (1)
    {                        /* repeat until done ....         */
        printf("Shell -> "); /*   display a prompt             */
        gets(line);          /*   read in the command line     */
        printf("\n");
        parse(line, argv);                /*   parse the line               */
        if (strcmp(argv[0], "exit") == 0) /* is it an "exit"?     */
            exit(0);                      /*   exit if it is                */
        execute(argv);                    /* otherwise, execute the command */
    }
}