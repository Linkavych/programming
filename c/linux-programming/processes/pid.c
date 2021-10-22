/*
 * Print the pid and ppid of the process running.
 */
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h> // getpid() and getppid() live here

int main(void) {

	printf("PID = %d\n", getpid());
	printf("PPID = %d\n", getppid());
	exit(EXIT_SUCCESS);
}
