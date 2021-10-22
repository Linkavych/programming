/*
 * Prompt the user for a number of seconds. Take user's input
 * and convert the number of seconds into its duration in hours, minutes,
 * and remaining seconds.
 *
 * Extra: Do not print decimal places.
 */
#include <stdio.h>
#include <stdlib.h>

int main(void) {

	float seconds;
	float hours;
	float minutes;
	float remain;

	printf("Enter the number of seconds: ");
	scanf("%f", &seconds);

	hours = (int)seconds / 3600;
	minutes = (int)((seconds - (hours * 3600)) / 60);
	remain = (seconds - (hours * 3600) - (minutes * 60));

	printf("Hours: %.0f, Minutes: %.0f, Seconds: %.0f\n", hours, minutes, remain);

	return 0;
}

	
