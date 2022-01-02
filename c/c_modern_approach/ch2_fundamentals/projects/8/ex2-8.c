#include <stdio.h>

int main(void)
{
	float loan, rate, payment;
	float mrate;

	mrate = ((rate / 100.0) / 12.0);

	printf("Enter amount of loan: ");
	scanf("%f", &loan);
	printf("Enter interest rate: ");
	scanf("%f", &rate);
	printf("Enter monthly payment: ");
	scanf("%f", &payment);

	loan = loan - payment + (loan * mrate);
	printf("Balance after first payment: %.2f\n", loan);
	loan = loan - payment + (loan * mrate);
	printf("Balance after first payment: %.2f\n", loan);
	loan = loan - payment + (loan * mrate);
	printf("Balance after first payment: %.2f\n", loan);

	return 0;
}

