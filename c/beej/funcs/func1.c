#include <stdio.h>

int plus_one(int n){
	return n + 1;
}

int main(void){
	int i = 10, j;

	j = plus_one(i);

	printf("i + 1 = %d\n", j);
}
