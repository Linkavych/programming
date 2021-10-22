/*
 * Create a program that takes input for five player's point totals
 * and games player totals and calculates the scoring averages for
 * each player. Create a struct with members for total points and games
 * played. Create an array of structs that is five elements deep (one per player)
 * and loop through the array to fill with point totals and games played.
 */
#include <stdio.h>
#include <stdlib.h>

struct data {
	int points;
	int games;
};

int main(void){

	struct data players[5];
	int i;

	for (i = 0; i < 5; i++) {

		printf("Enter Player %d's point total: ", i+1);
		scanf("%d", &players[i].points);

		printf("Enter Player %d's games played: ", i+1);
		scanf("%d", &players[i].games);

	}
	puts("");

	for (i = 0; i < 5; i++) {

		printf("Player %d's scoring average was %.2f ppg.\n", i + 1, (float)(players[i].points / players[i].games));
	}

	return 0;
}



