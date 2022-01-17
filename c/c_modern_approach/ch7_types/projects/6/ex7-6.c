#include <stdio.h>

int main(void)
{

	printf("Size of various types:\n");
	printf("Int: %lu\nShort: %lu\nLong: %lu\n", (unsigned long)sizeof(int), (unsigned long)sizeof(short), (unsigned long) sizeof(long));
  printf("Float: %lu\nDouble:%lu\nLong Double: %lu\n", (unsigned long) sizeof(float), (unsigned long)sizeof(double), (unsigned long)sizeof(long double));

	return 0;
}
