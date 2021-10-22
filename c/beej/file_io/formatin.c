// Taking in formatted input
#include <stdio.h>

int main(void){

	FILE *fp;
	char name[1024];
	float length;
	int mass;

	fp = fopen("whales.txt", "r");

	while (fscanf(fp, "%s %f %d", name, &length, &mass) != EOF)
		printf("%s whale, %d tons, %.2f meters\n", name, mass, length);

	fclose(fp);
}

