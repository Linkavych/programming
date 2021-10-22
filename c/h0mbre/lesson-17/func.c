/*
 * Declare a function that prints Hello, World! to the terminal and then call
 * that function from inside the main() function.
 *
 * Extra: use a function prototype to establish the function and put the function
 * belof main()
 */
#include <stdio.h>
#include <stdlib.h>

void hello(void);

int main(void){
	hello();
	return 0;
}

void hello(void){
	printf("Hello, world!\n");
}
