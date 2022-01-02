/*
 * Prompt the user to input a phone numer (xxx) xxx-xxx
 * Output: xxx.xxx.xxxx
 */
#include <stdio.h>

int main(void)
{
	int area, prefix, num;

	printf("Enter a phone number [(xxx) xxx-xxxx]: ");
	scanf("(%d) %d-%d", &area, &prefix, &num);

	printf("You entered: %d.%d.%d\n", area, prefix, num);

	return 0;
}
