/*
 * get user and group ID information for the user
 */
#include "apue.h"

int main(void)
{
    printf("UID = %d\nGID = %d\n", getuid(), getgid());

    exit(0);
}
