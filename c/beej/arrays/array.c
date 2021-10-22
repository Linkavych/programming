// A simple array example
#include <stdio.h>

int main(void){

	int i;
	float f[4];

	f[0] = 3.14159;
	f[1] = 1.41421;
	f[2] = 1.61803;
	f[3] = 2.71828;

	for (i = 0; i < 4; i++){
		printf("%f\n", f[i]);
	}
}
