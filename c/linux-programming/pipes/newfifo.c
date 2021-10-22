/*
 * Using named pipes in C
 */
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <sys/stat.h>
#include <sys/types.h>

int main(int argc, char *argv[]){

	mode_t mode = 0666;

	if (argc != 2){
		puts("USAGE: newfifo <name>");
		exit(EXIT_FAILURE);
	}

	if ((mkfifo(argv[1], mode)) < 0) {
		perror("mkfifo");
		exit(EXIT_FAILURE);
	}

	exit(EXIT_SUCCESS);
}
