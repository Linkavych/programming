// Using a switch statement
#include <stdio.h>

int main(void){

	int goats;

	printf("Enter the number of goats: ");
	scanf("%d", &goats); 			// reads in the # of goats from user

	switch (goats){
		case 0:
		  printf("No goats!\n");
      		  break;

		case 1:
		  printf("One goat!\n");
		  break;

		case 2:
		  printf("Two whole goats!!\n");
		  break;

		case 3: 
		  printf("That's three goats!\n");
		  break;

		default:
		  printf("That's more goats than I can imagine!\n");
		  break;
	}
}
