// Using EOF to read file streams
#include <stdio.h>

int main(void){

	FILE *fp;

	fp = fopen("test.txt", "r");
	char c;

	while ((c = fgetc(fp)) != EOF)
		printf("%c", c);

	fclose(fp);
}

