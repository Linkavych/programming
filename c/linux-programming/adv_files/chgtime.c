/*
 * Using the utime routine to change time
 */
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <utime.h>
#include <fcntl.h>

int main(void) {
	time_t now = 1000000000;
	struct utimbuf buf;
	int fd;

	buf.actime = now;
	buf.modtime = now;

	fd = open("foo.bar", O_CREAT, 0644);
	utime("foo.bar", &buf);
	close(fd);

	exit(EXIT_SUCCESS);
}
