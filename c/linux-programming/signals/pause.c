/*
 * Using pause() to wait for a signal, then exiting
 */
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(void) {
	pause();
	exit(EXIT_SUCCESS);
}
