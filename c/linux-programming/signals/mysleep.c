/*
 * Setting an alarm() in a program
 */
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(void) {

	// set the alarm()
	if ((alarm(5)) > 0){
		puts("an alarm was already set");
	}
	sleep(30);

	// should not get here
	puts("not here!");
	exit(EXIT_FAILURE);
}
