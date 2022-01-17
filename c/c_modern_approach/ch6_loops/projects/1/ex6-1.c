#include <stdio.h>

int main(void)
{
	float num, largest;

	printf("Enter a number: ");
	scanf("%f", &num);

	while (num > 0)
	{
		if (num > largest)
		{
			largest = num;
		}
		printf("Enter a number: ");
		scanf("%f", &num);
	}
	printf("The largest number entered was: %.2f\n", largest);

	return 0;
}

