// Using the static storage specifier
#include <stdio.h>

void counter(void){

	static int count = 1;

	printf("This has been called %d times\n", count);

	count++;
}

int main(void){

	counter();
	counter();
	counter();
	counter();
}
