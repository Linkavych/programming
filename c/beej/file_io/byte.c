// Writing a sequence of bytes to a file
#include <stdio.h>

int main(void){

	FILE *fp;
	unsigned char bytes[] = {5, 37, 0, 88, 255, 12};

	fp = fopen("output.bin", "wb");

	// Cal to fwrite()
	// Args:
	// 	- Pointer to data to write
	// 	- Size of each piece of data
	// 	- Count of each piece of data
	// 	- FILE*
	
	fwrite(bytes, sizeof(char), sizeof bytes, fp);

	fclose(fp);
}

