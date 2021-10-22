/*
 * Making a new directory
 */
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <unistd.h>

int main(int argc, char *argv[]){

	if (mkdir(argv[1], 0755)) {
		perror("mkdir");
		exit(EXIT_FAILURE);
	}

	exit(EXIT_SUCCESS);
}
