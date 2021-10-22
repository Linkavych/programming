//printing some sizes
#include <stdio.h>

int main(void) {

	int *p;

	printf("%ld is the size of int\n", sizeof(int));
	printf("%ld is the size of the int *p\n", sizeof(p));
	printf("%ld is the size of int\n", sizeof(*p));
}
