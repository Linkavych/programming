#include <stdio.h>

int main(void)
{
	float x;

	printf("Enter a value for x: ");
	scanf("%f", &x);

	printf("Value of the polynomial: %.2f\n", (((((3 * x) + 2) * x - 5) * x - 1) * x + 7) * x -6);

	return 0;
}
