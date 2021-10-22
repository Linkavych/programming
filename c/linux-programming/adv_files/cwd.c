/*
 * Print the current working directory
 */
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <errno.h>

#define BUFSZ 10

int main(void) {

	char *statbuf = malloc(BUFSZ);
	char *nullbuf = NULL;
	int i = 1;

	//statically allocate the buffer
	while ((getcwd(statbuf, i *BUFSZ)) == NULL) {
		++i;
		statbuf = realloc(statbuf, i * BUFSZ);
	}

	fprintf(stdout, "%d calls to realloc\n", i - 1);
	fprintf(stdout, "current dir is %s\n", statbuf);
	free(statbuf);

	//alternate method
	printf("current dir is %s\n", getcwd(nullbuf, -1));
	free(nullbuf);

	exit(EXIT_SUCCESS);
}
