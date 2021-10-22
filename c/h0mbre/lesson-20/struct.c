/*
 * Create/define a structure outside of main() that include an int, char, float members. 
 * Inside of main(), declare values for those members and print their values to the terminal.
 */
#include <stdio.h>
#include <stdlib.h>

struct test {
	int num;
	char alpha;
	float x;
};

int main(void){
	struct test Test1;

	Test1.num = 2;
	Test1.alpha = 'A';
	Test1.x = 3.14;

	printf("The structure Test1 has the following values: %d %c %f\n", 
			Test1.num, Test1.alpha, Test1.x);

	return 0;
}

	
