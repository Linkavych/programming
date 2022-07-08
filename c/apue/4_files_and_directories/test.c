/*
 * Write a program likee cp(1) that copies a file containing holes,
 * without writing the bytes 0 to the output file
 */
#include "apue.h"
#include <fcntl.h>
#include <stdbool.h>

bool is_all_zeros(char *, size_t);

int main(int argc, char *argv[])
{
    if (argc != 3)
        err_quit("Usage: ./a.out <filename> <filename>");

    int src_fd, dst_fd;
    struct stat buf;
    char *buffer;

    // open the files
    if ((src_fd = open(argv[1], O_RDONLY)) < 0)
        err_sys("open error");

    if ((dst_fd = open(argv[2], O_CREAT | O_TRUNC | O_RDWR, FILE_MODE)) < 0)
        err_sys("open error");

    if (fstat(src_fd, &buf) < 0)
        err_sys("fstat error");
    size_t bufsize = buf.st_blksize;

    // make a new buffer
    if ((buffer = malloc(sizeof(char) * bufsize)) == NULL)
        err_sys("malloc error");

    size_t nread;

    do {
        ssize_t m = 0;
        nread = 0;
        do {
            if ((m = read(src_fd, buffer + nread, bufsize - nread)) <0)
                err_sys("read error");
            nread += m;
        } while (nread < bufsize && m != 0);

        if (nread == bufsize && is_all_zeros(buffer, nread)) {
            if (lseek(dst_fd, nread, SEEK_CUR) < 0)
                err_sys("lseek error");
        } else {
            size_t nwritten = 0;
            while (nwritten < nread){
                if ((m = write(dst_fd, buffer + nwritten, nread - nwritten)) < 0)
                    err_sys("write error");
                nwritten += m;
            }
        }
    } while (nread > 0);

    close(src_fd);
    close(dst_fd);
    free(buffer);
}

bool is_all_zeros(char *buffer, size_t len)
{
    for (int i = 0; i < len; i++)
    {
        if (buffer[i] != '\0') {
            return false;
        }
    }
    return true;
}

        
