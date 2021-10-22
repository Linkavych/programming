/*
 * Initialize and assign a vlue to an interger, float, and char variable.
 * Print each to the screen on a new line with a sentence describing
 * the variable data type.
 */
#include <stdio.h>
#include <stdlib.h>

int main(void){

	int num;
	float numnum;
	char single;

	num = 2;
	numnum = 3.14;
	single = 'A';

	printf("%d is an interger!\n", num);
	printf("%.2f is a float!\n", numnum);
	printf("%c is a char!\n", single);

	return 0;
}

