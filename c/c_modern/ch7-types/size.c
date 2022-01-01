/*
 * Print the size of various data types
 */
#include <stdio.h>

int main(void)
{
	int x;
	short y;
	long z;
	float a;
	double b;
	long double c;

	printf("Integer: %lu\n", sizeof(x));
	printf("Short Integer: %lu\n", sizeof(y));
	printf("Long Int: %lu\n", sizeof(z));
	printf("Float: %lu\n", sizeof(a));
	printf("Double: %lu\n", sizeof(b));
	printf("Long Double: %lu\n", sizeof(c));

	return 0;
}

