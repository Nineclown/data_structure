#include "list.h"
#include <stdio.h>
#include <stdlib.h>

void init(List* list) {
	list->size = 0;
	list->starter = NULL;
}

Node* newNode(int data) {
	Node* node;
	node = (Node*)malloc(sizeof(Node));
	node->element = data;
	node->next = NULL;
	return node; //주소를 뱉는다.
}

void addNode(List* list, int data, int way) {
	//새로운 노드와 함수 호출동안 사용할 임시 그릇을 생성.
	Node* node = newNode(data);

	Node* temp;
	temp = list->starter;

	if (1 == way) {
		//starter가 가리키던 노드를 그릇에 담고, 새 노드와 starter를 연결
		if (NULL == temp) {
			list->starter = node;
			list->size++;
		}
		else {
			list->starter = node;
			node->next = temp;
			list->size++;
		}
	}
	else if (-1 == way) {
		if (NULL == temp) {
			list->starter = node;
			list->size++;
		}
		else {
			while (NULL != temp->next) {
				temp = temp->next;
			}
			temp->next = node;
			list->size++;
		}
	}
	
}


void printList(List* list) {
	Node* i;
	int count = 0;
	printf("= 			list...			  =\n");
	for (i = list->starter; i != NULL; i = i->next) {
		if (0 == count % 4)
			printf("\n");
		printf(" [%02d]: %3d ", count++, i->element);
	}
	printf("\n");
}


void removeNode(List* list) {
	if (IS_EMPTY(list->starter)) {
		printf("데이터가 없어 삭제 명령을 수행할 수 없습니다.\n");
	}
	else {
		printf("[00]: %d 를 삭제 합니다.\n", list->starter->element);
		Node* temp;
		temp = list->starter->next;
		free(list->starter);
		list->starter = temp;
		printf("삭제 되었습니다.\n");
	}
}
