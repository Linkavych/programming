/*
 * Return the PID of the process
 */
#include "apue.h"

int main(void)
{
    printf("[+] Process ID: %ld\n", (long)getpid());

    exit(0);
}
