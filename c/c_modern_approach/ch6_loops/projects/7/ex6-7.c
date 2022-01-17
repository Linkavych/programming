#include <stdio.h>

int main(void)
{

	int i, j, o, s;

	printf("This program prints a table of squares.\n");
	printf("Enter number of entries in table: ");
	scanf("%d", &j);

	o = 3;
	for (i = 1, s = 1; i <= j; o += 2, ++i)
	{
		printf("%10d%10d\n", i, s);
		s += o;
	}
	return 0;
}

