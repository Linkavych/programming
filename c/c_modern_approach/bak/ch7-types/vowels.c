/*
 * count the number of vowels in a sentence
 */
#include <stdio.h>
#include <ctype.h>

int main(void)
{
	char c;
	int sum = 0;


	printf("Enter a sentence: ");
	while ((c = getchar()) != '\n')
	{
		switch(toupper(c))
		{
			case 'A': case 'E': case 'I': case 'O': case 'U':
				sum++;
				break;
			default:
				break;
		}
	}

	printf("Your sentence contained %d vowels.\n", sum);

	return 0;
}
