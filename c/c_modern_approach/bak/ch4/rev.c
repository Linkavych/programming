/*
 * Prompt the user for a number
 * Print the number in reverse
 */
#include <stdio.h>

int main(void)
{
	int x, y, z, a, b, c, d, e, f, g, h;

	printf("Enter a two digit number: ");
	scanf("%d", &x);

	y = x % 10;
	z = x / 10;

	printf("Enter a three digit number: ");
	scanf("%d", &a);

	c = a % 100;
	b = a / 100;
	d = c % 10;
	e = c / 10;

	printf("Enter a three digit number: ");
	scanf("%1d%1d%1d", &f, &g, &h);

	printf("Your new two digit number: %d%d\n", y, z);
	printf("Your new three digit number: %d%d%d\n", d, e, b);
	printf("Another three digit number (no math): %d%d%d\n", h,g,f);

	return 0;
}

