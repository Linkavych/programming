/*
 * Accept a date input from the user and display it
 */
#include <stdio.h>

int main(void)
{
	int month, day, year;

	printf("Enter the date (mm/dd/yyyy): ");
	scanf("%d/%d/%d", &month, &day, &year);

	printf("Date: %d%2.2d%2.2d\n", year, month, day);

	return 0;
}
