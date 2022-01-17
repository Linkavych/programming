#include <stdio.h>

int main(void)
{
	int days, start;

	printf("Enter number of days in month: ");
	scanf("%d", &days);
	printf("Enter starting day of the week (1=Sunday, 7=Saturday: ");
	scanf("%d", &start);
  
	printf("   S   M   T   W   T   F   S\n");

	for (int i = 1, day = 1; i <= days + start -1; i++)
	{
		if (i < start)
			printf("    ");
		else
			printf("%4d", day++);
		if (i % 7 == 0)
			printf("\n");
	}

	return 0;
}
