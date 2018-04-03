#include "poly.h"
#include <stdio.h>
#include <stdlib.h>

//배열 다항식 계산기.
Poly polyCalc(Poly alpha, Poly beta, int sign) {
	Poly result;
	float count[MAX_DEGREE] = { 0 };
	int increase = 0;

	//두 다항식의 데이터를 count 배열에 담는다.
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

	//count 배열의 최고차항을 구하고 result에 대입한다.
	int Max = 0;

	for (int i = 0; i < MAX_DEGREE; i++) {
		if (count[i] != 0) {
			Max = i;
		}
	}
	result.degree = Max;

	//계산한 count배열의 값을 result에 대입한다.
	increase = 0;
	for (int i = Max; i >= 0; i--) {
		result.data[increase] = count[i];
		increase++;
	}
	return result;
}
//리스트 다항식 계산기.
List_poly polyCalc2(List_poly *poly1, List_poly *poly2, int sign) {
	List_poly result;
	initPoly(&result, MAX_DEGREE);
	int is_zero;
	Polydata* temp1 = poly1->starter;
	Polydata* temp2 = poly2->starter;

	if (1 == sign) {
		while ((!IS_EMPTY(temp1)) && (!IS_EMPTY(temp2))) {
			if (temp1->degree == temp2->degree) {//차수가 같은 경우,
				is_zero = temp1->coef + temp2->coef;
				if (0 != is_zero) {//계수가 0이면 저장하지 않는다.
					addData(&result, is_zero, temp1->degree);
				}
				temp1 = temp1->next;
				temp2 = temp2->next;
			}
			else if (temp1->degree > temp2->degree) {//poly1의 차수가 높은 경우,
				addData(&result, temp1->coef, temp1->degree);
				temp1 = temp1->next;
			}
			else {//poly2의 차수가 높은 경우,
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
			if (temp1->degree == temp2->degree) {//차수가 같은 경우,
				is_zero = temp1->coef - temp2->coef;
				if (0 != is_zero) {//계수가 0이면 저장하지 않는다.
					addData(&result, is_zero, temp1->degree);
				}
				temp1 = temp1->next;
				temp2 = temp2->next;
			}
			else if (temp1->degree > temp2->degree) {//poly1의 차수가 높은 경우,
				addData(&result, temp1->coef, temp1->degree);
				temp1 = temp1->next;
			}
			else {//poly2의 차수가 높은 경우,
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

	printf("= 최고차항: %d\n=\n= ", result.degree);
	for (int i = result.degree; i >= 0; i--) {
		if (0 < result.data[increase]) {//계수가 양수일 경우의 출력방식.
			if (0 != i) {//0차가 아닌 경우, 차수를 포함해 출력.
				printf(" +%.f X^%d", result.data[increase], i);
			}
			else {
				printf(" +%.f", result.data[increase]);
			}
		}
		else if (0 > result.data[increase]) {//계수가 음수일 경우의 출력방식.
			if (0 != i) {//0차가 아닌 경우, 차수를 포함해 출력.
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
