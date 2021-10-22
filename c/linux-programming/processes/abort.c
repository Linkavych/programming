/*
 * using the abort() function from stdlib.h to kill the program
 * Only want to use this when it is really needed in most programming
 * situations
 */
#include <stdio.h>
#include <stdlib.h>

int main(void) {

	abort(); //should dump a core file on abort

	exit(EXIT_SUCCESS); // shouldn't get here
}
