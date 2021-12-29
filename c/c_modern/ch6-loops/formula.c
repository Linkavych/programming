/*
 * Solving for e int the forumla:
 *
 * e = 1+1/1!...
 */
#include <stdio.h>

int main(void)
{
	int n, denom;
	float e;

	printf("Enter a number: ");
	scanf("%d", &n);

	for (int i = 1, denom = 1; i <= n; i++){
		e += 1.0f / (denom *= i);
	}
	printf("Approximate e: %f\n", e);

	return 0;
}

