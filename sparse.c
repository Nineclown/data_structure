#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <Windows.h>
#include <time.h>
#include "sparse.h"

//	����Ʈ�� �����͸� �߰��ϴ� �Լ�. x, y ��ġ�� �ش��ϴ� value. ����Ʈ�� ������ġ, ������ġ�� ���ϴ� way.
void addData(Matrix* matrix, int x_data, int y_data, int value, int way) {
	Sparse* temp;
	Sparse* newdata;

	newdata = (Sparse*)malloc(sizeof(Sparse));  // �����͸� �Լ� ������ �����ϱ� ������
	newdata->x = x_data;						// �������� �Ҵ������ �Լ� ȣ���� ������
	newdata->y = y_data;						// ���� �ı����� �ʴ´�.
	newdata->value = value;
	newdata->next = NULL;

	temp = matrix->starter;

	//�����͸� ���ʿ� �߰��ϴ� ���.
	if (1 == way) {
		if (NULL == temp) {
			matrix->starter = newdata;  // matrix->starter ��� temp�� ���� ���� �޶���.
		}								// -> �� �ǹ̸� �� �����ؾ� �Ѵ�.
		else {
			matrix->starter = newdata;
			newdata->next = temp;
		}
	}
	//�����͸� ���ʿ� �߰��ϴ� ���.
	else if (-1 == way) {
		if (NULL == temp) {
			matrix->starter = newdata;
		}
		else {
			while (temp->next != NULL) {
				temp = temp->next;
			}
			temp->next = newdata;
		}
	}
}

// ��� ����� ����� �ִ� �Լ�.
int** createMatrix(int input) {
	int size = input;
	Sleep(1000);		// srand()�Լ��� �ð� ���� �������� ������ �����ϴµ�, 
	srand(time(NULL));	// �� ���� �ʹ�ª�Ƽ� ������ ��� �����ϰ� ������.
						// �׷��� ������ ���� �÷� �ִ� Sleep() ���.

	int **sparse_matrix;										// �������� �迭�� �Ҵ��ϱ� ������
	sparse_matrix = (int**)malloc(sizeof(int*) * size);			// �Լ� ȣ���� ����Ǿ� ������ �ı��Ǿ
	for (int i = 0; i < size; i++) {							// ������� �� ������ �����Ͱ� �����Ǿ� �ִ�.
		sparse_matrix[i] = (int*)malloc(sizeof(int*)* size);	// ��, return ������ sparse_matrix�� �Ѱ��ִµ�,
	}															// sparse_matrix�� ���� ���ÿ����̹Ƿ� �ı��� �ȴ�.																				
	for (int i = 0; i < size; i++) {							// ���������� sparse_matrix�� ���� �����ؼ� �Ѱ��ְ� �ȴ�.
		for (int j = 0; j < size; j++) {						// sparse_matrix�� ���� �������� ����Ű�� �ּ�.
			sparse_matrix[i][j] = rand() % 3;
			printf("matrix[%d][%d]: %d ", i, j, sparse_matrix[i][j]);
		}
		printf("\n");
	}
	printf("\n");
	return sparse_matrix;
}

// ��� ����� free��Ű�� �Լ�.
void freeMatrix(int** matrix, int size) {
	for (int i = 0; i < size; i++) {
		free(matrix[i]);
	}
	free(matrix);
}

// ��Ʈ����(��� ����� ��� ���鿡 ���� ����Ʈ)�� ����ϴ� �Լ�
void printMatrix(Matrix* matrix, int size) {
	Sparse* i;
	int temp = matrix->starter->x;						// �迭�� �ڸ����� ���߱� ���� x �ε����� ����� ����
	printf("\n");
	for (i = matrix->starter; i != NULL; i = i->next) {	// �迭�� �ڸ��� ���� �� ���
		if (temp != i->x) {
			printf("\n");
			temp = i->x;
		}
		printf("[%d][%d]: %2d ", i->x, i->y, i->value);
	}
	printf("\n\n");
}

// ��Ʈ���� �ʱ�ȭ �Լ�
void init(Matrix* matrix) {
	matrix->starter = NULL;
}

