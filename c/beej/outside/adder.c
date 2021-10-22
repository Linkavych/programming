// An addition program
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char **argv) {

	int total = 0;

	for (int i = 0; i < argc; i++){
		int value = strtol(argv[i], NULL, 10);
		total += value;
	}
	printf("%d\n", total);
}
