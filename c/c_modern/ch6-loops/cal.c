/*
 * Print a simple calendar
 * User input: number of days, starting day
 */
#include <stdio.h>

int main(void)
{
	int start, days, day;

	printf("Enter number of days in month: ");
	scanf("%d", &days);
	printf("Enter starting day (1=Sunday, 7=Saturday): ");
	scanf("%d", &start);

	printf("\n   S   M   T   W   T   F   S\n");


	for (int i = 1, day = 1; i <= days + start - 1; i++){
		if (i < start)
			printf("    ");
		else 
			printf("%4d", day++);
		if ((i % 7) == 0)
			printf("\n");
	}
	printf("\n");
	return 0;
}
