/*
 * Comput the dimensional weight of a 12" x 10" x 8" box
 */
#include <stdio.h>

int main(void)
{
	int height = 8;
	int width = 10;
	int length = 12;
	int volume, weight;

	volume = height * length * width;
	weight = (volume + 165) / 166;

	printf("Dimensions: %dx%dx%dx\n", length, width, height);
	printf("Volume: %d\n", volume);
	printf("Dimensional Weight: %d\n", weight);

	return 0;
}

