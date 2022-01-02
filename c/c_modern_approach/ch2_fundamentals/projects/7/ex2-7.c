#include <stdio.h>

int main(void)
{
	int x;

	printf("Enter a dollar amount: ");
	scanf("%d", &x);

	printf("$20 bills: %d\n", x / 20);
	printf("$10 bills: %d\n", (x % 20) / 10);
	printf(" $5 bills: %d\n", ((x % 20) % 10) / 5);
	printf(" $1 bills: %d\n", (((x % 20) % 10) % 5));

	return 0;
}
