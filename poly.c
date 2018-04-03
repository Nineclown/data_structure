#include "poly.h"
#include <stdio.h>
#include <stdlib.h>

//�迭 ���׽� ����.
Poly polyCalc(Poly alpha, Poly beta, int sign) {
	Poly result;
	float count[MAX_DEGREE] = { 0 };
	int increase = 0;

	//�� ���׽��� �����͸� count �迭�� ��´�.
	for (int i = alpha.degree; i >= 0; i--) {
		count[i] = alpha.data[increase];
		increase++;
	}
	increase = 0;
	if (-1 == sign) {
		for (int i = beta.degree; i >= 0; i--) {
			count[i] -= beta.data[increase];
			increase++;
		}
	}
	else if (1 == sign) {
		for (int i = beta.degree; i >= 0; i--) {
			count[i] += beta.data[increase];
			increase++;
		}
	}

	//count �迭�� �ְ������� ���ϰ� result�� �����Ѵ�.
	int Max = 0;

	for (int i = 0; i < MAX_DEGREE; i++) {
		if (count[i] != 0) {
			Max = i;
		}
	}
	result.degree = Max;

	//����� count�迭�� ���� result�� �����Ѵ�.
	increase = 0;
	for (int i = Max; i >= 0; i--) {
		result.data[increase] = count[i];
		increase++;
	}
	return result;
}
//����Ʈ ���׽� ����.
List_poly polyCalc2(List_poly *poly1, List_poly *poly2, int sign) {
	List_poly result;
	initPoly(&result, MAX_DEGREE);
	int is_zero;
	Polydata* temp1 = poly1->starter;
	Polydata* temp2 = poly2->starter;

	if (1 == sign) {
		while ((!IS_EMPTY(temp1)) && (!IS_EMPTY(temp2))) {
			if (temp1->degree == temp2->degree) {//������ ���� ���,
				is_zero = temp1->coef + temp2->coef;
				if (0 != is_zero) {//����� 0�̸� �������� �ʴ´�.
					addData(&result, is_zero, temp1->degree);
				}
				temp1 = temp1->next;
				temp2 = temp2->next;
			}
			else if (temp1->degree > temp2->degree) {//poly1�� ������ ���� ���,
				addData(&result, temp1->coef, temp1->degree);
				temp1 = temp1->next;
			}
			else {//poly2�� ������ ���� ���,
				addData(&result, temp2->coef, temp2->degree);
				temp2 = temp2->next;
			}
		}
		while (!IS_EMPTY(temp1)) {
			addData(&result, temp1->coef, temp1->degree);
			temp1 = temp1->next;
		}
		while (!IS_EMPTY(temp2)) {
			addData(&result, temp2->coef, temp2->degree);
			temp2 = temp2->next;
		}

	}
	else if (-1 == sign) {
		while ((!IS_EMPTY(temp1)) && (!IS_EMPTY(temp2))) {
			if (temp1->degree == temp2->degree) {//������ ���� ���,
				is_zero = temp1->coef - temp2->coef;
				if (0 != is_zero) {//����� 0�̸� �������� �ʴ´�.
					addData(&result, is_zero, temp1->degree);
				}
				temp1 = temp1->next;
				temp2 = temp2->next;
			}
			else if (temp1->degree > temp2->degree) {//poly1�� ������ ���� ���,
				addData(&result, temp1->coef, temp1->degree);
				temp1 = temp1->next;
			}
			else {//poly2�� ������ ���� ���,
				addData(&result, -temp2->coef, temp2->degree);
				temp2 = temp2->next;
			}
		}
		while (!IS_EMPTY(temp1)) {
			addData(&result, temp1->coef, temp1->degree);
			temp1 = temp1->next;
		}
		while (!IS_EMPTY(temp2)) {
			addData(&result, -temp2->coef, temp2->degree);
			temp2 = temp2->next;
		}
	}

	return result;

}
void initPoly(List_poly *poly, int size) {
	poly->starter = NULL;
}
void addData(List_poly *poly, int coef, int degree) {
	Polydata* newpoly;

	newpoly = (Polydata*)malloc(sizeof(Polydata));
	newpoly->coef = coef;
	newpoly->degree = degree;
	newpoly->next = NULL;

	if (IS_EMPTY(poly->starter))
		poly->starter = newpoly;
	else {
		Polydata* temp;
		temp = poly->starter;
		while (!IS_EMPTY(temp->next)) {
			temp = temp->next;
		}
		temp->next = newpoly;
	}

}
void printPoly2(List_poly* list) {
	Polydata* i;
	printf("\n");
	for (i = list->starter; i != NULL; i = i->next) {
		if (0 < i->coef) {
			if (0 != i->degree)
				printf(" +%dX^%d ", i->coef, i->degree);
			else {
				printf(" +%d ", i->coef);
			}
		}
		else {
			if (0 != i->degree)
				printf(" %dX^%d ", i->coef, i->degree);
			else {
				printf(" %d ", i->coef);
			}
		}

	}
	printf("\n\n");
}
void printPoly(Poly result) {
	int increase = 0;

	printf("= �ְ�����: %d\n=\n= ", result.degree);
	for (int i = result.degree; i >= 0; i--) {
		if (0 < result.data[increase]) {//����� ����� ����� ��¹��.
			if (0 != i) {//0���� �ƴ� ���, ������ ������ ���.
				printf(" +%.f X^%d", result.data[increase], i);
			}
			else {
				printf(" +%.f", result.data[increase]);
			}
		}
		else if (0 > result.data[increase]) {//����� ������ ����� ��¹��.
			if (0 != i) {//0���� �ƴ� ���, ������ ������ ���.
				printf(" %.f X^%d", result.data[increase], i);
			}
			else {
				printf(" %.f", result.data[increase]);
			}
		}
		increase++;
	}
	printf("\n");
}
