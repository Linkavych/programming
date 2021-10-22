// First for loop, simple
#include <stdio.h>
#include <stdlib.h>

int main (void){

	int r;

	do {
		r = rand() % 100; //get a random number between 0 and 99
		printf("%d\n", r);
	} while (r != 37);
}

