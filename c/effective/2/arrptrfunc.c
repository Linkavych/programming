// Creating an array of pointers to functions and calling the functions
// based on the index
#include <stdio.h>

int sum(int a, int b);
int sub(int a, int b);
int mult(int a, int b);
int div(int a, int b);

int (*p[4])(int x, int y);

int main (void) {

	int result;
	int c, j, op;

	p[0] = sum;
	p[1] = sub;
	p[2] = mult;
	p[3] = div;

	c = 6;
	j = 2;

	for (int i = 0; i < 4; i++)
		printf("%d\n", (p[i](c, j)));

	return 0;
}

int sum(int a, int b){
	return a + b;
}

int sub(int a, int b) {
	return a - b;
}

int mult(int a, int b) {
	return a * b;
}

int div(int a, int b) {
	return a / b;
}
