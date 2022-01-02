/*
 * Checks which number is largest and smallest from four numbers
 */
#include <stdio.h>

int main(void)
{
	int a[4];
	int large = 0;
        int small = 100000;

	printf("Enter four numbers: ");
	scanf("%d %d %d %d", &a[0], &a[1], &a[2], &a[3]);

	for (int i = 0; i < 4; i++){
		if (a[i] < small){
			small = a[i];
		}
		else if (a[i] > large){
			large = a[i];
		}
	}

	printf("Largest: %d\n", large);
	printf("Smallest: %d\n", small);

	return 0;
}

