/*
 * This program creates a file with a 'hole' in it
 */
#include "apue.h"
#include <fcntl.h>

char buf1[] = "abcdefghij";
char buf2[] = "ABCDEFGHIJ";

int main(void)
{
    int fd;

    if ((fd = creat("file.hole", FILE_MODE)) < 0)
        err_sys("creat error");

    if (write(fd, buf1, 10) != 10)
        err_sys("buf1 write error");
    // Offset is at 10 here
    if (lseek(fd, 16384, SEEK_SET) == -1)
        err_sys("lseek error");

    // offset at 16384
    if (write(fd, buf2, 10) != 10)
        err_sys("buf2 write error");
    // offset at 16394
    exit(0);
}
