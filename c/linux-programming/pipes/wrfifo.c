/*
 * Writing to a known FIFO pipe
 */
#include <linux/limits.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <limits.h>
#include <fcntl.h>
#include <time.h>

int main(void) {

	int fd, len;
	char buf[PIPE_BUF];
	mode_t mode = 0666;
	time_t tp;

	// ID ourselves
	printf("I am %d\n", getpid());

	// Open FIFO pipe write only
	if ((fd = open("fifo1", O_WRONLY)) < 0){
		perror("open");
		exit(EXIT_FAILURE);
	}

	// Generate data to write
	while (1) {
		time(&tp);
		len = sprintf(buf, "wrfifo %d sends %s", getpid(), ctime(&tp));

		// use len +1 because sprtintf does not count the 
		// terminating null
		if ((write(fd, buf, len + 1)) < 0){
			perror("write");
			close(fd);
			exit(EXIT_FAILURE);
		}
		sleep(3);
	}
	close(fd);
	exit(EXIT_SUCCESS);
}
