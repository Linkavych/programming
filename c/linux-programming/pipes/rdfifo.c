/*
 * Create a FIFO pipe and read from it
 */
#include <linux/limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>
#include <limits.h>
#include <unistd.h>

int main(void) {

	int fd;
	int len;
	char buf[PIPE_BUF];
	mode_t mode = 0666;

	if ((mkfifo("fifo1", mode)) < 0){
		perror("mkfifo");
		exit(EXIT_FAILURE);
	}

	// open the FIFO pipe read only
	if ((fd = open("fifo1", O_RDONLY)) < 0){
		perror("open");
		exit(EXIT_FAILURE);
	}

	//read and display fifo output to EOF
	while ((len = read(fd, buf, PIPE_BUF - 1)) > 0)
		printf("rdfifo read: %s", buf);

	close(fd);

	exit(EXIT_SUCCESS);
}
