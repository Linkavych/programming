/*
 * Computing the dimensional weight of a 12" x 10" x 8" box
 */
#include <stdio.h>

int main(void)
{
	int height = 8;
	int width = 10;
	int length = 12;
        int volume = height * length * width;

	printf("Dimensions: %dx%dx%d\n", length, width, height);
	printf("Volume (cu in): %d\n", volume);
	printf("Dimensional weight (lbs): %d\n", (volume + 165) / 166);

	return 0;
}
