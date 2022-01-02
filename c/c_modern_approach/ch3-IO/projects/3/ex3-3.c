#include <stdio.h>

int main(void) 
{
	int gsi, group, pub, item, check;

	printf("Enter ISBN: ");
	scanf("%d-%d-%d-%d-%d", &gsi, &group, &pub, &item, &check);

	printf("GS1 prefix: %d\n", gsi);
	printf("Group Identifier: %d\n", group);
	printf("Publisher code: %d\n", pub);
	printf("Item number: %d\n", item);
	printf("Check digit: %d\n", check);

	return 0;
}
