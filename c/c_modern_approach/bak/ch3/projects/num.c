/*
 * Prompt user to enter numbers 1 through 16 in any order
 * Ouput by groups of 4
 * Sums by row, col, and diagonal
 */
#include <stdio.h>

int main(void)
{
	int a,b,c,d,e,f,g,h,i,j,k,l,m,n,o,p;

	printf("Enter the numbers 1 through 16 in any order: ");
	scanf("%d%d%d%d%d%d%d%d%d%d%d%d%d%d%d%d", &a,&b,&c,&d,&e,&f,&g,&h,&i,&j,&k,&l,&m,&n,&o,&p);

	printf("%d %d %d %d\n", a,b,c,d);
	printf("%d %d %d %d\n", e,f,g,h);
	printf("%d %d %d %d\n", i,j,k,l);
	printf("%d %d %d %d\n", m,n,o,p);

	printf("Row Totals: %d %d %d %d\n", (a+b+c+d), (e+f+g+h), (i+j+k+l), (m+n+o+p));
	printf("Column Totals: %d %d %d %d\n", (a+e+i+m), (b+f+j+n),(c+g+k+o), (d+h+l+p));
	printf("Diagonal Totals: %d %d\n", (a+f+k+p), (d+g+j+m));

	return 0;
}
