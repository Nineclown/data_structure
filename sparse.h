#pragma once

typedef struct matrix {
	struct sparse* starter;
} Matrix;

typedef struct sparse {
	int x;
	int y;
	int value;
	struct sparse* next;
} Sparse;

void addData(Matrix* matrix, int x_data, int y_data, int value, int way);
int** createMatrix(int input);
void freeMatrix(int** matrix, int size);
void printMatrix(Matrix* matrix, int size);
void init(Matrix* matrix);
void copyData(Matrix* matrix, int** sparse_matrix, int size);
Matrix calcSparse(Matrix* matrix1, Matrix* matrix2, int way);