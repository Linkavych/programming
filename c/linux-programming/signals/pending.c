/*
 * Detecting pending signals and handling them
 */
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <sys/types.h>

int main(void) {

	sigset_t set, pendset;
	struct sigaction action;

	sigemptyset(&set);

	// add the interesting signal
	sigaddset(&set, SIGTERM);

	// block it
	sigprocmask(SIG_BLOCK, &set, NULL);

	// send sigterm to self
	kill(getpid(), SIGTERM);


	// Get pending signals
	sigpending(&pendset);

	//if SIGTERM, ignore
	if (sigismember(&pendset, SIGTERM)) {
		sigemptyset(&action.sa_mask);
		action.sa_handler = SIG_IGN; //ignore sigterm
		sigaction(SIGTERM, &action, NULL);
	}

	// unblock SIGTERM
	sigprocmask(SIG_UNBLOCK, &set, NULL);

	exit(EXIT_SUCCESS);
}
