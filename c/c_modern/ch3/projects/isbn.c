/*
 * Write a program that breaks down the ISBN entered by the user
 * GS1 Prefix
 * Group ID
 * Publisher Code
 * Item Number
 * Check Digit
 */
#include <stdio.h>

int main(void)
{
	int prefix, id, pub, item, check;

	printf("Enter the ISBN: ");
	scanf("%d-%d-%d-%d-%d", &prefix, &id, &pub, &item, &check);

	printf("GS1 Prefix: %d\n", prefix);
	printf("Group ID: %d\n", id);
	printf("Publisher: %d\n", pub);
	printf("Item #: %d\n", item);
	printf("Check Digit: %d\n", check);

	return 0;
}
