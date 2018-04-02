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
	return node; //�ּҸ� ��´�.
}

void addNode(List* list, int data) {
	//���ο� ���� �Լ� ȣ�⵿�� ����� �ӽ� �׸��� ����.
	Node* temp = (Node*)malloc(sizeof(Node));
	Node* node = newNode(data);

	//starter�� ����Ű�� ��带 �׸��� ���, �� ���� starter�� ����
	temp->next = list->starter;
	list->starter = node;
	node->next = temp->next;
	list->size++;
	free(temp);
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
		printf("�����Ͱ� ���� ���� ����� ������ �� �����ϴ�.\n");
	}
	else {
		printf("[00]: %d �� ���� �մϴ�.\n", list->starter->element);
		Node* temp = (Node*)malloc(sizeof(Node));
		temp->next = list->starter->next;
		free(list->starter);
		list->starter = temp->next;
		free(temp);
		printf("���� �Ǿ����ϴ�.\n");
	}
}
