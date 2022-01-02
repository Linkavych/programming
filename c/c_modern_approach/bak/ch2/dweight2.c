/*
 * Computing the dimensional weight of a 12" x 10" x 8" box
 */
#include <stdio.h>

#define INCHES_PER_POUND 166

int main(void)
{
	int height, width, volume, weight, length;

	printf("Enter the height of box: ");
	scanf("%d", &height);
	printf("Enter the length of box: ");
	scanf("%d", &length);
	printf("Enter width of box: ");
	scanf("%d", &width);

	volume = length * width * height;
	weight = (volume + INCHES_PER_POUND - 1) / INCHES_PER_POUND;


	printf("Dimensions: %dx%dx%d\n", length, width, height);
	printf("Volume (cu in): %d\n", volume);
	printf("Dimensional weight (lbs): %d\n", weight);

	return 0;
}
