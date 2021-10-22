// Allocating memory for an array with malloc()
#include <stdio.h>
#include <stdlib.h>

int main(void){

	// Allocate space for 10 ints
	int *p = malloc(sizeof(int) * 10);

	// Assign them values
	for (int i = 0; i < 10; i++)
		p[i] = i * 5;

	// Print all values
	for (int i = 0; i < 10; i++)
		printf("%d\n", p[i]);

	// Free the memory
	free(p);
}
