// Subtracting pointers to get the length of a string
// Basically, a strlen() version
#include <stdio.h>

int my_strlen(char *s){
	// start scanning from the beginning of string
	char *p = s;

	// Stop at the NULL
	while (*p != '\0')
		p++;

	return p - s;
}

int main(void){
	printf("%d\n", my_strlen("Hello, world!")); // returns 13
}

// Pointer subtraction only works on items within the same array
