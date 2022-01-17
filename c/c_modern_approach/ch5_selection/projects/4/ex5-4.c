#include <stdio.h>

int main(void)
{
	int speed;
  
	printf("Enter a wind speed (knots): ");
	scanf("%d", &speed);

	printf("Beaufort scale rating: ");

	if (speed > 63)
		printf("Hurricane\n");
	else if (speed < 1)
		printf("Calm\n");
	else if (speed >= 1 && speed < 4)
		printf("Light air\n");
	else if(speed >= 4 && speed < 28)
		printf("Breeze\n");
	else if (speed >= 28 && speed < 48)
		printf("Gale\n");
	else if (speed >=48 && speed < 64)
		printf("Storm\n");

	return 0;
}
