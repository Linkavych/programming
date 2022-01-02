#include <stdio.h>

int main(void)
{
	char x = '*';

	printf("%8c\n", x);
	printf("%7c\n", x);
	printf("%6c\n", x);
	printf("%c%4c\n", x, x);
	printf("%2c%2c\n", x, x);
	printf("%3c\n", x);

	return 0;
}
