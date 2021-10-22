// Converting a numeric value to a string
#include <stdio.h>

int main(void)
{
	char s[10];
	float f = 3.14159;

	// Convert f to string, storing in s, writing at most 10 characters
	// including NUL terminator
	snprintf(s, 10, "%f", f);

	printf("String value: %s\n", s);
}
