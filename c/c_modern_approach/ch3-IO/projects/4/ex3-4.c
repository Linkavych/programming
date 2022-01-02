#include <stdio.h>

int main(void)
{
	int pre, mid, last;

	printf("Enter phone number [(xxx) xxx-xxxx)]: ");
	scanf("(%d) %d-%d)", &pre, &mid, &last);

	printf("You entered: %d.%d.%d\n", pre, mid, last);

	return 0;
}
