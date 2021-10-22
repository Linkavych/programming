/*
 * This program will create a lock file and attempt to lock it a second time.
 * Purpose is to illustrate the correct lock file logic
 */
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <fcntl.h>
#include <unistd.h>

int main(int argc, char *argv[]) {

	int fd, newfd;

	//open the lock file
	fd = open(argv[1], O_CREAT | O_EXCL, 0644);

	if (fd < 0 && errno == EEXIST) {
		puts("File is already locked.");
		close(fd);
	}
	else if (fd < 0) {
		puts("Unknown error.");
	}
	else {
		puts("lock estalished");
		// additional processing would take
		// place in this section of code
		// since the file is locked
	}

	newfd = open(argv[1], O_CREAT | O_EXCL, 0644);

	if (newfd < 0 && errno == EEXIST) {
		puts("File is already locked.");
		close(fd);
	}
	else if (newfd < 0) {
		puts("Unknown error.");
	}
	else {
		puts("lock estalished");
		// additional processing would take
		// place in this section of code
		// since the file is locked
	}
	close(fd);
	unlink(argv[1]);

	exit(EXIT_SUCCESS);
}
