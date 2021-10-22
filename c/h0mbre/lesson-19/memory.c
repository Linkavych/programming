/*
 * Initialize a char pointer variable. Use malloc() to allocate memory for a char array by assigning
 * the result of malloc() to your pointer. Your program should check that the memory was indeed
 * allocated and if not, print an error message and exit with code 1. Make sure the allocation size
 * is a multiple of the char data type by using sizeof() so the code is portable. Dont forget to free()
 *
 * Print a success or failure message to the terminal
 */
#include <stdio.h>
#include <stdlib.h>

int main(void){

	char *ptr;

	ptr = malloc(sizeof(char)*10);
	if(ptr == NULL) {
		printf("Memory not allocated\n");
		exit(1);
	}
	else{
		printf("Memory successfully allocated!\n");
	}
	free(ptr);
	return 0;
}
