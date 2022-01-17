/*
 * Printing a table of squares
 */
#include <stdio.h>

int main(void)
{
  long int i, n;

	printf("This program prints a table of squares.\n");
	printf("Enter number of entries in the table: ");
	scanf("%ld", &n);

  // Clearing newline from the buffer
	getchar();

	for ( i = 1; i <= n; i++)
		if (i % 24 == 0)
		{
			printf("%10ld%10ld\n", i, i * i);
			printf("Press Enter to continue...");
			if (getchar() == '\n')
				continue;
		}
		else
			printf("%10ld%10ld\n", i, i * i);
	
	return 0;
}
