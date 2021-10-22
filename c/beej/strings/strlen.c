// Getting the length of a string with strlen()
#include <stdio.h>
#include <string.h>

int main(void){

	char *s = "Hello, world!";

	// The strlen() function from string.h returns an int type value
	printf("The string is %zu characters long.\n", strlen(s));
}


