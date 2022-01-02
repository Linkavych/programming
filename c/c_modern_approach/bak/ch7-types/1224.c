/*
 * Ask user for a 12-hour time
 * display time in 24-hour format
 */
#include <stdio.h>
#include <ctype.h>

int main(void)
{
	int hour, minute;
	char c;
	char m = 'M';

	printf("Enter a 12-hour time with AM/PM indicator: ");
	scanf("%d :%d %c", &hour, &minute, &c);

	if (toupper(c) == 'P')
		printf("24-hour time: %d:%.2d %c%c\n", (hour + 12), minute, toupper(c), m);
	else
		printf("24-hour time: %.2d:%.2d %c%c\n", hour, minute, toupper(c), m);

	return 0;
}
