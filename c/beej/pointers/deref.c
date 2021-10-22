#include <stdio.h>

int main(void){

	int i;
	int *p;

	p = &i;

	i = 10;
	*p = 20;  // i is not 20!

	printf("%d is i\n", i);
	printf("And p is %d\n", *p);
}


