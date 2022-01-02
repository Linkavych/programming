#include <stdio.h>
#include <ctype.h>

int main(void)
{
	int rows[5][5] = {{0,0}};
	int i,n,tmp;
	float avg;

	for (i=0;i < 5; i++)
	{
		printf("Enter student %d quiz scores: ", i + 1);

		for (n=0; n < 5; n++)
		{
			scanf("%d", &rows[i][n]);
		}
	}
	printf("Student totals: ");

	for (i = 0; i < 5; i++)
	{
		tmp = 0;

		for (n = 0; n < 5; n++)
		{
			tmp += rows[i][n];
		}
		printf("%d ", tmp);
	}
	printf("\n");
	printf("Student averages: ");

	for (i = 0; i < 5; i++)
	{
		tmp = 0;

		for (n = 0; n < 5; n++)
		{
			tmp += rows[i][n];
		}
		avg = (float)tmp /5;
		printf("%.2f ", avg);
	}
	printf("\n");

	printf("Column totals: ");
	for (i = 0; i < 5; i++)
	{
		tmp = 0;

		for (n = 0; n < 5; n++)
		{
			tmp += rows[n][i];
		}
		printf("%d ", tmp);
	}
	printf("\n");

	return 0;
}
