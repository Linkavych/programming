// A copy of the memcpy() function to show void *
#include <stdio.h>

void *my_memcpy(void *dest, void *src, int byte_count)
{
	// Convert void* to char*
	char *s = src, *d = dest;

	// Dereference and copy
	while (byte_count--){
		*d++ = *s++;
	}

	// These functions usually return the destination in case
	// it is useful to the function
	return dest;
}

// This technique can be used to iterate over the bytes of ANY OBJECT in C
