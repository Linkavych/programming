/*
 * Sum a series of variables
 */
#include <stdio.h>

int main(void)
{
	double n, sum = 0.0;

	printf("This program sums a series of integers (doubles).\n");
	printf("Enter numbers (0 to terminate): ");

	scanf("%lf", &n);
	while (n != 0){
		sum += n;
		scanf("%lf", &n);
	}
	printf("The sum is %lf.", sum);

	return 0;
}
