#include <stdio.h>

int main(void)
{
	int year, day, month;

	printf("Enter a date (mm/dd/yyyy): ");
	scanf("%d/%d/%d", &month, &day, &year);

	printf("Date: %d%d%d\n", year, month, day);

	return 0;
}
