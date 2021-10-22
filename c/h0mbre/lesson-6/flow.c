/*
 * Prompt the user for a numerator and denominator. Tell the user whether or not
 * there is a remainder using an IF construct.
 */
#include <stdio.h>
#include <stdlib.h>

int main(void) {

	int numer;
	int denom;

	printf("Enter a numerator: ");
	scanf("%d", &numer);
	printf("Enter the denominator: ");
	scanf("%d", &denom);

	if (numer % denom == 0)
		printf("There is NOT a remainder!\n");
	else
		printf("There IS a remainder!\n");

	return 0;
}

