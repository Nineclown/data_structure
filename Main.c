#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <Windows.h>
#include <time.h>
#include "sparse.h"
#define MAX 3

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
			if (j % size == 0) printf("\n");
			printf("matrix[%d][%d]: %d ", i, j, sparse_matrix[i][j]);
		}
	}
	printf("\n");
	return sparse_matrix;
}

void freeMatrix(int** matrix, int size) {
	for (int i = 0; i < size; i++) {
		free(matrix[i]);
	}
	free(matrix);
}

void printMatrix(Matrix* matrix) {
	Sparse* i;
	printf("\n");
	for (i = matrix->starter; i != NULL; i = i->next) {
		printf("[%d][%d]: %d ", i->x, i->y, i->value);
	}
	printf("\n\n");
}

void init(Matrix* matrix) {
	matrix->starter = NULL;
}

void copyData(Matrix* matrix, int** sparse_matrix, int size) {
	for (int i = 0; i < size; i++) {
		for (int j = 0; j < size; j++) {
			if (sparse_matrix[i][j] != 0) {
				addData(matrix, i, j, sparse_matrix[i][j], -1); //-1�� ������ ������ �߰�
			}													// 1�� �Ӹ��� ������ �߰�		
		}
	}
}

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
						temp1 = temp1->next;
						temp2 = temp2->next;
					}
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
	else {
		printf("�� �� �Է��ϼ̽��ϴ�. ��\n");
	}
	return result;
}

int main() {
	int size;
	int **sparse_matrix1, **sparse_matrix2;	//������ ����.
	
	//������ �����.
	printf("�������� ũ��: ");
	scanf_s("%d", &size);
	sparse_matrix1 = createMatrix(size);
	printf("test\n");
	sparse_matrix2 = createMatrix(size);
	
	//�������� ȿ�������� ���� ���[����Ʈ Ȱ��]
	Matrix matrix1, matrix2;
	
	init(&matrix1);
	init(&matrix2);

	copyData(&matrix1, sparse_matrix1, size);	//����Ʈ�� �����͸� ����.
	copyData(&matrix2, sparse_matrix2, size);

	Matrix result;
	int way;
	while (1) {
		printf("����(1), ����(2) : ");
		scanf_s("%d", &way);
		result = calcSparse(&matrix1, &matrix2, way);	//������ ����.
		printMatrix(&result);
	}
}






