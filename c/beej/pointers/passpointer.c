// Passing a pointer to a function!
#include <stdio.h>

void increment(int *p){

	*p = *p + 1;
}

int main(void){
	int i = 10;
	int *j = &i;

	printf("i is %d\n", i);
	printf("i is also %d\n", *j);

	increment(j);

	printf("i is now %d\n", i);
}

