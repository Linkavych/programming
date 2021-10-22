/*
 * Illustrating the behavior of getenv()
 */
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main (void) {

	char enval[] = {"MYPATH=/usr/local/bin"};

	if (putenv(enval)){
		puts("putenv failed.");
	} else {
		puts("putenv succeeded");
	}

	if (getenv("MYPATH")){
		printf("MYPATH=%s\n", getenv("MYPATH"));
	} else {
		puts("MYPATH unassigned");
	}

	if (getenv("YOURPATH")) {
		printf("YOURPATH=%s\n", getenv("YOURPATH"));
	} else {
		puts("YOURPATH unassigned.");
	}

	exit(EXIT_SUCCESS);
}