/*[�迭�� ���� ���׽� ��� ���α׷�]
	Poly a, b, c;// ���׽�.
	char* input;// ����ڰ� ����� �޴��� ���� ����.
	input = malloc(sizeof(char) * 10);

	printf("===================[polynomial]===================\n");
	printf("=============�ƾƾƾƤ��ƾƤ��Ƥ���===============\n");
	printf("==================================================\n");
	printf("= ���׽�1 ���� ��... ���׽�1�� �ְ� ������ ����: ");
	scanf_s("%d", &a.degree);
	for (int i = 0; i <= a.degree; i++) {
		printf("= %d������ ���: ", a.degree - i);
		scanf_s("%f", &a.data[i]);
		if ((0 == i) && (0 == a.data[0])) {
			printf("= �ְ������� ����� 0�� �� �� �����ϴ�. �ٽ� �Է����ּ���.\n");
			i--;
		}
	}

	printf("= ���׽�2 ���� ��... ���׽�2�� �ְ� ������ ����: ");
	scanf_s("%d", &b.degree);
	for (int i = 0; i <= b.degree; i++) {
		printf("= %d������ ���: ", b.degree - i);
		scanf_s("%f", &b.data[i]);
		if ((0 == i) && (0 == b.data[0])) {
			printf("= �ְ������� ����� 0�� �� �� �����ϴ�. �ٽ� �Է����ּ���.\n");
			i--;
		}
	}
	printf("\n=    ������ �������ϴ�. �۾��� �������ּ���.     =\n");
	while (1) {
		printf("=                                                =\n");
		printf("=	   ����(1). ����(2). ����(quit).	 =\n");
		printf("==================================================\n");
		printf("= ������ �۾���: ");
		scanf_s("%s", input, 10);
		printf("=											=\n");
		if (!strcmp(input, "1")) {
			c = polyCalc(a, b, 1);//����. ���������� ������ ����ü�� ��� ������ ������ �������? ���̸� �ȴ�. ����ִ°� �ƴ϶� ����� �ž�.
			printPoly(c);
		}
		else if (!strcmp(input, "2")) {
			c = polyCalc(a, b, -1);//����.
			printPoly(c);
		}
		else if (!strcmp(input, "quit")) {
			printf("= �����մϴ�.\n");
			return 0;
		}
		else {
			return 0;

		}
	}
}

	//�� �Լ��� ����. ������ ���� ����ѵ�. �� �������ڴµ� ������� ���� ����. �׷��� �̰� �� �� ȿ�������� �����ϱ� ���ؼ�
	//��� �ؾ� �ұ�?
	//�ܼ� ���� ����Ʈ�� ����ؼ� �ذ��� �� �ִ�? ���? ������ ����� ������ �ϰ� ������ ���� ������.
	*/

	/*[����Ʈ�� ������ ���׽� ���Ǳ׷�]
		List_poly poly1, poly2, poly3;

		initPoly(&poly1, MAX_DEGREE);
		initPoly(&poly2, MAX_DEGREE);

		char* input;// ����ڰ� ����� �޴��� ���� ����.
		input = malloc(sizeof(char) * 10);
		int degree;
		int coef;
		printf("===================[polynomial]===================\n");
		printf("=============�ƾƾƾƤ��ƾƤ��Ƥ���===============\n");
		printf("==================================================\n");
		printf("= ���׽�1 ���� ��... ���׽�1�� �ְ� ������ ����: ");
		scanf_s("%d", &degree);
		for (int i = 0; i <= degree; i++) {
			printf("= %d������ ���: ", degree - i);
			scanf_s("%d", &coef);
			if (0 == coef) {
				if (0 == i) {
					printf("= �ְ������� ����� 0�� �� �� �����ϴ�. �ٽ� �Է����ּ���.\n");
					i--;
				}
				else {
					printf("= ����� 0�� �����ʹ� �������� �ʽ��ϴ�\n");
				}
			} else{
				addData(&poly1, coef, degree - i);
			}
		}
		printPoly2(&poly1);

		printf("==================================================\n");
		printf("= ���׽�2 ���� ��... ���׽�2�� �ְ� ������ ����: ");
		scanf_s("%d", &degree);
		for (int i = 0; i <= degree; i++) {
			printf("= %d������ ���: ", degree - i);
			scanf_s("%d", &coef);
			if (0 == coef) {
				if (0 == i) {
					printf("= �ְ������� ����� 0�� �� �� �����ϴ�. �ٽ� �Է����ּ���.\n");
					i--;
				}
				else {
					printf("= ����� 0�� �����ʹ� �������� �ʽ��ϴ�\n");
				}
			}
			else {
				addData(&poly2, coef, degree - i);
			}
		}
		printPoly2(&poly2);

		printf("\n=    ������ �������ϴ�. �۾��� �������ּ���.     =\n");
		while (1) {
			printf("=	   ����(1). ����(2). ����(quit).	 =\n");
			printf("==================================================\n");
			printf("= ������ �۾���: ");
			scanf_s("%s", input, 10);
			if (!strcmp(input, "1")) {
				poly3 = polyCalc2(&poly1, &poly2, 1);//����. ���������� ������ ����ü�� ��� ������ ������ �������? ���̸� �ȴ�. ����ִ°� �ƴ϶� ����� �ž�.
				printPoly2(&poly3);
			}
			else if (!strcmp(input, "2")) {
				poly3 = polyCalc2(&poly1, &poly2, -1);
				printPoly2(&poly3);
			}
			else if (!strcmp(input, "quit")) {
				printf("= �����մϴ�.\n");
				return 0;
			}
			else {
				return 0;
			}
		}
	}
		*/

		/*[�ܼ� ���� ����Ʈ]
		//�����.
		List list; //�ܼ� ���� ����Ʈ.
		char* input;//����ڰ� ����� �޴��� ���� ����.
		int data;//��忡 �� �����͸� ����ڷκ��� �Է� ���� ����.

		//�ʱ�ȭ.
		input = malloc(sizeof(char) * 10);


		init(&list);//list �ʱ�ȭ.

		while (1) {
		//�޴�â.
		printf("===================[Linked list]===================\n");
		printf("=    ����Ʈ Ȯ��(0).�߰�(1).����(2).����(quit)    =\n");
		printf("===================================================\n");

		//�Է�.
		scanf_s("%s", input, 10);

		//����Ʈ ���.
		if (!strcmp(input, "0")) {
		printList(&list);
		}
		//����Ʈ�� ������ �߰�.
		else if (!strcmp(input, "1")) {
		printf("�߰��� �����͸� �Է��ϼ���: ");
		scanf_s("%d", &data);
		addNode(&list, data);
		}
		//����Ʈ�� ������ ����.
		else if (!strcmp(input, "2")) {
		removeNode(&list);
		}
		//���α׷� ����.
		else if (!strcmp(input, "quit")) {
		return 0;
		}
		//������ ���� ó��.
		else {
		printf("�� �� �Է��ϼ̾��\n");
		return 0;
		}
		}
		*/

		/*[���׽�]
		Poly a = { 3,{ 7, 1, 0, 2 } };//�ְ������� 3�� ���׽�. 7x^3 + 1x^2 + 2
		Poly b = { 4,{ 4, 9, 9, 1, 9 } }; // 4x^4 + 9x^3 + 9x^2 + 9x + 9
		Poly c;
		Poly d;
		int increase = 0;

		c = polyCalc(a, b, 1);//����
		printPoly(c);

		d = polyCalc(b, a, -1);//����
		printPoly(d);
		*/
