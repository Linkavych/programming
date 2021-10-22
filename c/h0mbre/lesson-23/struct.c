/*
 * Create a simple struct of your choice. Do not create an instance of the struct yet.
 * Declare a pointer to the struct. Create an instance of the struct. Initialize the pointer to point
 * to the struct instance.
 *
 * Assign values to the interger member of the struct in three ways:
 * 	use standard dot-notation and then print
 * 	use dot-notation for the pointer initialized to the instance and print
 * 	use the -> indirect membership operator between the pointer name and the struct member and print
 */
#include <stdio.h>
#include <stdlib.h>

struct example {
	int num;
};

int main(void) {

	struct example *ptr;
	struct example Test;

	ptr = &Test;

	Test.num = 12;
	printf("Standard 1: %d\n", Test.num);

	(*ptr).num = 21;
	printf("Standard 2 w/ ptr: %d\n", (*ptr).num);

	ptr->num = 42;
	printf("Indirect method: %d\n", ptr->num);
}
	
