/*[포인터 연습2]
int a = 12;
int* ai;
ai = &a;
printf("제발: %d\n", *ai);
*/

/*[포인터 연습3]
char i = 'C';
char* pi;
pi = &i;
printf("이거 머냥 %c\n", *pi);
pi = "hello";
printf("이건 또 머냥: %s\n", pi);
==> 결론.
%s는 주소를 받는 지시어. 그리고 *pi는 pi가 갖고 있는 주소에 해당하는 위치의 값을 의미. 그래서 에러가 나는것.
먼 말? 주소를 입력해야 하는데 값을 입력했으니까 런 타임 에러가 나는 거라고.
*/

//char* pi = malloc(sizeof(char) * 10);
//char pe[6] = "hello";
//pi = "hello";// pi에는 지금 "hello"라는 주소가 저장되어 있는 거야. 
//scanf("%s", pi);
//printf("제발: %s\ni주소: %p\npi값: %p\n", *pi, &i, pi); <-- 에러가 난다. pi는 그 자체로 역참조의 기능을 수행하는 것 같다.
//아니야. %s는 주소값을 입력해줘야 하는데 값을 입력해주니까 거기에 해당하는 값을 출력하지 못하는 거야.
// 결론. 문자열 포인터는 역참조 연산자를 사용할 필요가 없는거 같다. 사용하면 런타임 에러 발생한다.
// 그 이유는 포인터 공부3에 적혀있다.


/*[포인터 공부]
int* pi;
int i = 19;
pi = &i;
int ** pii;
pii = &pi;
printf("&i: %p, pii: %p, &pii: %p\npi: %p, &pi: %p\ni: %d, *pi: %d, pi: %d, *pii: %d", &i, pii, &pii, pi, &pi, i, *pi, pi, *pii);
*/