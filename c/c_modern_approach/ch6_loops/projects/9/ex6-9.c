#include <stdio.h>

int main(void)
{
	float loan, rate, payment;
	float mrate;
	int payments;

	printf("Enter amount of loan: ");
	scanf("%f", &loan);
	printf("Enter interest rate: ");
	scanf("%f", &rate);
	printf("Enter monthly payment: ");
	scanf("%f", &payment);
	printf("Total number of payments: ");
	scanf("%d", &payments);
	
	mrate = ((rate / 100.0) / 12.0);

	for (int i = 1; i <= payments; i++)
	{
		loan = loan - payment + (loan * mrate);
		if (loan < 0)
		{
			printf("Balance after payment #%d: No remaining balance\n", i);
			break;
		} else {
			printf("Balance after payment #%d: %.2f\n", i, loan);
		}
	}

	return 0;
}

