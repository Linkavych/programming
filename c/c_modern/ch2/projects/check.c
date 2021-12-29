/*
 * Print a large check mark to the screen
 */
#include <stdio.h>

int main (void)
{
	char x = '*';

	printf("       %c\n", x);
	printf("      %c\n", x);
	printf("     %c\n", x);
	printf("%c   %c\n", x, x);
	printf(" %c %c\n", x, x);
	printf("  %c\n", x);

	return 0;
}
