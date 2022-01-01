/*
 * Program to translate an alphanumeric phone number to numeric form
 */
#include <stdio.h>

int main(void)
{
	char x;

	printf("Enter a phone number: ");

	while ((x = getchar()) != '\n')
	{
		switch(x)
		{
			case 'A': case 'B': case 'C':
				putchar('2');
				break;
			case 'D': case'E': case 'F':
				putchar('3');
				break;
			case 'G': case 'H': case 'I':
				putchar('4');
				break;
			case 'J': case 'K': case 'L':
				putchar('5');
				break;
			case 'M': case 'N': case 'O':
				putchar('6');
				break;
			case 'P': case 'Q': case 'R': case 'S':
				putchar('7');
				break;
			case 'T': case 'U': case 'V':
				putchar('8');
				break;
			case 'W': case 'X': case 'Y': case 'Z':
				putchar('9');
				break;
			default:
				putchar(x);
				break;
		}
	}
	printf("\n");

	return 0;
}



