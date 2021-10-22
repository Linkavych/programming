/*
 * initialize and declare an int variable with any value. Assign a pointer
 * variable to the int variable, and print the value of the pointer.
 */
#include <stdio.h>

int main(void){

	int i = 5;
	int *p = &i;

	printf("The value of the pointer is: %p\n", p);

	return 0;
}

