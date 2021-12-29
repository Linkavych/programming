/*
 * Calculate the number of digits in an integer
 */
#include <stdio.h>

int main(void)
{
	int digits = 0, n;

	printf("Enter a nonnegative integer: ");
	scanf("%d", &n);

	do {
		n /= 10;
		digits++;
	} while (n > 0);

	printf("The number of digits is %d\n", digits);

	return 0;
}
