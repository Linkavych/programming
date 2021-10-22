/*
 * truc.c - a file for shortening files
 */
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

void usage(void);

int main(int argc, char *argv[]) {

	long len;

	if (argc != 3) {
		usage();
		exit(EXIT_FAILURE);
	}

	len = (long)strtol(argv[2], NULL, 10);

	if (truncate(argv[1], len)) {
		perror("truncate");
		exit(EXIT_FAILURE);
	}

	exit(EXIT_SUCCESS);
}

void usage(void) {
	puts("Usage: ./truc <filename> <length>");
}
