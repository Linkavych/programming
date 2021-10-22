/*
 * For this execise we're going to build a C program that executes syscalls.
 * This program will use the open() syscall.
 */
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>

int main(void) {
	int fd;

	// opening a file with open() in mode 700; creating the file
	fd = open("test.txt", O_WRONLY | O_CREAT, S_IRWXU);
	if (fd <0){
		printf("Open failed...\n");
		return -1;
	} else {
		printf("Open succeeded!\n");
	}
	return 0;
}
