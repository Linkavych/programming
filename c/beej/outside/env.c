//Grabbing an environment variable
#include <stdio.h>
#include <stdlib.h>

int main(void) {

	char *val = getenv("FROTZ"); // try to get this value

	// Check for exists
	if (val == NULL){
		printf("Cannot find FROTZ environment variable.\n");
		return EXIT_FAILURE;
	}

	printf("Value: %s\n", val);
}

