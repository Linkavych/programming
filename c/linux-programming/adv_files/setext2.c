/*
 * Set ext special flags on a file
 */
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <linux/ext2_fs.h>
#include <sys/ioctl.h>
#include <errno.h>

int main(int argc, char *argv[]) {

	int fd;
	long flags;

	if (argc != 2){
		puts("USAGE: ./setext2 <filename>");
		exit(EXIT_FAILURE);
	}

	if ((fd = open(argv[1], O_RDONLY)) < 0) {
		perror("open");
		exit(EXIT_FAILURE);
	}

	// setting flags on the file
	flags = EXT2_SYNC_FL | EXT2_NODUMP_FL;

	//set flags, bail on fail
	if (ioctl(fd, EXT2_IOCTL_SETFLAGS, &flags)){
		perror("ioctl");
		close(fd)
		exit(EXIT_FAILURE);
	}

	if (flags & EXT2_SYNC_FL)
		puts("SYNC flag set");

	if (flags & EXT2_NODUMP_FL)
		puts("NODUMP flag set");

	close(fd);
	exit(EXIT_FAILURE);
}
