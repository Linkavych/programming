/*
 * Setting a few alarms
 */
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>

int main(void) {

	long int erret;

	if ((alarm(15)) > 0){
		puts("an alarm was already set");
	}

	// Set another alarm
	sleep(3);
	erret = alarm(5);

	if (erret > 0) {
		printf("%ld seconds left in the first alarm\n", erret);
	}

	//cacnel second alarm
	sleep(2);
	printf("%d seconds left on second alarm\n", alarm(0));

	exit(EXIT_FAILURE);
}
