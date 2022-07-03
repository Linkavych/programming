/*
 * tests whether stdin is capable of seeking
 */
#include "apue.h"

int main(void)
{
    if (lseek(STDIN_FILENO, 0, SEEK_CUR) == -1)
        printf("[!] Cannot seek\n");
    else
        printf("[+] Seek ok...\n");

    exit(0);
}
