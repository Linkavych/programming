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


	while (1){
		printf("Enter second date (mm/dd/yy): ");
	        scanf("%2d/%2d/%2d", &m2, &d2, &y2);

		if (d2 == 0 && m2 == 0 && y2 == 0)
			break;
		if (y2 < y1 || (y1 == y2 && m2 < m1) ||
				(y1 == y2 && m2 == m1 && d2 < d1)){
			d1 = d2;
			m1 = m2;
			y1 = y2;
		}
	}
	printf("The earliest date is: %d/%d/%.2d\n", m1, d1, y1);


	return 0;
}

			



