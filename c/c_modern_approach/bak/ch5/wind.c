/*
 * Displaying a simplified wind scale
 */
#include <stdio.h>

int main(void)
{
	int knots;

	printf("Enter the wind speed in knots: ");
	scanf("%d", &knots);

	if (knots > 63){
		printf("Hurricane\n");
	}
	else if (knots < 64 && knots > 47){
		printf("Storm\n");
	}
	else if (knots < 48 && knots > 27){
		printf("Gale\n");
	}
	else if (knots > 3 && knots < 28){
		printf("Breeze\n");
	}
	else if (knots > 0 && knots < 4){
		printf("Light air\n");
	}
	else
		printf("Calm\n");

	return 0;
}
