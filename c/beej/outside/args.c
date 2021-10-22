//interacting with the command line and receiving arguments
//
#include <stdio.h>

int main(int argc, char *argv[]) {

	for (int i = 0; i < argc; i++)
		printf("arg %d: %s\n", i, argv[i]);
}

