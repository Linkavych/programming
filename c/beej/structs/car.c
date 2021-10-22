// A simple struct
#include <stdio.h>


struct car {
	char *name;
	float price;
	int speed;
};

struct car saturn = {.name="Saturn SL/2", .price=15999.99, .speed=175};
struct car chevy;

int main (void){


	chevy.name = "Silverado 1500";
	chevy.price = 20000.00;
	chevy.speed = 125;
	
	
	printf("Name: %s\n", saturn.name);
	printf("Price (USD): %f\n", saturn.price);
	printf("Top speed: %d\n", saturn.speed);

	printf("Name: %s\n", chevy.name);
	printf("Price (USD): %f\n", chevy.price);
	printf("Top Speed: %d\n", chevy.speed);
}
