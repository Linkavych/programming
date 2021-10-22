/*
 * Create a file and change its mode.
 */
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>

int main(void) {

	mode_t mode = 0755;
	int fd;

	//create a new file
	if ((fd = open("empty.file", O_CREAT, 0644)) < 0) {
		perror("open");
		exit(EXIT_FAILURE);
	}
	//ls the file
	system("ls -l empty.file");

	//change the file permissions
	if ((fchmod(fd, mode)) < 0) {
		perror("fchmod");
		exit(EXIT_FAILURE);
	}

	//ls the file again
	system("ls -l empty.file");
	exit(EXIT_SUCCESS);
}

