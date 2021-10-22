/*
 * This program uses record locks to write to one part of a file and
 * puts a read lock on another portion of a file.
 */
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <errno.h>

int main(void){

	int fd;
	struct flock lock;

	if ((fd = open("test.dat", O_RDWR)) < 0) {
		perror("open");
		exit(EXIT_FAILURE);
	}

	// set up a write lock on the last 100 bytes fo the file
	lock.l_type = F_WRLCK;
	lock.l_whence = SEEK_END;
	lock.l_start = 0;
	lock.l_len = 100;

	// set the lock
	if (!fcntl(fd, F_SETLK, &lock)) {
		puts("Write lock established");
	} else {
		fcntl(fd, F_GETLK, &lock);
		printf("write locked by PID %d\n", lock.l_pid);
	}

	// create the read lock on the file
	lock.l_type = F_RDLCK;
	lock.l_whence = SEEK_END;
	lock.l_start = 0;
	lock.l_len = 100;

	if (!fcntl(fd, F_SETLK, &lock)) {
		puts("read lock established");
	} else {
		fcntl(fd, F_GETLK, &lock);
		printf("read locked by PID %d\n", lock.l_pid);
	}

	getchar();
	exit(EXIT_SUCCESS);
}
