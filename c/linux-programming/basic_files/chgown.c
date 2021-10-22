/*
 * Create a file and change its mode/owner
 */
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>
#include <unistd.h>

int main(void) {
	uid_t owner = 500;
	uid_t group = 100;
	int fd;

	//create a file
	if ((fd = open("some.file", O_CREAT, 0644)) < 0) {
		perror("open");
		exit(EXIT_FAILURE);
	}

	//ls the file
	system("ls -l some.file");

	if ((fchown(fd, owner, group)) < 0) {
		perror("fchown");
		exit(EXIT_FAILURE);
	}

	system("ls -l some.file");
	exit(EXIT_SUCCESS);
}
