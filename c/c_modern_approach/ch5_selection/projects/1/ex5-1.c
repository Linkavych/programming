#include <stdio.h>

int main(void) 
{
	int num;

	printf("Enter a number: ");
	scanf("%d", &num);

	if (num < 10)
		printf("The number %d has one digit.\n", num);
	else if (num < 100)
		printf("The number %d has two digits.\n", num);
	else if (num < 1000)
		printf("The number %d has three digits.\n", num);
	else if (num < 10000)
		printf("The number %d has four digits.\n", num);
	else
		printf("Not a valid number.\n");

	return 0;
}
