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