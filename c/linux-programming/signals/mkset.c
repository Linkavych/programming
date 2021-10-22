/*
 * Messing with creating signal handlers
 */
#include <signal.h>
#include <stdlib.h>
#include <stdio.h>

void err_quit(char *);

int main(void) {

	sigset_t newset;

	// create a set
	if ((sigemptyset(&newset)) < 0) {
		err_quit("sigemptyset");
	}
	if ((sigaddset(&newset, SIGCHLD)) < 0) {
		err_quit("sigaddset");
	}

	// check the signal mask
	if (sigismember(&newset, SIGCHLD)) {
		puts("SIGCHLD is in signal mask");
	} else {
		puts("SIGCHLD not in signal mask");
	}

	//sigterm should not be there
	if (sigismember(&newset, SIGTERM)) {
		puts("SIGTERM in signal mask");
	} else {
		puts("SIGTERM not in signal mask");
	}
	exit(EXIT_SUCCESS);
}

void err_quit(char *msg) {
	perror(msg);
	exit(EXIT_FAILURE);
}
