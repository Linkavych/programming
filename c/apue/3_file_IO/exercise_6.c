/*
 * test and prov if you can replace data in an existing file opened
 * read-write with the append flag set.
 */
#include "apue.h"
#include <fcntl.h>

int main(void)
{
    int fd;
    char buf[BUFSIZ];
    int n;
    int offset;

    if ((fd = open("test.file", O_APPEND | O_CREAT | O_RDWR, FILE_MODE)) < 0)
        err_sys("open error");

    printf("Writing to our file...\n");
    
    if (write(fd, "first line\n\0", 12) != 12)
        err_sys("write error");

    //offset is 12
    offset = lseek(fd, 0, SEEK_CUR);
    printf("Offset: %d\n", offset);

    printf("Changing the offset with lseek()...\n");
    offset = lseek(fd, 0, SEEK_SET);
    printf("Offset 2: %d\n", offset);

    printf("Attempting to write to the file again...\n");
    if (write(fd, "second line\n\0", 13) != 13)
        err_sys("write error");
    printf("Checking offset...\n");
    offset = lseek(fd, 0, SEEK_CUR);
    printf("Offset 3: %d\n", offset);

    printf("Printing file contents...\n");

    // set lseek to start of file
    lseek(fd, 0, SEEK_SET);

    while ((n = read(fd, buf, BUFSIZ)) > 0)
        if (write(STDOUT_FILENO, buf, n) != n)
            err_sys("write error");
    if (n < 0)
        err_sys("read error");

    exit(0);
}
