/*
 * Print a table of squares
 */
#include <stdio.h>

int main(void)
{
	int i, n;

	printf("This program prints a table of squares.\n");
	printf("Enter number of table entries: ");
	scanf("%d", &n);
	getchar(); //ungets the \n from the buffer

	for (i = 1; i <= n; i++){
		printf("%10d%10d\n", i, i*i);
		if (i % 24 == 0){
			printf("Press Enter to continue...\n");
			if (getchar() == '\x0a')
				continue;
		}
	}

	return 0;
}
