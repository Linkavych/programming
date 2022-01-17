// Calculate a broker's commission
#include <stdio.h>

int main(void) 
{
	float commission, value, rival, pps;
	int shares;

	printf("Enter the number of shares: ");
	scanf("%d", &shares);
	printf("Enter the price per share: ");
	scanf("%f", &pps);

	value = (float) shares * pps;

	if (shares >= 2000)
		rival = 33.00f + 0.02f * value;
	else
		rival = 33.00f + 0.03 * value;

	if (value < 2500.00f)
		commission = 30.00f + .017f * value;
	else if (value < 6250.00f)
		commission = 56.00f + 0.0066f * value;
	else if (value < 20000.00f)
		commission = 76.00f + 0.0034f * value;
	else if (value < 50000.00f)
		commission = 100.00f + 0.0022f * value;
	else if (value < 5000000.00f)
		commission = 155.00f + 0.0011f * value;
	else
		commission = 255.00f + 0.0009f * value;

	if (commission < 39.00f)
		commission = 39.00f;

	printf("Commission: $%.2f\n", commission);
  printf("Rival commission: $%.2f\n", rival);
	
	return 0;
}
