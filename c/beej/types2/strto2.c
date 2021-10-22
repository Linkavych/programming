// Using the strto family of functions for string conversion
#include <stdio.h>
#include <stdlib.h>

int main(void)
{
	char *s = "101010";

	//Convert string s, a num in base 10, to unsigned long
	// NULL means we dont care to learn about error info
	
	unsigned long int x = strtoul(s, NULL, 2);

	printf("%lu\n", x);
}

