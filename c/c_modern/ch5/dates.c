/*
 * Compare two dates and see which is earlier
 */
#include <stdio.h>

int main(void)
{
	int m1, d1, y1;
	int m2, d2, y2;

	printf("Enter first date (mm/dd/yy): ");
	scanf("%2d/%2d/%2d", &m1, &d1, &y1);
	printf("Enter second date (mm/dd/yy): ");
	scanf("%2d/%2d/%2d", &m2, &d2, &y2);

	if (y1 < y2)
		printf("%d/%d/%d is ealier than %d/%d/%d\n", m1, d1, y1, m2, d2, y2);
	else if (y2 < y1)
		printf("%d/%d/%d is ealier than %d/%d/%d\n", m2, d2, y2, m1, d1, y1);
	else if (y1 == y2){
		if (m1 < m2)
		    printf("%d/%d/%d is ealier than %d/%d/%d\n", m1, d1, y1, m2, d2, y2);
		else if (m2 < m1)
		    printf("%d/%d/%d is ealier than %d/%d/%d\n", m2, d2, y2, m1, d1, y1);
		else if (m1 == m2){
			if (d1 < d2)
		            printf("%d/%d/%d is ealier than %d/%d/%d\n", m1, d1, y1, m2, d2, y2);
			else if (d2 < d1)
		            printf("%d/%d/%d is ealier than %d/%d/%d\n", m2, d2, y2, m1, d1, y1);
		}
	}
	else
		printf("Dates are the same!\n");

	return 0;
}

			



