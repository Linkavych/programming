// Reading a text file
#include <stdio.h>

int main(void){

	FILE *fp;

	fp = fopen("test.txt", "r");

	char c = fgetc(fp);
	printf("%c\n", c);

	fclose(fp);
}

