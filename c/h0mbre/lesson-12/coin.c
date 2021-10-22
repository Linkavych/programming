/*
 * Prompt the user for a number of coin flips and then simulate that number of coin
 * flips and print the results to the terminal.
 */
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main(void) {

	int h,ta,x;
	time_t t;

	srand((unsigned) time(&t));

	printf("Enter the number of flips: ");
	scanf("%d", &x);

	for(int i = 0; i < x; i++){
		int flip = (rand() % 2);
		if(flip == 0){
			h++;
		} else {
			ta++;
		}
	}
	printf("The number of flips was: %d\n", x);
	printf("The number of HEADS flips: %d\n", h);
	printf("The number of TAILS flips: %d\n", ta);

	return 0;
}
	
