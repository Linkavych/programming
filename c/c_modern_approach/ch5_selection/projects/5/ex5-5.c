#include <stdio.h>

int main(void)
{
	float income, tax_due;

	printf("Enter the taxable income: ");
	scanf("%f", &income);

	if (income < 750.00f)
		tax_due = income * 1.01;
	else if (income >= 750.00f && income < 2251.00f)
		tax_due = 7.50f + ((income - 750.00f) * .02f);
	else if (income >= 2251.00f && income < 3751.00f)
		tax_due = 37.50f + ((income - 2250.00f) * .03f);
	else if (income >= 3751.00f && income < 5251.00f)
		tax_due = 82.50f + ((income - 3750.00f) * 0.04f);
	else if (income >= 5251.00f && income < 7001.00f)
		tax_due = 142.50 + ((income - 5250.00f)  * 0.05f);
	else if (income > 7000.00f)
		tax_due = 230.00 + ((income - 7000.00f) * 0.06f);

	printf("Taxes due: $%.2f\n", tax_due);

	return 0;
}
		
