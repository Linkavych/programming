/*
 * Implementing our own perror() function with strerror()
 *
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

void mperror(const char *msg, int errnum);

int main(void) {

	FILE *pfile;

	if ((pfile = fopen("foobar", "r")) == NULL){
		mperror("fopen", errno);
		exit(EXIT_FAILURE);
	} else {
		fprintf(stdout, "Why are we here?\n");
		fclose(pfile);
	}
	exit(EXIT_SUCCESS);
}

void mperror(const char *msg, int errnum) {
	fprintf(stderr, "%s: %s\n", msg, strerror(errnum));
}
