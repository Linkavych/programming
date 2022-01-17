#include <stdio.h>

int main(void)
{
	int a, b, x;

	printf("Enter a two-digit number: ");
	scanf("%d", &x);

	a = x / 10;
	b = x % 10;

	printf("The reverse is: %d%d\n", b, a);

	return 0;
}
