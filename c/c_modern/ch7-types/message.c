/*
 * Program that calculates the length of a provided message
 */
#include <stdio.h>

int main(void)
{
	int len = 0;

	printf("Enter a message: ");
	while (getchar() != '\n'){
		len++;
	}

	printf("Your message was %d characters.\n", len);

	return 0;
}
