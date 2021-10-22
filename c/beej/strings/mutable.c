// Mutable strings vs immutable
#include <stdio.h>
#include <string.h>

int main(void){

	// Pointer to a string is NOT mutable
	char *s = "Hello, world!\n";
        // A string array IS MUTABLE
	char z[] = "Bye, world!\n";

	printf("%s", s);
	printf("%s", z);

	// Mutating the second string
	z[0] = 'F';

	printf("%s", z);
}

