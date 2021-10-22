#include <stdio.h>

//The do-while construct

int i = 10;

int main(void){
	do {
		printf("do-while: i is %d\n", i);
		i++;
	} while (i < 10);

	printf("Complete!\n");
}
