/*
 * Formats product information entered by a user
 */
#include <stdio.h>

int main(void)
{
	float price;
	int day, month, year, item;

	printf("Enter the item number: ");
	scanf("%d", &item);
	printf("Enter the unit price: ");
	scanf("%f", &price);
	printf("Enter the purchase date (mm/dd/yyy): ");
	scanf("%d/%d/%d", &month, &day, &year);

	printf("ITEM\tUNIT\tPURCHASE\n\tPRICE\tDATE\n%d\t$%.2f\t%.2d/%.2d/%d\n", 
			item, price, month, day, year);

	return 0;
}
