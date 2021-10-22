/*
 * read and write system calls
 *
 */
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

int main(void) {

	int fdsrc, fdnull, fdtmp, numbytes;
	char fname[] = "fread.c";
	char buf[10];

	//open the source file, /dev/null, and /tmp/foo.bar
	if ((fdsrc = open(fname, O_RDONLY)) < 0) {
		perror("open fdsrc");
		exit(EXIT_FAILURE);
	}

	if ((fdnull = open("/dev/null", O_WRONLY)) < 0) {
		perror("open fdnull");
		close(fdsrc); // close because we opened it already
		exit(EXIT_FAILURE);
	}

	if ((fdtmp = open("/tmp/foo.bar", O_CREAT | O_TRUNC | O_WRONLY, 0644)) < 0) {
			perror("open fdtmp");
			close(fdsrc);
			close(fdnull);
			exit(EXIT_FAILURE);
	}

	// read up to 10 bytes
	while ((numbytes = read(fdsrc, buf, 10)) != 0) {
		if (write(fdnull, buf, 10) < 0)
			perror("write /dev/null");
		if (write(fdtmp, buf, numbytes) < 0)
			perror("write /tmp/foo.bar");
	}


	// close and exit
	close(fdsrc);
	close(fdtmp);
	close(fdnull);

	exit(EXIT_SUCCESS);
}
