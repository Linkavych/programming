#include <stdio.h>

#define PI 3.14f

int main(void)
{
	int r = 10;
	float vol;

	vol = ((4.0f / 3.0f) * r) * (PI * PI * PI);

	printf("Volume of a 10-meter radius sphere: %.2f\n", vol);

	return 0;
}

