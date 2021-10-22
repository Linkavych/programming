// Writing to a text file
#include <stdio.h>

int main(void){

	FILE *fp;
	int x = 32;

	// If the below were fp = stdout 
	// it would output to the screen
	fp = fopen("output.txt", "w");

	fputc('B', fp);
	fputc('\n', fp);
	fprintf(fp, "x = %d\n", x);
	fputs("Hello, world!\n", fp);

	fclose(fp);
}

