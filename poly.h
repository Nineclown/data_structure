#pragma once

#define MAX_DEGREE 10
#define MAX 10
#define SWAP(x, y, t) ( (t)=(x), (x)=(y), (y)=(t) )
#define IS_EMPTY(ptr) (!(ptr))

typedef struct polynomial {
	int degree;
	float data[MAX_DEGREE];
} Poly;


typedef struct list_poly{
	struct polydata* starter;
} List_poly;

typedef struct polydata {
	int coef;
	int degree;
	struct polydata* next;
} Polydata;

Poly polyCalc(Poly alpha, Poly beta, int sign);
List_poly polyCalc2(List_poly *poly1, List_poly *poly2, int sign);
void printPoly(Poly result);
void printPoly2(List_poly* list);
void selection_sort(int* list[]);

void initPoly(List_poly *poly, int size);
void addData(List_poly *poly, int coef, int degree);