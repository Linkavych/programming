// C will not stop you from trying to get an object beyond the bounds of the array
#include <stdio.h>

int main(void){

	int i;
	int a[5] = {22, 37, 3490, 18, 95};

	for (i = 0; i < 10; i++){
		printf("%d\n", a[i]);
	}
}

