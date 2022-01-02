/* Declaring variables without initializing */
#include <stdio.h>

int main(void)
{
	int a, b, c;
	char d;
	float e;
	long f;
	long double g;

	printf("INTS: %d, %d, %d\n", a, b, c);
	printf("CHAR: %c\n", d);
	printf("FLOAT: %f\n", e);
	printf("LONG: %ld\n", f);
	printf("LONG DOUBLE: %Lf\n", g);

	return 0;
}
