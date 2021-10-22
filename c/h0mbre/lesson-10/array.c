/*
 * Create an interger array with 10 intergers and then print the number of elements
 * in the array to ther terminal.
 * Hint: play with sizeof() function to determine how many bytes of storage an int takes
 */
#include <stdio.h>
#include <stdlib.h>

int main(void){

	int nums[10] = {0,1,2,3,4,5,6,7,8,9};

	printf("The array has %ld elements.", (sizeof(nums)/sizeof(int)));

	return 0;
}
