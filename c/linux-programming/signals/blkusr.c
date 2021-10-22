/*
 * Custom signal handler for SIGUSR1
 */
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>

void err_quit(char *); // error function
void hndl_usr1(int); // signal handler

int main(void) {

	struct sigaction action;

	//setup the handler
	action.sa_handler = hndl_usr1;
	sigemptyset(&action.sa_mask);
	action.sa_flags = SA_NOCLDSTOP;

	// register the handler
	if ((sigaction(SIGUSR1, &action, NULL)) < 0) {
		err_quit("sigaction");
	}
	// sleep on signal
	sleep(60);

	exit(EXIT_SUCCESS);
}

void err_quit(char *msg){
	perror(msg);
	exit(EXIT_FAILURE);
}

void hndl_usr1(int signum){
	if (signum == SIGUSR1){
		puts("Caught USR1");
	} else {
		printf("Caught %d\n", signum); 
	}
}
