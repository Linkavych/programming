#include <stdio.h>

int main(void)
{
	int hour, min;

	printf("Enter a 24-hour time: ");
	scanf("%d:%d", &hour, &min);
  
	printf("Equivalent 12-hour time: ");

	if (hour > 12)
		printf("%d:%d PM\n", hour - 12, min);
	else if (hour < 12)
		printf("%d:%d AM\n", hour, min);
	else if (hour == 12)
		printf("%d:%d AM/PM\n", hour, min);
	else
		printf("INVALID\n");

	return 0;
}
