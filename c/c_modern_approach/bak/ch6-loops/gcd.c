/*
 * Greatest common denominator
 */
#include <stdio.h>

int main(void)
{
	int x, y, gcd;

	printf("Enter two integers: ");
	scanf("%d %d", &x, &y);

	for (int i = 1; i <= x && i <= y; i++)
	{
		if (x % i == 0 && y % i == 0)
			gcd = i;
	}

	printf("GCD is: %d\n", gcd);
	return 0;
}



