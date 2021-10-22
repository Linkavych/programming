// Program meant to swap to integers

#include <stdio.h>

void swap(int *pa, int *pb) {
	int t = *pa;
	*pa = *pb;
	*pb = t;
	printf("Swap: a = %d, b = %d\n", *pa, t);
}

int main(void){

	int a = 21;
	int b = 17;

	swap(&a, &b);
	printf("Main: a = %d, b= %d\n", a, b);
	return 0;
}
