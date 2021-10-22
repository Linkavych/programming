/*
 * Using fork for process creation
 */
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(void) {

	pid_t child;

	if ((child = fork()) == -1) { // using fork() to create a new child; fork is in unistd.h
		perror("fork");
		exit(EXIT_FAILURE);
	}
	else if (child == 0) {
		puts("in child");
		printf("\tchild pid = %d\n", getpid());
		printf("\tchild ppid = %d\n", getppid());
		exit(EXIT_SUCCESS);
	} else {
		fputs("in parent\n", stdout);
		printf("\tparent pid = %d\n", getpid());
		printf("\tparent ppid = %d\n", getppid());
	}
	exit(EXIT_SUCCESS);
}
