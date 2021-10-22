// Exploring qsort() functionality and void *s
//
#include <stdio.h>
#include <stdlib.h>

// Type of struct to sort
struct animal {
	char *name;
	int leg_count;
};

// Comparison function called by qsort to help it determine
// what to sort by. Used here to sort an array of struct animals
// by leg_count
int compar(const void *elem1, const void *elem2)
{
	const struct animal *animal1 = elem1;
	const struct animal *animal2 = elem2;

	// Return <0 = 0 or > 0 depending on sort
	// Sort by ascending by leg_count
	// So return the diff in leg_counts
	return animal1->leg_count - animal2->leg_count;
}

int main(void)
{
	// Build an array of four structs with different characteristics
	struct animal a[4] = {
		{.name="Dog", .leg_count=4},
		{.name="Monkey", .leg_count=2},
		{.name="Spider", .leg_count=8},
		{.name="Snake", .leg_count=0}
	};

	// Call qsort to sort the array. qsort needs to be told what to sort that data by
	// which we handle with the compar(). 
	//
	// This call is saying qsort array a, which has 4 elements, and each element is
	// sizeof(struct animal) bytes big, and this is the function that will cmpare
	// any two elements
	qsort(a, 4, sizeof(struct animal), compar);

	//Print everything out
	for (int i = 0; i < 4; i++) {
		printf("%d: %s\n", a[i].leg_count, a[i].name);
	}
}


// As long as qsort is given a function to compare two items from an array, it can sort anything
