/*
 * Printing out the struct properties of a file
 */
#include "apue.h"
#include <time.h>
#include <fcntl.h>
#include <sys/stat.h>

int main(int argc, char *argv[])
{
    int fd;
    struct stat buf;

    if (argc != 2)
        err_quit("Usage: ./a.out <filename>");

    if ((fd = open(argv[1], O_RDONLY)) < 0)
        err_sys("open error");

    if (fstat(fd, &buf) < 0)
        err_ret("fstat error");

    printf("Device ID: %lu\n", buf.st_dev);
    printf("Inode: %lu\n", buf.st_ino);
    printf("Mode: %04o\n", buf.st_mode);
    printf("Hard links: %lu\n", buf.st_nlink);
    printf("UID: %d\n", buf.st_uid);
    printf("GID: %d\n", buf.st_gid);
    printf("Size (bytes): %lu\n", buf.st_size);
    printf("Blocksize: %lu\n", buf.st_blksize);
    printf("Blocks: %lu\n", buf.st_blocks);
    printf("Access time: %s", ctime(&buf.st_atime));
    printf("Modify time: %s", ctime(&buf.st_mtime));
    printf("Change time: %s", ctime(&buf.st_ctime));

    close(fd);

    exit(0);
}


