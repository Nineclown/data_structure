#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "list.h"

int main() {


	//�����.
	List list; //�ܼ� ���� ����Ʈ.
	char* input;//����ڰ� ����� �޴��� ���� ����.
	int data;//��忡 �� �����͸� ����ڷκ��� �Է� ���� ����.
	input = malloc(sizeof(char) * 4);

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
			addNode(&list, data, -1);
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
}
	/*[������ ���ϱ�]
		int size;
	int **sparse_matrix1, **sparse_matrix2;	//������ ����.
	
	//������ �����.
	printf("�������� ũ��: ");
	scanf_s("%d", &size);
	sparse_matrix1 = createMatrix(size);
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
		printf("����(1), ����(2), ����(0) : ");
		scanf_s("%d", &way);
		result = calcSparse(&matrix1, &matrix2, way);	//������ ����.
		printMatrix(&result, size);
	}
}
	*/
	
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
