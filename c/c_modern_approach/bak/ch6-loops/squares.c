/*
 * Print even squares between 1 and n based on user input
 */
#include <stdio.h>

int main(void)
{
	int x;

	printf("Enter a number: ");
	scanf("%d", &x);

	for (int i = 1; i <= x; i++){
		if (((i * i) % 2 == 0) && ((i * i) <= x))
			printf("%5d\n", i * i);
	}
	return 0;
}
