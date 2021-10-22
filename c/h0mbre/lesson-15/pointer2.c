#include <stdio.h>

int main(void){

	int i = 12;
	int *p = &i;

	printf("The value of int variable is: %d\n", i);
	printf("The value of the pointer to the int variable is: %p\n", p);
	printf("The memory address of the int variable is : %p\n", &i);
	printf("The value held at the memory location that the pointer is pointing to is: %d\n", *p);

	return 0;
}

