/*
 * Comput the dimensional weight of a 12" x 10" x 8" box
 */
#include <stdio.h>

int main(void)
{
	int height;
	int width;
	int length;
	int volume, weight;

	printf("Enter the height of the box: ");
	scanf("%d", &height);
	printf("Enter the length of the box: ");
	scanf("%d", &length);
	printf("Enter the width of the box: ");
	scanf("%d", &width);
	
	volume = height * length * width;
	weight = (volume + 165) / 166;

	printf("Dimensions: %dx%dx%dx\n", length, width, height);
	printf("Volume: %d\n", volume);
	printf("Dimensional Weight: %d\n", weight);

	return 0;
}

