/*
 * implementation of dup2() without using fcntl
 */
#include "apue.h"
#include <memory.h>
#include <errno.h>
#include <fcntl.h>

int new_dup2( int fd, int fd2)
{
    int old[fd2];
    int filetmp = dup(fd2);

    memset(old, 0, sizeof(old));

    if (filetmp < -1)
    {
        printf("illegal fd\n");
        exit(1);
    }
    else
    {
        close(filetmp);
    }

    if (fd == fd2)
        return fd2;

    close(fd2);
    int ans = dup(fd);
    old[ans] = 1;

    while (ans != fd2)
    {
        ans = dup(fd);
        old[ans] = 1;
    }

    for (int i = 0; i < fd; i++)
    {
        if (old[i])
            close(i);
    }
    return ans;
}

int main(void)
{
    int fd;
    int fd2 = 3;
    const char *fname = "test.txt";
    const char *contents = "test the dup2()";

    if ((fd = open(fname, O_CREAT|O_RDWR)) < 0)
        err_sys("open error");

    int new = new_dup2(fd, fd2);

    if (write(new, contents, strlen(contents)) != strlen(contents))
        err_sys("write error");

    printf("Write success!");

    exit(0);
}
