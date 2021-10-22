// using realloc to resize some memory
//
#include <stdio.h>
#include <stdlib.h>

int main(void){

	// Allocate space for 20 floats
	float *p = malloc(sizeof(float) * 20);

	// Assign them values
	for (int i = 0; i < 20; i ++)
		p[i] = i / 20.0;

	// Change to a 40 float array
	float *new_p = realloc(p, sizeof *p * 40);

	// Test for success
	if (new_p == NULL){
		printf("Error in allocating memory!\n");
		return 1;
	}

	p = new_p;

	// Assign new elements
	for (int i = 0; i < 40; i++)
		p[i] = 1.0 + (i - 20) / 20.0;

	// Print some values
	for (int i = 0; i < 40; i++)
		printf("%.2f\n", p[i]);

	// free the memory
	free(p);
}

