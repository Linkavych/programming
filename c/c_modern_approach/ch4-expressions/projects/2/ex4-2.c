#include <stdio.h>

int main(void)
{
	int a, b, c, x;

	printf("Enter a three-digit number: ");
	scanf("%d", &x);

	a = x / 100;
	b = (x % 100) / 10;
	c = (x % 100) % 10;

	printf("The reverse is: %d%d%d\n", c, b, a);

	return 0;
}
