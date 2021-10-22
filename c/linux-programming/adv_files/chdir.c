/*
 * Change to a new directory
 */
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <errno.h>

int main(int argc, char *argv[]){

	if (chdir(argv[1]) < 0) {
		perror("chdir");
		exit(EXIT_FAILURE);
	}
	system("ls");

	exit(EXIT_SUCCESS);
}
