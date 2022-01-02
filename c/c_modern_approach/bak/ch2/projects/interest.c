/*
 * Calculate the remaining balance on a loan after three payments
 */
#include <stdio.h>

int main(void)
{
	float loan, rate, payment;

	printf("Enter amount of loan: ");
	scanf("%f", &loan);
	printf("Enter interest rate: ");
	scanf("%f", &rate);
	printf("Enter monthly payment: ");
	scanf("%f", &payment);

	float month1, month2, month3, mrate;
	
	mrate = ((rate / 100) / 12) + 1;

	month1 = (loan - payment) * mrate;
	month2 = (month1 - payment) * mrate;
	month3 = (month2 - payment) * mrate;

	printf("Balance #1: $%.2f\n", month1);
	printf("Balance #2: $%.2f\n", month2);
	printf("Balance #3: $%.2f\n", month3);

	return 0;
}
	

