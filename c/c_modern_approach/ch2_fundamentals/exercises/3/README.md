# Exercise 3

Condense the `dweight.c` program by replacing the assignments to height, length, and width with
initializers and (2) removing the weight variable, instead calculating (volume + 165) / 166
within the last printf.

```c
/*
 * Compute the dimensional weight of a 12" x 10" x 8" box
 */
#include <stdio.h>

int main(void)
{
	int height = 8;
	int width = 10;
	int length = 12;
	int volume;

	volume = height * length * width;

	printf("Dimensions: %dx%dx%dx\n", length, width, height);
	printf("Volume: %d\n", volume);
	printf("Dimensional Weight: %d\n", (volume + 165) / 166);

	return 0;
}
```
