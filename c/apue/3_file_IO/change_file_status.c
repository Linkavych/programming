/*
 * Turn on one or more of the file status flags for a descriptor
 */
#include "apue.h"
#include <fcntl.h>

void set_fl(int fd, int flags)
{
    int val;

    if ((val = fcntl(fd, F_GETFL, 0)) < 0)
        err_sys("fcntl F_GETFL error");

    val |= flags; // turns on the flags we want
    // val &= ~flags; // turn off the flags we want

    if (fcntl(fd, F_SETFL, val) < 0)
        err_sys("fcntl F_SETFL error");
}
