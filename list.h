#pragma once

#define IS_EMPTY(ptr) (!(ptr))


typedef struct node {
	int element;
	struct node* next;
} Node;

typedef struct list {
	int size;
	struct node* starter;
} List;

void init(List* list);
Node* newNode(int data);
void addNode(List* list, int data);
void printList(List* list);
