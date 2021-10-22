// Demonstration of making a variable static
// Adding an retrieve function that returns the value of counter
#include <stdio.h>

void retrieve(unsigned int *p) {

	printf("Current counter: %d\n", *p);

}

void increment(void) {

	static unsigned int counter = 0;
	
	retrieve(&counter);

	counter++;
	printf("%d\n", counter);
}

int main(void) {
	for (int i = 0; i < 10; i++){
		increment();
	}
	return 0;
}
