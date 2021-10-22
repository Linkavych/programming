// Inputting a deliberately bad number to test error handling
#include <stdio.h> 
#include <stdlib.h>

int main(void)
{
	char *s = "34x90";
	char *badchar;

	//convert string s, a number in base 10, to unsigned long
	
	unsigned long int x = strtoul(s, &badchar, 10);

	// It will convert as much as possible:  34
	
	printf("%lu\n", x); // 34

	// But we can see the offending character because of our pointer
	
	printf("Invalid character: %c\n", *badchar); //"x"
}
