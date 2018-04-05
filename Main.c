#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "list.h"

int main() {


	//선언부.
	List list; //단순 연결 리스트.
	char* input;//사용자가 사용할 메뉴를 담을 변수.
	int data;//노드에 들어갈 데이터를 사용자로부터 입력 받을 변수.
	input = malloc(sizeof(char) * 4);

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
			addNode(&list, data, -1);
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
}
	/*[희소행렬 구하기]
		int size;
	int **sparse_matrix1, **sparse_matrix2;	//희소행렬 선언.
	
	//희소행렬 만들기.
	printf("희소행렬의 크기: ");
	scanf_s("%d", &size);
	sparse_matrix1 = createMatrix(size);
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
		printf("덧셈(1), 뺄셈(2), 종료(0) : ");
		scanf_s("%d", &way);
		result = calcSparse(&matrix1, &matrix2, way);	//희소행렬 연산.
		printMatrix(&result, size);
	}
}
	*/
	
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
