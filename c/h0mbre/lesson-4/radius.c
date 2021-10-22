/*
 * Prompt the user to input the length of a radius and then print
 * the area of the circle to the terminal.
 *
 * Extra: Use #define to assign a value to PIE of 3.14
 */
#include <stdio.h>
#include <stdlib.h>

#define PIE 3.14

int main(void) {

	float length;

	puts("Enter the length of the radius: ");
	scanf("%f", &length);

	float area;

	area = PIE * (length * length);

	printf("The area is: %.2f\n", area);

	return 0;
}
