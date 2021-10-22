/*
 * Delete a directory
 */
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>

int main(int argc, char *argv[]){

	if (rmdir(argv[1])){
		perror("rmdir");
		exit(EXIT_FAILURE);
	}

	exit(EXIT_SUCCESS);
}
