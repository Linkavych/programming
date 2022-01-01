/*
 * Calculate the average word length for a sentence
 */
#include <stdio.h>

int main(void)
{

	float sum = 0.0;
	int spaces = 0;
	char c;

	printf("Enter a sentence: ");

	while ((c = getchar()) != '\n')
	{
		if (c == ' '){
			spaces++;
		}
		else
			sum++;
	}

	printf("Average word length: %.2f\n", (sum / (spaces + 1)));

	return 0;
}
