#include <stdio.h>

int main(void)
{
	int item, day, month, year;
	float price;

	printf("Enter item number: ");
	scanf("%d", &item);
	printf("Enter unit price: ");
	scanf("%f", &price);
	printf("Enter purchase date (mm/dd/yyyy): ");
	scanf("%d/%d/%d", &month, &day, &year);

	printf("ITEM\t\tUNIT\t\tPURCHASE\n");
	printf("    \t\tPRICE\t\tDATE\n");
	printf("%-4d\t\t$%-4.2f\t\t%d/%d/%d\n", item, price, month, day, year);

	return 0;
}
