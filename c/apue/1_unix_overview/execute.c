/*
 * Reading commands in from STDIN and execute them on the system
 */
#include "apue.h"
#include <sys/wait.h>

int main(void)
{
    char buf[MAXLINE];
    pid_t pid;
    int status;

    printf("%% "); // prommpt for input
    while (fgets(buf, MAXLINE, stdin) != NULL)
    {
        if (buf[strlen(buf) - 1] == '\n')
            buf[strlen(buf) - 1] = 0; // set terminating NUL byte

        if ((pid = fork()) < 0)
        {
            err_sys("fork error");
        } else if (pid == 0) {
            execlp(buf, buf, (char *)0);
            err_ret("[!] Could not execute: %s", buf);
            exit(127);
        }

        // parent
        if ((pid = waitpid(pid, &status, 0)) < 0)
            err_sys("waitpid error");
        printf("%% ");
    }
    exit(0);
}
