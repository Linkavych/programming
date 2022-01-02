/*
 * Compute the factorial of a positive integer
 * using different data types
 */
#include <stdio.h>

int main(void)
{
	short a;
	int b;
	long int c;
	long long int d;
	float e;
	double f;
	long double g;

	short fact = 1;

	printf("Enter a positive integer: ");
	scanf("%hd", &a);

	for (int i = a; i > 1; i--)
		fact *= i;

	printf("Factorial of %d: %d\n", a, fact);

	return 0;
}
