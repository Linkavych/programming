#include <stdio.h>

#define PI 3.14f

int main(void)
{
	int r; 
	float vol;

	printf("Enter the radius of the sphere: ");
	scanf("%d", &r);

	vol = ((4.0f / 3.0f) * r) * (PI * PI * PI);

	printf("Volume of a 10-meter radius sphere: %.2f\n", vol);

	return 0;
}

