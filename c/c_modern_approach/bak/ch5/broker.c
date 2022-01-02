/*
 * Cascading IF statements to arrive at an answer
 */
#include <stdio.h>

int main(void)
{
	float commission, pps, value;
	int shares;

	printf("Enter price per share: ");
	scanf("%f", &pps);
	printf("Enter number of shares purchased: ");
	scanf("%d", &shares);

	value = pps * (float)shares;

	if (value < 2500.00f)
		commission = 30.00f + 0.17f * value;
	else if (value < 6250.00f)
		commission = 56.00f + 0.0066f * value;
	else if (value < 20000.00f)
		commission = 76.00f + 0.0034f * value;
	else if (value < 50000.00f)
		commission = 100.00f + 0.0022f * value;
	else if (value < 500000.00f)
		commission = 155.00f + 0.0011f * value;
	else
		commission = 255.00f + 0.0009f * value;

	if (commission < 39.00f)
		commission = 39.00f;

	printf("Value of purchase: %.2f\n", value);
	printf("Commission: $%.2f\n", commission);

	return 0;
}
