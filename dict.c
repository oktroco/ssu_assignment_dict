#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define PRINT_STR(x) printf(#x" : %s\n", x)
typedef struct word_struct{
	char eng[16]; //영어단어 15자 + '\0'
	char kor[93]; //한글단어 30자 + 공백 최대 2개 + '\0' (한글은 한글자에 utf-8기준 3바이트)
	struct word_struct *next; //자기 참조를 위한 포인터변수
} word_struct;

int make_struct(FILE *dict, word_struct *word);
FILE *read_file(void);
void choose_dic(word_struct *word);
void make_word_array(word_struct **word_array, word_struct *word);
int compare_word(const void *a, const void *b);

int cnt = 0; //현재 다루는 자기 참조 구조체의 구조체갯수(전역변수)

int main(void){
	word_struct *word = (word_struct *)malloc(sizeof(word_struct)); //첫 구조체word
	choose_dic(word); //파일선택 후 자기참조구조체 생성

	word_struct *word_array[cnt];
	make_word_array(word_array, word); //포인터배열 생성
	qsort(word_array, cnt, sizeof(word_struct *), compare_word);
	#ifdef DEBUG
	/*
	특정 구조체에 자기 참조 구조체로 이어진 모든 구조체를 출력하는 코드
	*/
		for(int i = 0; i<cnt; i++){
			printf("%d. %s %s\n", i, word_array[i] -> eng, word_array[i] -> kor);
		}
	#endif
	return 0;
}

//qsort를 위한 compare함수
int compare_word(const void *a, const void *b){
	printf("%d\n", (strcmp((*(word_struct **)a) -> eng, (*(word_struct **)b) -> eng)));
	return strcmp((*(word_struct **)a) -> eng, (*(word_struct **)b) -> eng);
}

/*
어느 함수에서든 호출 가능
자기참조구조체를 통해 만든 구조체배열의 주소를 get
*/
void choose_dic(word_struct *word){
	FILE *dict;
	while((dict = read_file()) == NULL); //dict에 x.dic 파일 저장(읽을 때까지 반복)
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
	while(fscanf(dict, "%s ", p_word -> eng) != EOF){ //영어단어 저장
		char a;
		int i = 0;
		//한글은 띄어쓰기를 포함하기 위해 getc로 개행문자전까지 입력
		while((a = getc(dict)) != '\n'){
			(p_word -> kor)[i] = a;
			i++;
		}
		#ifdef DEBUG
			PRINT_STR(p_word -> eng);
			PRINT_STR(p_word -> kor);
			printf("한글strlen : %lu\n", strlen(p_word->kor));
		#endif
		cnt_tmp++;
		p_word -> next = (word_struct *)malloc(sizeof(word_struct)); //p_word의 next에 다음 구조체의 주소를 동적할당
		p_word = p_word -> next; //다음 구조체에 정보입력을 하기 위해 p_word에 다음 구조체 주소 대입
	}
	p_word -> next = NULL; //마지막 구조체에는 이어지는 구조체가 없으므로 next에 NULL포인터 대입
	return cnt_tmp;
}

//x.dic이 dic.list이 존재하는지 검사 후 x.dic의 주소를 반환을 하는 함수
FILE *read_file(void){
	char target[10]; //사용자가 원하는 파일명문자열
	char compare[10]; //존재확인을 위한 비교문자열
	FILE *f_list = fopen("dic.list", "r"); //dic.list 오픈
	printf("단어장 번호를 입력해주세요 : ");
	scanf("%s", target); //target에 사용자가 원하는 숫자 입력
	strcat(target, ".dic"); //target에 확장자 .dic 입력
	while(fscanf(f_list, "%s", compare) != EOF){ //target이 dic.list에 있는지 한줄씩 확인
		if(!strcmp(target, compare)){ //strcmp가 0을 반환하면(같은 이름의 파일이 있으면)
			fclose(f_list); //dic.list 닫기
			return fopen(target, "r"); //x.dic파일 주소 반환
		}
	}
	//target이 dic.list에 없을 경우 NULL반환
	fclose(f_list);
	printf("해당번호의 단어장은 없습니다.\n");
	return NULL;
}
