/*
 * Prompt the users for an amount of dollars and cents spent
 * Return the value with 5% tax included
 */
#include <stdio.h>

#define TAX 1.05

int main(void)
{
	float spent, wtax;

	printf("Enter the amount spent(e.g. 20.25): ");
	scanf("%f", &spent);

	wtax = TAX * spent;

	printf("Total with tax: %.2f\n", wtax);

	return 0;
}
