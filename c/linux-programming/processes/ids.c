/*
 * Getting the real and effective ids
 * getuid, geteuid, getgid,getegid
 */
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h> // required to call these process ID functions
#include <unistd.h> // this is where the get**id() functions live

int main(void) {

	printf("Real User ID: %d\n", getuid());
	printf("Effective user ID: %d\n", geteuid());
	printf("Real group ID: %d\n", getgid());
	printf("Effective GID: %d\n", getegid());

	exit(EXIT_SUCCESS);

}
	
