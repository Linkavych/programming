#include <stdio.h>

int main(void)
{
	float x;

	printf("Enter a value for x: ");
	scanf("%f", &x);

	printf("Value of the polynomial: %.2f\n", ((3.0f * (x * x * x * x * x)) + 
				(2 * (x * x * x * x)) - (5 * (x * x * x)) - (x * x) + (7 * x) - 6));

	return 0;
}
