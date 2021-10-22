/*
 * Using the exec() family of calls in a prgram...
 * really just execve()
 */
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(void) {

	char *args[] = {"/bin/ls", NULL};

	if (execve("/bin/ls", args, NULL) == -1) {
			perror("execve");
			exit(EXIT_FAILURE);
	}

	puts("This should not appear.");
	exit(EXIT_SUCCESS);
}
			
