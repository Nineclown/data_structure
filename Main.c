#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <Windows.h>
#include <time.h>
#include "sparse.h"
#define MAX 3

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
				addData(matrix, i, j, sparse_matrix[i][j], -1); //-1은 꼬리에 데이터 추가
			}													// 1은 머리에 데이터 추가		
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
						temp1 = temp1->next;
						temp2 = temp2->next;
					}
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
	else {
		printf("잘 못 입력하셨습니다. 꽥\n");
	}
	return result;
}

int main() {
	int size;
	int **sparse_matrix1, **sparse_matrix2;	//희소행렬 선언.
	
	//희소행렬 만들기.
	printf("희소행렬의 크기: ");
	scanf_s("%d", &size);
	sparse_matrix1 = createMatrix(size);
	printf("test\n");
	sparse_matrix2 = createMatrix(size);
	
	//희소행렬을 효율적으로 담을 방법[리스트 활용]
	Matrix matrix1, matrix2;
	
	init(&matrix1);
	init(&matrix2);

	copyData(&matrix1, sparse_matrix1, size);	//리스트에 데이터를 저장.
	copyData(&matrix2, sparse_matrix2, size);

	Matrix result;
	int way;
	while (1) {
		printf("덧셈(1), 뺄셈(2) : ");
		scanf_s("%d", &way);
		result = calcSparse(&matrix1, &matrix2, way);	//희소행렬 연산.
		printMatrix(&result);
	}
}






