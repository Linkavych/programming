#include <stdio.h>

int main(void)
{
	int x;

	printf("Enter an integer: ");
	scanf("%d", &x);

	printf("Reversed: ");
  
	do {
		printf("%d", x % 10);
		x /= 10;
	} while (x != 0);

	printf("\n");

	return 0;
}
