// Passing a single dimensional array to a function
#include <stdio.h>

//passing a pointer to the first element
// This is the most common format for passing an array
void times2(int *a, int len){
	for (int i = 0; i < len; i++)
		printf("%d\n", a[i] * 2);
}

// Same thing, but with array notation
void times3(int a[], int len){
	for (int i = 0; i < len; i++)
		printf("%d\n", a[i] * 3);
}

// Same thing, but now with size
void times4(int a[5], int len){
	for (int i = 0; i < len; i++)
		printf("%d\n", a[i] * 4);
}

int main(void){

	int x[5] = {11, 22, 33, 44, 55};

	times2(x, 5);
	times3(x, 5);
	times4(x, 5);

}


