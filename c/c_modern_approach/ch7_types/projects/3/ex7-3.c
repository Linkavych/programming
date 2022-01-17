#include <stdio.h>

int main(void)
{
	double n, sum = 0;

	printf("This program sums a series of integers.\n");
	printf("Enter integers (0 to terminate): ");

	scanf("%lf", &n);

	while (n != 0)
	{
		sum += n;
		scanf("%lf", &n);
	}
	printf("Sum: %.2f\n", sum);

	return 0;
}
