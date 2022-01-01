/*
 * Check a number for a repeated digit
 */
#include <stdbool.h>
#include <stdio.h>

int main(void)
{

	bool digit_seen[10] = {false};
	bool repeated[10] = {false};
	int counter[10] = {0};
	int digit;
	long n;

	printf("Enter a number: ");
	scanf("%ld", &n);

  while (n > 0)
	{
		digit = n % 10;
		if (digit_seen[digit])
		{
			repeated[digit] = true;
			counter[digit] += 1;
		}
		else
		{
			digit_seen[digit] = true;
			counter[digit] += 1;
		}
		n /= 10;
	}

	printf("Digit:\t     0 1 2 3 4 5 6 7 8 9\n");
	printf("Occurences:  ");

	for (int i = 0; i < 10; i++)
	{
		printf("%d ", counter[i]);
	}
	printf("\n");
	return 0;
}

