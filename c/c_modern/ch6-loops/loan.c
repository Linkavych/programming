/*
 * Calculate the remaining balance on a loan after three payments
 */
#include <stdio.h>

int main(void)
{
	float loan, rate, payment;
	int num;

	printf("Enter amount of loan: ");
	scanf("%f", &loan);
	printf("Enter interest rate: ");
	scanf("%f", &rate);
	printf("Enter monthly payment: ");
	scanf("%f", &payment);
	printf("Enter number of payments: ");
	scanf("%d", &num);

	float new, mrate, pmonth;

	new = loan;
	
	mrate = ((rate / 100) / 12) + 1;

	for (int i = 1; i <=num; i++){
		pmonth = (new - payment) * mrate;
		printf("Balance #%d: $%.2f\n", i, pmonth);
		new = pmonth;
	}
	return 0;
}
	

