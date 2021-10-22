// Passing a multidimensional array to a function
// C needs to know the dimensions of the array being passed in this case
#include <stdio.h>

void print_2d_array(int a[2][3]){

	for (int row = 0; row < 2; row++){
		for (int col = 0; col < 3; col++)
			printf("%d ", a[row][col]);
		printf("\n");
	}
}

int main(void){

	int x[2][3] = {
		{1, 2, 3},
		{4, 5, 6}
	};

	print_2d_array(x);
}


