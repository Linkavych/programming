/*
 * Create a program that prompts the user to input scoring totals for 5 players
 * during 4 basketball games. The program will track which player had the highest
 * scoring average over the four games and print the results.
 *
 * Use a two-dimensional array and nested for loops. The outer-most for loop will
 * iterate on a per game basis gathering scores for the inner-most for loop iterating
 * through players. Use this same model to create arrays to store total scores and
 * to calculate averages.
 */
#include <stdio.h>
#include <stdlib.h>

int main(void) {
	const int games = 4;
	const int players = 5;

	int scores[4][5];
	int totals[5];
	int highest_total;

	//counters
	int game_count, player_count;

	//start the loops
	for(game_count = 0; game_count < games; game_count++)
	{
		printf("Game count: %d\n", (game_count + 1));

		//inner loop begins
		for(player_count = 0; player_count < players; player_count++)
		{
			printf("Enter the score for Player#%d: ", (player_count + 1));
			scanf("%d", &scores[game_count][player_count]);
		}
	}

	// create the point totals
	for(player_count = 0; player_count < players; player_count++)
	{
		int player_total = 0;
		for (game_count = 0; game_count < games; game_count++)
		{
			player_total += scores[game_count][player_count];
		}
		totals[player_count] = player_total;
	}

	// create the highest total
	highest_total = 0;
	int player_id;
	for (player_count = 0; player_count < players; player_count++)
	{
		if (totals[player_count] > highest_total)
		{
			highest_total = totals[player_count];
			player_id = (player_count + 1);
		}
	}

	float ppg = (float)(highest_total / 4);

	printf("Player #%d had the highest scoring average at %.2f ppg.\n", player_id, ppg);

	return 0;
}

