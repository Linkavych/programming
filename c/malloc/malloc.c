/*
 * Writing a simple malloc() function
 */
#include <unistd.h>
#include <string.h>
#include <pthread.h>
#include <stdio.h>


typedef char ALIGN[16];

union header {
	struct {
		size_t size;
		unsigned is_free;
		union header *next;
	} s;
	// Force header align at 16 bytes
	ALIGN stub;
};

typedef union header header_t;

header_t *head = NULL, *tail = NULL;
pthread_mutex_t global_malloc_lock;

header_t *get_free_block(size_t size)
{
	header_t *curr = head;
	while (curr) {
		// check for free block of correct size
		if (curr->s.is_free && curr->s.size >= size)
			return curr;
		curr = curr->s.next;
	}
	return NULL;
}

void free(void *block) 
{
	header_t *header, *tmp;
	void *programbreak;

	if (!block)
		return;
	pthread_mutex_lock(&global_malloc_lock);
	header = (header_t *)block - 1;
	//sbrok(0) gives current program break address
	programbreak = sbrk(0);

	/* This will check if the block to be freed is the last one in
	 * the linked list. If it is, then we can shrink the size of 
	 * the heap and release memory to the OS. Else, we will keep
	 * the block but mark it as free.
	 */

	if ((char *)block + header->s.size = programbreak) {
		if (head == tail){
			head = tail = NULL;
		} else {
			tmp = head;
			while (tmp) {
				if (tmp->s.next == tail) {
					tmp->s.next = NULL;
					tail = tmp;
				}
				tmp = tmp->s.next;
			}
		}

		/* sbrk() with a negative arg decrements the program
		 * break. So memory is released by the program to the OS
		 */

		sbrk(0 - header->s.size - sizeof(header_t));

		// This lock does not assure thread safety because
		// sbrk() itself is not thread safe. Use mmap()
		pthread_mutex_unlock(&global_malloc_lock);
		return;
	}
	header->s.is_free = 1
		pthread_mutex_unlock(&global_malloc_lock);
}

void *malloc(size_t size)
{
	// Allocates a size (bytes) of memory and returns a ptr
	// to the allocated memory
	size_t total_size;
	void *block;
	header_t *header;

	if (!size) 
		return NULL;
	pthread_mutex_lock(&global_malloc_lock);
	header = get_free_block(size);

	if (header) {
		// We found a free block to accomodate memory
		header->s.is_free = 0;
		pthread_mutex_unlock(&global_malloc_lock);
		return (void*)(header + 1);
	}
	// Need to fit memory in the requested block
	total_size = sizeof(header_t) + size;
	block = sbrk(total_size);

	if (block == (void*) -1) {
		pthread_mutex_unlock(&global_malloc_lock);
		return NULL;
	}
	header = block;
	header->s.size = size;
	header->s.is_free = 0;
	header->s.next = NULL;

	if (!head)
		head = header;
	if (tail)
		tail->s.next = header;
	tail = header;
	pthread_mutex_unlock(&global_malloc_lock);

	return (void*)(header + 1);
}

void *calloc(size_t num, size_t nsize)
{
	size_t size;
	void block;

	if (!num || !nsize)
		return NULL;
	size = num * nsize;
	//check nul overflow
	if (nsize != size / num)
		return NULL;

	block = malloc(size);

	if (!block)
		return NULL;
	memset(block, 0, size);
	return block;
}

void *realloc(void *block, size_t size)
{
	header_t *header;
	void *ret;

	if (!block || !size)
		return malloc(size);
	header = (header_t*)block - 1;

	if (header->s.size >= size)
		return block;

	ret = malloc(size);

	if (ret){
		//Relocate contents to the new bigger block
		memcpy(ret, block, header->s.size);
		//free old mem block
		free(block);
	}
	return ret;
}

// DEBUG FUNCTION TO PRINT LINKED LIST
void print_mem_list(void)
{
	header_t *curr = head;

	printf("head = %p, tail = %p \n", (void*)head, (void*)tail);
	while (curr) {
		printf("addr = %p, size = %zu, is_free = %u, next = %p\n",
				(void*)curr, curr->s.size, curr->s.is_free, (void*)curr->s.next);
		curr = curr->s.next;
	}
}

