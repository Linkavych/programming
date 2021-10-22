/*
 * Sending two signals to a running process: one to ignore, one to kill it
 */
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <sys/types.h>
#include <unistd.h>
#include <wait.h>

int main(void) {

	pid_t child;
	int erret;

	if ((child = fork()) < 0) {
		perror("fork");
		exit(EXIT_FAILURE);
	}
	else if (child == 0){
		sleep(30);
	}
	else {
		//sending signal to ignore
		printf("sending SIGCHLD to %d\n", child);
		erret = kill(child, SIGCHLD);
		if (erret < 0) {
			perror("kill:SIGCHLD");
		} else {
			printf("%d is still alive\n", child);
		}

		// now kill the child process
		printf("killing %d\n", child);
		if ((kill(child, SIGTERM)) < 0) {
			perror("kill:SIGTERM");
		}
		waitpid(child, NULL, 0);
	}
	exit(EXIT_SUCCESS);
}
