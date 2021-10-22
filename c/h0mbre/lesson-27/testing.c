#include <stdio.h>
#include <unistd.h>

int main(void) {

	write(1, "Hello, World!", 13);

	puts("");

	return 0;
}
