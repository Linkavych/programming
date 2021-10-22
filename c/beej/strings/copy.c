// Copying a string with strcpy()
#include <stdio.h>
#include <string.h>

int main(void){

	char s[] = "Hello, world!";
	char t[100];

	// Copy the string
	strcpy(t, s);

	// Modify t
	t[0] = '!';

	printf("%s\n", s);
	printf("%s\n", t);
}
