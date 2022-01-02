#include <stdio.h>

int main(void)
{
	float money;

	printf("Enter an amount: ");
	scanf("%f", &money);

	printf("With tax added: $%.2f\n", money * 1.05);

	return 0;
}
