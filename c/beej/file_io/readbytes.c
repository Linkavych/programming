// Reading binary data from a file
#include <stdio.h>

int main(void){

	FILE *fp;
	unsigned char c;

	fp = fopen("output.bin", "rb");

	while (fread(&c, sizeof(char), 1, fp) > 0)
		printf("%d\n", c);
}

