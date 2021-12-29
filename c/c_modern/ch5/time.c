/*
 * Display 24 hour time as 12 hour time
 */
#include <stdio.h>

int main(void)
{
	int pre, post;

	printf("Enter a 24-hour time (hh:mm): ");
	scanf("%2d:%2d", &pre, &post);

	printf("12-hour time: ");

	if (pre > 12 && pre < 24) {
		printf("%d:%.2d PM\n", (pre - 12), post);
	}
	else if (pre == 24){
		printf("00:%.2d\n", post);
	}
	else if (pre < 12){
		printf("%d:%.2d AM\n", pre, post);
	}
	else
		printf("%d:%.2d PM\n", pre, post);

	return 0;
}
		
