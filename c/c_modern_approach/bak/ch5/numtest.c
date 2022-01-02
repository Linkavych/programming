/*
 * Test how many digits are in a number
 */
#include <stdio.h>

int main(void)
{
	int num;

	printf("Enter a number (0-9999): ");
	scanf("%d", &num);

	printf("The number %d has ", num);

	if (num < 10){
		printf("1 digit.\n");
	}
	else if (num < 100){
		printf("2 digits.\n");
	}
	else if (num < 1000){
		printf("3 digits.\n");
	}
	else if (num < 10000){
		printf("4 digits.\n");
	}
	else
		printf("Unrecognized.\n");

	return 0;
}

