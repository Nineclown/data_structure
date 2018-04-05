#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <Windows.h>
#include <time.h>
#include "sparse.h"

//	리스트에 데이터를 추가하는 함수. x, y 위치와 해당하는 value. 리스트의 시작위치, 꼬리위치를 정하는 way.
void addData(Matrix* matrix, int x_data, int y_data, int value, int way) {
	Sparse* temp;
	Sparse* newdata;

	newdata = (Sparse*)malloc(sizeof(Sparse));  // 데이터를 함수 내에서 생성하기 때문에
	newdata->x = x_data;						// 동적으로 할당해줘야 함수 호출이 끝나도
	newdata->y = y_data;						// 값이 파괴되지 않는다.
	newdata->value = value;
	newdata->next = NULL;

	temp = matrix->starter;

	//데이터를 앞쪽에 추가하는 방식.
	if (1 == way) {
		if (NULL == temp) {
			matrix->starter = newdata;  // matrix->starter 대신 temp를 쓰면 값이 달라짐.
		}								// -> 의 의미를 잘 이해해야 한다.
		else {
			matrix->starter = newdata;
			newdata->next = temp;
		}
	}
	//데이터를 뒤쪽에 추가하는 방식.
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

// 희소 행렬을 만들어 주는 함수.
int** createMatrix(int input) {
	int size = input;
	Sleep(1000);		// srand()함수가 시간 값을 바탕으로 난수를 생성하는데, 
	srand(time(NULL));	// 그 텀이 너무짧아서 난수가 계속 동일하게 생성됨.
						// 그래서 강제로 텀을 늘려 주는 Sleep() 사용.

	int **sparse_matrix;										// 동적으로 배열을 할당하기 때문에
	sparse_matrix = (int**)malloc(sizeof(int*) * size);			// 함수 호출이 종료되어 스택이 파괴되어도
	for (int i = 0; i < size; i++) {							// 관계없이 힙 영역에 데이터가 보존되어 있다.
		sparse_matrix[i] = (int*)malloc(sizeof(int*)* size);	// 단, return 값으로 sparse_matrix를 넘겨주는데,
	}															// sparse_matrix의 값은 스택영역이므로 파괴가 된다.																				
	for (int i = 0; i < size; i++) {							// 내부적으로 sparse_matrix의 값을 복사해서 넘겨주게 된다.
		for (int j = 0; j < size; j++) {						// sparse_matrix의 값은 힙영역을 가리키는 주소.
			sparse_matrix[i][j] = rand() % 3;
			printf("matrix[%d][%d]: %d ", i, j, sparse_matrix[i][j]);
		}
		printf("\n");
	}
	printf("\n");
	return sparse_matrix;
}

// 희소 행렬을 free시키는 함수.
void freeMatrix(int** matrix, int size) {
	for (int i = 0; i < size; i++) {
		free(matrix[i]);
	}
	free(matrix);
}

// 매트릭스(희소 행렬의 요소 값들에 대한 리스트)를 출력하는 함수
void printMatrix(Matrix* matrix, int size) {
	Sparse* i;
	int temp = matrix->starter->x;						// 배열의 자릿수를 맞추기 위해 x 인덱스를 기억할 변수
	printf("\n");
	for (i = matrix->starter; i != NULL; i = i->next) {	// 배열의 자릿수 정리 및 출력
		if (temp != i->x) {
			printf("\n");
			temp = i->x;
		}
		printf("[%d][%d]: %2d ", i->x, i->y, i->value);
	}
	printf("\n\n");
}

// 매트릭스 초기화 함수
void init(Matrix* matrix) {
	matrix->starter = NULL;
}

// 희소행렬의 쓸모있는 값들을 매트릭스에 추가하는 함수.
void copyData(Matrix* matrix, int** sparse_matrix, int size) {
	for (int i = 0; i < size; i++) {
		for (int j = 0; j < size; j++) {
			if (sparse_matrix[i][j] != 0) {
				addData(matrix, i, j, sparse_matrix[i][j], -1); //-1은 꼬리에 데이터 추가
			}													// 1은 머리에 데이터 추가		
		}
	}
}

// 매트릭스(희소 행렬의 요소) 간의 산술 연산을 수행하는 함수.
Matrix calcSparse(Matrix* matrix1, Matrix* matrix2, int way) {
	Matrix result;
	init(&result);
	Sparse* temp1, *temp2;
	temp1 = matrix1->starter;
	temp2 = matrix2->starter;
	if (1 == way) {
		while ((temp1 != NULL) && (temp2 != NULL)) {
			if (temp1->x == temp2->x) { //행이 동일한 경우,
				if (temp1->y == temp2->y) {			//열도 동일한 경우,
					int is_zero = temp1->value + temp2->value;
					if (is_zero) { // 0이 아니면
						addData(&result, temp1->x, temp1->y, is_zero, -1);
						temp1 = temp1->next;
						temp2 = temp2->next;
					}
				}
				else if (temp1->y < temp2->y) {		// 두번째 행렬의 y가 더 큰 경우.
					addData(&result, temp1->x, temp1->y, temp1->value, -1);
					temp1 = temp1->next;
				}
				else {								// 첫번째 행렬의 y가 더 큰 경우.
					addData(&result, temp2->x, temp2->y, temp2->value, -1);
					temp2 = temp2->next;
				}
			}
			else if (temp1->x < temp2->x) {			// 두번ㅉ 행렬의 x가 더 큰 경우.
				addData(&result, temp1->x, temp1->y, temp1->value, -1);
				temp1 = temp1->next;
			}
			else {									// 첫번째 행렬의 x가 더 큰 경우.
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
			if (temp1->x == temp2->x) { //행이 동일한 경우,
				if (temp1->y == temp2->y) {			//열도 동일한 경우,
					int is_zero = temp1->value - temp2->value;
					if (is_zero) { // 0이 아니면
						addData(&result, temp1->x, temp1->y, is_zero, -1);
					}
					temp1 = temp1->next;
					temp2 = temp2->next;
				}
				else if (temp1->y < temp2->y) {		// 두번째 행렬의 y가 더 큰 경우.
					addData(&result, temp1->x, temp1->y, temp1->value, -1);
					temp1 = temp1->next;
				}
				else {								// 첫번째 행렬의 y가 더 큰 경우.
					addData(&result, temp2->x, temp2->y, -temp2->value, -1);
					temp2 = temp2->next;
				}
			}
			else if (temp1->x < temp2->x) {			// 두번째 행렬의 x가 더 큰 경우.
				addData(&result, temp1->x, temp1->y, temp1->value, -1);
				temp1 = temp1->next;
			}
			else {									// 첫번째 행렬의 x가 더 큰 경우.
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
		printf("종료.\n");
		exit(0);
	}
	else {
		printf("예상 밖의 입력.\n");
		exit(0);
	}
	return result;
}