// �������� �����ִ� ������ ��Ʈ������ �߰��ϴ� �Լ�.
void copyData(Matrix* matrix, int** sparse_matrix, int size) {
	for (int i = 0; i < size; i++) {
		for (int j = 0; j < size; j++) {
			if (sparse_matrix[i][j] != 0) {
				addData(matrix, i, j, sparse_matrix[i][j], -1); //-1�� ������ ������ �߰�
			}													// 1�� �Ӹ��� ������ �߰�		
		}
	}
}

// ��Ʈ����(��� ����� ���) ���� ��� ������ �����ϴ� �Լ�.
Matrix calcSparse(Matrix* matrix1, Matrix* matrix2, int way) {
	Matrix result;
	init(&result);
	Sparse* temp1, *temp2;
	temp1 = matrix1->starter;
	temp2 = matrix2->starter;
	if (1 == way) {
		while ((temp1 != NULL) && (temp2 != NULL)) {
			if (temp1->x == temp2->x) { //���� ������ ���,
				if (temp1->y == temp2->y) {			//���� ������ ���,
					int is_zero = temp1->value + temp2->value;
					if (is_zero) { // 0�� �ƴϸ�
						addData(&result, temp1->x, temp1->y, is_zero, -1);
						temp1 = temp1->next;
						temp2 = temp2->next;
					}
				}
				else if (temp1->y < temp2->y) {		// �ι�° ����� y�� �� ū ���.
					addData(&result, temp1->x, temp1->y, temp1->value, -1);
					temp1 = temp1->next;
				}
				else {								// ù��° ����� y�� �� ū ���.
					addData(&result, temp2->x, temp2->y, temp2->value, -1);
					temp2 = temp2->next;
				}
			}
			else if (temp1->x < temp2->x) {			// �ι��� ����� x�� �� ū ���.
				addData(&result, temp1->x, temp1->y, temp1->value, -1);
				temp1 = temp1->next;
			}
			else {									// ù��° ����� x�� �� ū ���.
				addData(&result, temp2->x, temp2->y, temp2->value, -1);
				temp2 = temp2->next;
			}
		}
		while (temp1 != NULL) {
			addData(&result, temp1->x, temp1->y, temp1->value, -1);
			temp1 = temp1->next;
		}
		while (temp2 != NULL) {
			addData(&result, temp2->x, temp2->y, temp2->value, -1);
			temp2 = temp2->next;
		}
	}
	else if (2 == way) {
		while ((temp1 != NULL) && (temp2 != NULL)) {
			if (temp1->x == temp2->x) { //���� ������ ���,
				if (temp1->y == temp2->y) {			//���� ������ ���,
					int is_zero = temp1->value - temp2->value;
					if (is_zero) { // 0�� �ƴϸ�
						addData(&result, temp1->x, temp1->y, is_zero, -1);
					}
					temp1 = temp1->next;
					temp2 = temp2->next;
				}
				else if (temp1->y < temp2->y) {		// �ι�° ����� y�� �� ū ���.
					addData(&result, temp1->x, temp1->y, temp1->value, -1);
					temp1 = temp1->next;
				}
				else {								// ù��° ����� y�� �� ū ���.
					addData(&result, temp2->x, temp2->y, -temp2->value, -1);
					temp2 = temp2->next;
				}
			}
			else if (temp1->x < temp2->x) {			// �ι�° ����� x�� �� ū ���.
				addData(&result, temp1->x, temp1->y, temp1->value, -1);
				temp1 = temp1->next;
			}
			else {									// ù��° ����� x�� �� ū ���.
				addData(&result, temp2->x, temp2->y, -temp2->value, -1);
				temp2 = temp2->next;
			}
		}
		while (temp1 != NULL) {
			addData(&result, temp1->x, temp1->y, temp1->value, -1);
			temp1 = temp1->next;
		}
		while (temp2 != NULL) {
			addData(&result, temp2->x, temp2->y, -temp2->value, -1);
			temp2 = temp2->next;
		}
	}
	else if (0 == way) {
		printf("����.\n");
		exit(0);
	}
	else {
		printf("���� ���� �Է�.\n");
		exit(0);
	}
	return result;
}

