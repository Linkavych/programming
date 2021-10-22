// Manipulating pointers
#include <stdio.h>

int a[] = {11, 22, 33, 44, 55, 66, 77, 9999};
int *p = &a[0]; // p points to 11 in memory

int main(void){

	// iterate through memory until we hit a sentinel value
	while (*p != 9999){
		printf("%d\n", *p);
		p++;
	}
}
