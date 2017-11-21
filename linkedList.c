#include <stdio.h>
#include <stdlib.h>

#define OKAY 1
#define MALLOCFAIL 2

typedef struct node
{
	// void *data; // like object type
	int data;
	struct node *prev;
	struct node *next;	

} NODE;

typedef struct
{	
	NODE *head;
	NODE *tail;
} LIST;

int addFront(LIST *list, int newData) {
	NODE *temp = malloc(sizeof(NODE));
	if (temp == NULL) {
		return MALLOCFAIL;
	}
	temp->next = list->head;
	temp->data = newData;
	if (list->head == NULL) {
		list->tail = temp;
	}
	list->head = temp;
	return OKAY;
}

void traverse(NODE *head) {
	printf("Traversing\n");
	while (head != NULL) {
		printf("head: %p head->data: %d head->next: %p \n",
			(void *)head, head->data, (void *)head->next);
	}
	printf("End Of Traversal\n");
}

void traverse(LIST list, void (*Fp)(void *)) {
	NODE *curr = list->head;
	while (curr != NULL) {
		fp(curr->data);
	}
	traverse(list, printPoint);
}

int main(int argc, char const *argv[])
{
	LIST myList = {NULL, NULL};
	// NODE *head = NULL;
	if (addFront(&myList, 7) == MALLOCFAIL) {
		printf("Malloc has failed. Go home.\n");
		exit(99);
	}
	head = addFront(head, 9);
	head = addFront(head, 22);
	traverse(head);
	return 0;
}





