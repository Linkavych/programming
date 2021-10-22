// Doing array and pointer equivalence
#include <stdio.h>

int main(void){

	int a[] = {11, 22, 33, 44, 55};
	int *p = a; // points to first element of a - 11

	// Print the elements of the array using different notation
	for (int i = 0; i < 5; i++)
		printf("%d\n", a[i]); // Array notation with a

	for (int i = 0; i < 5; i++)
		printf("%d\n", p[i]); // Array notation with p

	for (int i = 0; i < 5; i++)
		printf("%d\n", *(a + i)); // Pointer notation with a

	for (int i = 0; i < 5; i++)
		printf("%d\n", *(p + i)); //Pointer notation with p

	for (int i = 0; i < 5; i++)
		printf("%d\n", *(p++)); // moving the pointer
	// Above does not work on the array
	// printf("%d\n", *(a++)) throws an error
}

