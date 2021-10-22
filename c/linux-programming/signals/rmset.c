/*
 * Remove signals from a set
 */
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>

void err_quit(char *);

int main(void) {

	sigset_t newset;

	// create the set
	if ((sigfillset(&newset)) < 0) {
		err_quit("sigfillset");
	}
	// remove SIGALRM from set
	if ((sigdelset(&newset, SIGALRM)) < 0) {
		err_quit("sigaddset");
	}

	// sigalrm should be gone
	if (sigismember(&newset, SIGALRM)) {
		puts("SIGALRM is in signal mask");
	} else {
		puts("SIGALRM not in signal mask");
	}

	// sigterm should still be present
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
