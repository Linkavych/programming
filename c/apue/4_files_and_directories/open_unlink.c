/*
 * Open a file and then unlink it
 */
#include "apue.h"
#include <fcntl.h>

int main(void)
{
    if (open("tmp", O_RDWR) < 0)
        err_sys("open error");
    printf("File opened...\n");
    if (unlink("tmp") < 0)
        err_sys("unlink error");
    printf("Unlinked the file....\n");
    printf("Sleeping...\n");
    sleep(15);

    printf("Done!\n");
    exit(0);
}
