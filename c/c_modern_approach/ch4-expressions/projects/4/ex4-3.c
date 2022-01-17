#include <stdio.h>

int main(void)
{
	int a, b, c;

	printf("Enter a three-digit number: ");
	scanf("%1d%1d%1d", &a, &b, &c);

	printf("The reverse: %d%d%d", c, b, a);

	return 0;
}
