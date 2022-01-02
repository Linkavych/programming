/*
 * Prompt the user for input of a US dollar amount spent
 * Show how to pay using the least amount of 20, 10, 5, 1 bills
 */
#include <stdio.h>

int main(void)
{
	int dollars;

	printf("Enter a dollar amount: ");
	scanf("%d", &dollars);

	int twenty = dollars /  20;
	int ten = (dollars - (twenty * 20)) / 10;
	int five = ((dollars - (twenty * 20)) - (ten * 10)) / 5;
	int single = ((dollars - (twenty * 20)) - (ten * 10)) % 5;

	printf("$20 bills: %d\n", twenty);
	printf("$10 bills: %d\n", ten);
	printf("$5 bills: %d\n", five);
	printf("$1 bills: %d\n", single);

	return 0;
}
	
