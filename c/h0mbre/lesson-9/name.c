/*
 * Take two command line arguments from the user, their first and last name
 * and print a welcome message. Program should check for two arguments and then
 * print usage instructions if the user submits too few or too many arguments.
 */
#include <stdio.h>
#include <stdlib.h>

void usage(void){
	printf("Usage: ./name <fname> <lname>\n");
}

int main(int argc, char *argv[]){
	char *fname = argv[1];
	char *lname = argv[2];

	if (argc != 3){
		usage();
		exit(EXIT_FAILURE);
	} else {
		printf("Welcome, %s %s!\n", fname, lname);
	}
	return 0;
}


