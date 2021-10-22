/*
 * Prompt the user to input their first and last name
 * and then print a welcome message. Try storing the input as a char
 * variable's value.
 *
 * Easy: Allocate an arbitrary amount of indices to your char array and pray user 
 * input fits
 */
#include <stdio.h>
#include <stdlib.h>

int main(void) {

	char fname[80];
	char lname[80];

	puts("Enter your first name: ");
	scanf("%s", &fname);

	puts("Enter your last name: ");
	scanf("%s", &lname);

	printf("Welcome, %s %s!\n", fname, lname);

	return 0;
}
