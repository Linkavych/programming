#include <stdio.h>

int main(void)
{
	int big, small;
	int a[4];

	printf("Enter four integers: ");
	scanf("%d%d%d%d", &a[0], &a[1], &a[2], &a[3]);

	big = a[0];
	small= a[0];

	for (int i = 0; i < 4; i++)
	{
		if (a[i] < small)
			small = a[i];
		if (a[i] > big)
			big = a[i];
	}
	printf("Largest: %d\n", big);
	printf("Smallest: %d\n", small);

	return 0;
}


