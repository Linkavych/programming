/*
 * Greatest common denominator
 */
#include <stdio.h>

int main(void)
{
	int x, y, gcd;

	printf("Enter a fraction (2/4) to reduce: ");
	scanf("%d/%d", &x, &y);

	for (int i = 1; i <= x && i <= y; i++)
	{
		if (x % i == 0 && y % i == 0)
			gcd = i;
	}
	printf("GCD is: %d\n", gcd);
	printf("Reduced fraction is: %d/%d\n", x/gcd, y/gcd);
	return 0;
}



