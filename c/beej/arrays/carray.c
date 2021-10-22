// Passing a pointer to an array to a function and changing it
#include <stdio.h>

void double_array(int *a, int len){

	// Multiply each element by 2
	// Will double the values in x in main()!
	// Both point to same space in memory
	for (int i = 0; i < len; i++)
		a[i] *= 2;
}

int main(void){
	int x[5] = {1, 2, 3, 4, 5};

	double_array(x, 5);

	for (int i = 0; i < 5; i++)
		printf("%d\n", x[i]);
}

