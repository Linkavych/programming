// Making a struct and passing it as a pointer in a function
#include <stdio.h>

struct car {
	char *name;
	float price;
	int speed;
};

void set_price(struct car *c, float new_price);

int main(void){
	struct car saturn = {.speed=175, .name="Saturn SL/2"};

	//Pass the struct pointer to a function
	set_price(&saturn, 800.00);

	printf("Name: %s\n", saturn.name);
	printf("Price: %f\n", saturn.price);
	printf("Speed: %d\n", saturn.speed);

}

void set_price(struct car *c, float new_price){
	// This won't work for setting the price
	// c.price = new_price;
	// The struct needs to be dereferenced for the above to work
	
	(*c).price = new_price; // this will work, but is not the best way in C
}
