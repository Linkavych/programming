//An example of using a struct to create a linked list
#include <stdio.h>
#include <stdlib.h>

struct node {
	int data;
	struct node *next;
};

int main(void) {

	struct node *head;

	//Hacky linked list
	head = malloc(sizeof(struct node));
	head->data = 11;
	head->next = malloc(sizeof(struct node));
	head->next->data = 22;
	head->next->next = malloc(sizeof(struct node));
	head->next->next->data = 33;
	head->next->next->next = NULL;

	// Traverse the linked list
	for (struct node *cur = head; cur != NULL; cur = cur->next) {
		printf("%d\n", cur->data);
	}
}

