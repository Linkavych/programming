/*
 * Prompt the user to input their first and last name
 * and then print a welcome message. Try storing the input as a char
 * variable's value.
 *
 * Extra: Dynamically allocate the array size of the char variable based on
 * user input
 *
 */
#include <stdio.h>
#include <stdlib.h>

int main(void) {

	char *fname;
	char *lname;

	puts("Enter your first name: ");
	scanf("%ms", &fname);

	puts("Enter your last name: ");
	scanf("%ms", &lname);

	printf("Welcome, %s %s!\n", fname, lname);

	free(fname);
	free(lname);

	return 0;
}
