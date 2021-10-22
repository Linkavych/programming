/*
 * Ask the user for test scores and then keep asking the user if they would like to continue
 * or end the program. Store all test scores and calculate the average that prints to the terminal.
 * Initialize the array to size of 10 and use a max count of 8.
 *
 * Print the average of the test scores to the second decimal place.
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define INITIAL_CAPACITY 3

int main(void){
	char answer[] = "y";

	//allocation of memory for three scores
	double *scores = malloc(INITIAL_CAPACITY * sizeof(double));

	// error check the allocation
	if (!scores){
		fprintf(stderr, "Allocation error.\n");
		return 1;
	}

	int capacity = INITIAL_CAPACITY;

	int i;

	for(i = 0; strcmp(answer, "y") == 0; ++i) {
		if (i == capacity) {
			capacity *= 2;
			scores = realloc(scores, capacity * sizeof(double));

			if(!scores){
				fprintf(stderr, "Allocation error.\n");
				return 1;
			}
		}

		printf("Enter a test score: ");
		scanf("%lf", &scores[i]);

		printf("Would you like to continue? y/n ");
		scanf("%s", &answer);
	}

	double sum = 0;

	for(int cnt = 0; cnt < i; cnt++){
		sum += scores[cnt];
	}

	printf("%.2f is the average.\n", sum / i);

	free(scores);

	return 0;
}
