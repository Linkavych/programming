/*
 * Initialize an int array of 10 elements and then print the value of the array with printf
 */
#include <stdio.h>

int main(void){

	int arr[10] = {0,1,2,3,4,5,6,7,8,9};

	printf("%p - This is the pointer to the first element in the array.\n", arr);
	printf("%p - Which matches this (arr[0])!\n", &arr[0]);

	return 0;
}

