#include "header.h"
#include "manage.c"
#include "hangman.c"
int cnt = 0; //현재 다루는 자기 참조 구조체의 구조체갯수(전역변수)

int main(void){
	system("clear");
	char num = 0;
	while(num != 5){
		fprintf(stderr, ">>영어 단어 암기 프로그램<<\n");		//메뉴 출력
		fprintf(stderr, "1. 영어 단어 맞추기\t2. 플래쉬 카드\n");
		fprintf(stderr, "3. 행맨(hangman)\t 4. 단어장 관리\n");
		fprintf(stderr, "5. 프로그램 종료\n");
		scanf("%hhd", &num);
		while(getchar() != '\n'); //입력버퍼 비우기

		if (num == 4)
			manage_init();	//단어장관리
		else if (num == 3)
			hang_man();	//행맨
		else if (num == 2)
			;	//플래시카드
		else if (num == 1)
			;	//단어맞추기
		else if (num == 5)
			;
		else
			fprintf(stderr, "잘못된 입력\n");	//1~5 사이의 입력이 아닐때 오류메세지 출력
		putchar('\n');
		//system("clear");
	}

}

//qsort를 위한 compare함수
int compare_word(const void *a, const void *b){
	return strcmp((*(word_struct **)a) -> eng, (*(word_struct **)b) -> eng);
}

/*
어느 함수에서든 호출 가능
자기참조구조체를 통해 만든 구조체배열의 주소를 get
*/
void choose_dic(word_struct *word){
	FILE *dict;
	while((dict = read_file("r")) == NULL); //dict에 x.dic 파일 저장(읽을 때까지 반복)
	cnt = make_struct(dict, word); //dict와 word를 이용하여 자기 참조 구조체 완성
	fclose(dict);
}

/*
자기참조구조체를 다루기 쉽게
포인터배열에 자기참조구조체들의 주소값들을 저장하는 작업
*/
void make_word_array(word_struct **word_array, word_struct *word){
	word_struct *word_tmp = word;
	for(int i = 0; i < cnt; i++){
		word_array[i] = word_tmp;
		word_tmp = word_tmp -> next;
	}
}

/*
dic에서 자기 참조 구조체를 생성하는 함수
자기 참조 구조체의 구조체 갯수를 반환
*/
int make_struct(FILE *dict, word_struct *word){
	int cnt_tmp = 0; //자기 참조 구조체의 구조체갯수
	word_struct *p_word = word; //임시 포인터변수p_word에 word의 주소대입
	//파일이 끝날 때까지 while 순환
	int check = fscanf(dict, "%s %[^\n]", p_word -> eng, p_word -> kor);	//check 변수에 받아와서 더 읽어올게 있는지 확인
	while(check != EOF){	//영어단어 저장
		getc(dict);
		#ifdef DEBUG
			PRINT_STR(p_word -> eng);
			PRINT_STR(p_word -> kor);
			fprintf(stderr, "한글strlen %lu\n", strlen(p_word -> kor));
		#endif
		cnt_tmp++;
		p_word -> next = (word_struct *)malloc(sizeof(word_struct)); //p_word의 next에 다음 구조체의 주소를 동적할당
		p_word = p_word -> next; //다음 구조체에 정보입력을 하기 위해 p_word에 다음 구조체 주소 대입
		check = fscanf(dict, "%s %[^\n]", p_word -> eng, p_word -> kor);
	}
	p_word -> next = NULL; //마지막 구조체에는 이어지는 구조체가 없으므로 next에 NULL포인터 대입
	return cnt_tmp;
}

//x.dic이 dic.list이 존재하는지 검사 후 x.dic의 주소를 반환을 하는 함수
FILE *read_file(char *type){
	char target[10]; //사용자가 원하는 파일명문자열
	char compare[10]; //존재확인을 위한 비교문자열
	FILE *f_list = fopen("dic.list", "r"); //dic.list 오픈
	printf("단어장 번호를 입력해주세요 : ");
	scanf("%s", target); //target에 사용자가 원하는 숫자 입력
	while(getchar() != '\n');								//(추가) 개행문자 혹은 나머지 입력버퍼 비우기
	strcat(target, ".dic"); //target에 확장자 .dic 입력
	while(fscanf(f_list, "%s", compare) != EOF){ //target이 dic.list에 있는지 한줄씩 확인
		if(!strcmp(target, compare)){ //strcmp가 0을 반환하면(같은 이름의 파일이 있으면)
			fclose(f_list); //dic.list 닫기
			printf("단어장 %s를 선택했습니다.\n", target);
			return fopen(target, type); //x.dic파일 주소 반환
		}
	}
	//target이 dic.list에 없을 경우 NULL반환
	fclose(f_list);
	printf("해당번호의 단어장은 없습니다.\n");
	return NULL;
}

void freeall(word_struct *curr){	//연결리스트의 동적할당을 해제하는 함수
	if(curr -> next != NULL)
		freeall(curr -> next);
	free(curr);
}
