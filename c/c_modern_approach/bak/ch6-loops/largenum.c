/*
 * Find the largest in a series of numbers provided by the user
 * Input one number at a time
 * 0 to terminate program
 */
#include <stdio.h>

int main(void)
{
	float n, large;

	while (n != 0){
		printf("Enter a number: ");
	        scanf("%f", &n);

		if (n > large)
			large = n;
	}

	printf("\nThe largest number was %.2f\n", large);

	return 0;
}
