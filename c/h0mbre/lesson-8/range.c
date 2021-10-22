/*
 * Ask the user for a number between 1-500 and then display the range it is from
 * 1-100
 * 101-200
 * 201-300
 * 301-400
 * 401-500
 */
#include <stdio.h>
#include <stdlib.h>

int main(void){

	int num;

	printf("Enter a number between 1 and 500: ");
	scanf("%d", &num);

	switch(num) {

		case 1 ... 100:
			printf("Your number is between 1 and 100.\n");
			break;

		case 101 ... 200:
			printf("Your number is between 101 and 200.\n");
			break;

		case 201 ... 300:
			printf("Your number is between 201 and 300.\n");
			break;

		case 301 ... 400:
			printf("Your number is between 301 and 400.\n");
			break;

		case 401 ... 500:
			printf("Your number is between 401 and 500.\n");
			break;

		default:
			printf("That is not a valid number.\n");
			exit(EXIT_FAILURE);

	}
	return 0;
}

