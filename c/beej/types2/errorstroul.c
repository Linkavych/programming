// Better error handling with the strtol-style functions
#include <stdio.h>
#include <stdlib.h>

int main(void){

	char *s = "3490";
	char *badchar;

	unsigned long int x = strtoul(s, &badchar, 10);

	// Check if stuff went well
	
	if (*badchar == '\0'){
		printf("Success! %lu\n", x);
	} else {
		printf("Partial conversion: %lu\n", x);
		printf("Invalid character: %c\n", *badchar);
	}
}

