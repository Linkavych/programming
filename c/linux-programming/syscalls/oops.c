/*
 * oops.c - using perror for syscall error handling
 */
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>

int main(void) {

	FILE *pfile;

	if ((pfile = fopen("foobar", "r")) == NULL){
		perror("fopen");
		exit(EXIT_FAILURE);
	}
	else {
		fprintf(stdout, "How did we get here?\n");
		fclose(pfile);
	}

	exit(EXIT_SUCCESS);
}
