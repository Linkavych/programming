/*
 * Prompt the user for input of x
 * Solve for: 3x^5 + 2x^4 -5x^3 - x^2 +7x -6
 */
#include <stdio.h>

int main(void)
{
	float x, result;

	printf("Enter the value of x: ");
	scanf("%f", &x);

	result = ((3*(x*x*x*x*x)) + (2*(x*x*x*x)) - (5*(x*x*x)) - (x*x) + (7*x) - 6);

	printf("RESULT: %.2f\n", result);

	return 0;
}