/*[배열로 만든 다항식 계산 프로그램]
	Poly a, b, c;// 다항식.
	char* input;// 사용자가 사용할 메뉴를 담을 변수.
	input = malloc(sizeof(char) * 10);

	printf("===================[polynomial]===================\n");
	printf("=============아아아아ㅏ아아ㅏ아ㅏ아===============\n");
	printf("==================================================\n");
	printf("= 다항식1 세팅 중... 다항식1의 최고 차항의 차수: ");
	scanf_s("%d", &a.degree);
	for (int i = 0; i <= a.degree; i++) {
		printf("= %d차항의 계수: ", a.degree - i);
		scanf_s("%f", &a.data[i]);
		if ((0 == i) && (0 == a.data[0])) {
			printf("= 최고차항의 계수가 0이 될 수 없습니다. 다시 입력해주세요.\n");
			i--;
		}
	}

	printf("= 다항식2 세팅 중... 다항식2의 최고 차항의 차수: ");
	scanf_s("%d", &b.degree);
	for (int i = 0; i <= b.degree; i++) {
		printf("= %d차항의 계수: ", b.degree - i);
		scanf_s("%f", &b.data[i]);
		if ((0 == i) && (0 == b.data[0])) {
			printf("= 최고차항의 계수가 0이 될 수 없습니다. 다시 입력해주세요.\n");
			i--;
		}
	}
	printf("\n=    세팅이 끝났습니다. 작업을 선택해주세요.     =\n");
	while (1) {
		printf("=                                                =\n");
		printf("=	   덧셈(1). 뺄셈(2). 종료(quit).	 =\n");
		printf("==================================================\n");
		printf("= 수행할 작업은: ");
		scanf_s("%s", input, 10);
		printf("=											=\n");
		if (!strcmp(input, "1")) {
			c = polyCalc(a, b, 1);//덧셈. 지역변수로 선언한 구조체를 어떻게 스택이 끝나도 살아있지? 낚이면 안대. 살아있는게 아니라 복사된 거야.
			printPoly(c);
		}
		else if (!strcmp(input, "2")) {
			c = polyCalc(a, b, -1);//뺄셈.
			printPoly(c);
		}
		else if (!strcmp(input, "quit")) {
			printf("= 종료합니다.\n");
			return 0;
		}
		else {
			return 0;

		}
	}
}

	//위 함수의 단점. 공간을 많이 사용한데. 난 못느끼겠는데 빈공간이 많아 진데. 그래서 이걸 좀 더 효율적으로 관리하기 위해서
	//어떻게 해야 할까?
	//단순 연결 리스트를 사용해서 해결할 수 있다? 어떻게? 차수랑 계수를 값으로 하고 꼬리를 무는 식으로.
	*/

	/*[리스트로 구현한 다항식 프ㅗ그램]
		List_poly poly1, poly2, poly3;

		initPoly(&poly1, MAX_DEGREE);
		initPoly(&poly2, MAX_DEGREE);

		char* input;// 사용자가 사용할 메뉴를 담을 변수.
		input = malloc(sizeof(char) * 10);
		int degree;
		int coef;
		printf("===================[polynomial]===================\n");
		printf("=============아아아아ㅏ아아ㅏ아ㅏ아===============\n");
		printf("==================================================\n");
		printf("= 다항식1 세팅 중... 다항식1의 최고 차항의 차수: ");
		scanf_s("%d", &degree);
		for (int i = 0; i <= degree; i++) {
			printf("= %d차항의 계수: ", degree - i);
			scanf_s("%d", &coef);
			if (0 == coef) {
				if (0 == i) {
					printf("= 최고차항의 계수가 0이 될 수 없습니다. 다시 입력해주세요.\n");
					i--;
				}
				else {
					printf("= 계수가 0인 데이터는 저장하지 않습니다\n");
				}
			} else{
				addData(&poly1, coef, degree - i);
			}
		}
		printPoly2(&poly1);

		printf("==================================================\n");
		printf("= 다항식2 세팅 중... 다항식2의 최고 차항의 차수: ");
		scanf_s("%d", &degree);
		for (int i = 0; i <= degree; i++) {
			printf("= %d차항의 계수: ", degree - i);
			scanf_s("%d", &coef);
			if (0 == coef) {
				if (0 == i) {
					printf("= 최고차항의 계수가 0이 될 수 없습니다. 다시 입력해주세요.\n");
					i--;
				}
				else {
					printf("= 계수가 0인 데이터는 저장하지 않습니다\n");
				}
			}
			else {
				addData(&poly2, coef, degree - i);
			}
		}
		printPoly2(&poly2);

		printf("\n=    세팅이 끝났습니다. 작업을 선택해주세요.     =\n");
		while (1) {
			printf("=	   덧셈(1). 뺄셈(2). 종료(quit).	 =\n");
			printf("==================================================\n");
			printf("= 수행할 작업은: ");
			scanf_s("%s", input, 10);
			if (!strcmp(input, "1")) {
				poly3 = polyCalc2(&poly1, &poly2, 1);//덧셈. 지역변수로 선언한 구조체를 어떻게 스택이 끝나도 살아있지? 낚이면 안대. 살아있는게 아니라 복사된 거야.
				printPoly2(&poly3);
			}
			else if (!strcmp(input, "2")) {
				poly3 = polyCalc2(&poly1, &poly2, -1);
				printPoly2(&poly3);
			}
			else if (!strcmp(input, "quit")) {
				printf("= 종료합니다.\n");
				return 0;
			}
			else {
				return 0;
			}
		}
	}
		*/

		/*[단순 연결 리스트]
		//선언부.
		List list; //단순 연결 리스트.
		char* input;//사용자가 사용할 메뉴를 담을 변수.
		int data;//노드에 들어갈 데이터를 사용자로부터 입력 받을 변수.

		//초기화.
		input = malloc(sizeof(char) * 10);


		init(&list);//list 초기화.

		while (1) {
		//메뉴창.
		printf("===================[Linked list]===================\n");
		printf("=    리스트 확인(0).추가(1).삭제(2).종료(quit)    =\n");
		printf("===================================================\n");

		//입력.
		scanf_s("%s", input, 10);

		//리스트 출력.
		if (!strcmp(input, "0")) {
		printList(&list);
		}
		//리스트에 데이터 추가.
		else if (!strcmp(input, "1")) {
		printf("추가할 데이터를 입력하세요: ");
		scanf_s("%d", &data);
		addNode(&list, data);
		}
		//리스트의 데이터 삭제.
		else if (!strcmp(input, "2")) {
		removeNode(&list);
		}
		//프로그램 종료.
		else if (!strcmp(input, "quit")) {
		return 0;
		}
		//간단한 예외 처리.
		else {
		printf("잘 못 입력하셨어요\n");
		return 0;
		}
		}
		*/

		/*[다항식]
		Poly a = { 3,{ 7, 1, 0, 2 } };//최고차항이 3인 다항식. 7x^3 + 1x^2 + 2
		Poly b = { 4,{ 4, 9, 9, 1, 9 } }; // 4x^4 + 9x^3 + 9x^2 + 9x + 9
		Poly c;
		Poly d;
		int increase = 0;

		c = polyCalc(a, b, 1);//덧셈
		printPoly(c);

		d = polyCalc(b, a, -1);//뺄셈
		printPoly(d);
		*/
