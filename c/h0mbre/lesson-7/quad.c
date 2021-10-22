/*
 * Prompt the user for A, B, and C values and use them to determine the value of X
 * using the quadratic formula. Use math.h to make life easier.
 *
 * Extra: Build in a mechanism which checks the solution by plugging it back into
 * the formula and seeing if it equals 0. Use IF control flow to instruct the user
 * to double check all solutions which aren't confirmed.
 */
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int main(void) {

	float A;
	float B;
	float C;
	float X1, X2;

	printf("Enter the value for A: ");
	scanf("%f", &A);
	printf("Enter the value for B: ");
	scanf("%f", &B);
	printf("Enter the value for C: ");
	scanf("%f", &C);

	X1 = (-B - sqrt((B * B) - (4 * A * C))) / (2 * A);
	X2 = (-B + sqrt((B * B) - (4 * A * C))) / (2 * A);

	printf("The answer using the '+' operator is: %f\n", X2);
	printf("The answer using the '-' operator is: %f\n", X1);

	return 0;
}


