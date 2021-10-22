// Using aligned_alloc() to strictly align memory allocations
// Most commonly used with embedded systems
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(void){

	// Allocate 256 bytes on a 64byte boundary
	char *p = aligned_alloc(64, 256); //256 == 64 * 4

	// copy in a string and print
	strcpy(p, "Hello, world!");
	printf("%s\n", p);

	// free memory
	free(p);
}
/*
 * An example of manually reallocating space for use with aligned_alloc()
 * because realloc() will not work here
 *
 *
 * void *aligned_realloc(void *ptr, size_t old_size, size_t alignment, size_t size)
 * {
 * 	char *new_ptr = aligned_alloc(alignment, size);
 *
 * 	if (new_ptr == NULL)
 * 		return NULL;
 *
 * 	size_t copy_size = old_size < size? old_size: size;	// get min
 *
 * 	if (ptr != NULL)
 * 		memcpy(new_ptr, ptr, copy_size);
 *
 * 	free(ptr);
 *
 * 	return new_ptr;
 * }
 *
 * Preferabbly, avoid the need to reallocate aligned data
 */

