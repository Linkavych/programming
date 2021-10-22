/*
 * newmask.c - resetting umask
 */
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>

int main(void) {

	mode_t newmask = 0666, oldmask;

	oldmask = umask(newmask);
	printf("old umask is %#o\n", oldmask);
	printf("new umask is %#o\n", newmask);

	system("touch foo");

	exit(EXIT_SUCCESS);
}
