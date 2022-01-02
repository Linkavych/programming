/*
 * Compute the volume of a sphere
 */
#include <stdio.h>

#define PI 3.14
#define VOL (4.0f / 3.0f)

int main(void)
{
	float radius, volume;

	printf("Enter the radious of the sphere: ");
	scanf("%f", &radius);

	volume = (VOL * PI) * (radius * radius * radius);

	printf("Volume: %.2f\n", volume);

	return 0;
}
