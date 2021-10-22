/*
 * Using wait() to ensure the parent process collects the child
 *
 * wait() and waitpid() are in <sys/wait.h> and also need the <sys/types.h> header
 */
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

int main(void) {

	pid_t child;
	int status;

	if ((child = fork()) == -1){
		perror("fork");
		exit(EXIT_FAILURE);
	}
	else if (child == 0) {
		puts("in child");
		printf("\tchild pid = %d\n", getpid());
		printf("\tchild ppid = %d\n", getppid());
		exit(EXIT_SUCCESS);
	} else {
		waitpid(child, &status, 0);
		puts("in parent");
		printf("\tparent pid= %d\n", getpid());
		printf("\tparent ppid = %d\n", getppid());
		printf("\tchild exited with %d\n", status);
	}
	exit(EXIT_SUCCESS);
}

