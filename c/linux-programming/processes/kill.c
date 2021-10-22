/*
 * using the kill() function to terminate a program
 * Only using the SIGKILL signal for this
 */
#include <stdio.h>
#include <stdlib.h>
#include <signal.h> // needed for kill()
#include <sys/types.h> ///needed for kill
#include <sys/wait.h>

int main(void) {

	pid_t child;
	int status, retval;

	if ((child = fork()) < 0){
		perror("fork");
		exit(EXIT_FAILURE);
	}
	if (child == 0) {
		sleep(1000); // sleeping long enough to be killed
		exit(EXIT_SUCCESS);
	} else {
		//using WNOHANG
		if ((waitpid(child, &status, WNOHANG)) == 0) {
			retval = kill(child, SIGKILL);
			if (retval) {
				perror("kill");
				puts("fail kill");
				waitpid(child, &status, 0);
			} else {
				printf("%d killed\n", child);
			}
		}
	}
	exit(EXIT_SUCCESS);
}
	
