#include "header.h"
#include "manage.c"
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
	while(fscanf(dict, "%s %[^\n]", p_word -> eng, p_word -> kor) != EOF){	//영어단어 저장			(변경)getc로 받아오기에서 %[^\n]로
		getc(dict);
		#ifdef DEBUG
			PRINT_STR(p_word -> eng);
			PRINT_STR(p_word -> kor);
			fprintf(stderr, "한글strlen %lu\n", strlen(p_word -> kor));
		#endif
		cnt_tmp++;
		p_word -> next = (word_struct *)malloc(sizeof(word_struct)); //p_word의 next에 다음 구조체의 주소를 동적할당
		p_word = p_word -> next; //다음 구조체에 정보입력을 하기 위해 p_word에 다음 구조체 주소 대입
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

void freeall(word_struct *head){	//연결리스트의 동적할당을 해제하는 함수
	while(head != NULL){
		word_struct *tmp = head -> next;
		free(head);
		head = tmp;
	}
}


void print_hangman(char* underbar, char* hanged_man, word_struct* word){	//행맨의 화면을 출력하는 함수
	int tmp = 0;
	printf(">>영어 단어 암기 프로그램 : 행맨<<\n");
	printf("(힌트) : %s\n\n\n", word -> kor);
	for(tmp = 0; tmp < 20; tmp++)
		putchar('-');
	printf("+\n");
	printf("%20c\n", hanged_man[0]);
	printf("%19c%c%c\n", hanged_man[2], hanged_man[1], hanged_man[3]);
	printf("%19c%c\n\n\n", hanged_man[4], hanged_man[5]);

	printf("%s\n", underbar);
}


void manh(int lose, char* hanged_man){		//매달려있는 행맨의 진행도를 저장하는 함수
	switch(lose){
		case 6 :
			hanged_man[5] = '\\';
			break;
		case 5 :
			hanged_man[4] = '/';
			break;
		case 4 :
			hanged_man[3] = '\\';
			break;
		case 3 :
			hanged_man[2] = '/';
			break;
		case 2 :
			hanged_man[1] = '|';
			break;
		case 1 : 
			hanged_man[0] = 'O';
	}
}


void hang_man(void){		//행맨
	int random_hang, dump = 0, progress = 0, tries = 1, lose = 0,  correct = 0;	//lose는 몇번 실패했는지, correct는 단어를 맞췄는지 판정하는데 사용
	char input_char, answer[16], hanged_man[6] = {' ', ' ', ' ', ' ', ' ', ' '};	//answer는 행맨 밑 언더바에, hanged_man은 행맨을 그리는데 사용

	word_struct *head = (word_struct*)malloc(sizeof(word_struct));	//연결리스트를 받아올 구조체 선언
	choose_dic(head); //연결리스트 불러옴
	srand(time(NULL));
	random_hang = rand() % (cnt - 1); //난수 생성

	word_struct *link = head -> next;	//사용할 구조체 가져오기
	while(random_hang){
		link = link -> next;
		random_hang--;
	}
	
	for(dump = 0; dump < strlen(link->eng); dump++)		//단어들이 나오는  언더바 초기화
		answer[dump] = '_';
	answer[dump + 1] = '\0';
	
	while(progress != strlen(link -> eng)){
		system("clear");
		manh(lose, hanged_man);
		print_hangman(answer, hanged_man, link);
		if(lose == 6){					//행맨이 전부 그려질 경우 진행도와 상관없이 패배
			printf("\n\nGAME OVER\n3초 후에 메인 메뉴로 돌아갑니다.\n");
			freeall(head);	//동적할당 해제
			sleep(3);
			return;
		}
		printf("\n%d번째 시도 : ", tries);
		scanf("%c", &input_char);
		while(getchar() != '\n');	//입력버퍼 비우기
		for(dump = 0; dump < strlen(link -> eng); dump++)	//받아온 단어를 비교
			if((link -> eng)[dump] == input_char){
			       progress += 1;		//진행도를 증가시킴
			       answer[dump] = input_char;
			       (link -> eng)[dump] = '0';	//같다면 본래 배열에'0'을 넣어 다시 사용되지 않게함
			       correct = 1;
			}
		correct ? 0 : (lose += 1);	//같은게 있었다면 lose는 증가하지 않음
		correct = 0;
		tries++;

	}
	system("clear");
	print_hangman(answer, hanged_man, link);
	freeall(head);	//동적할당 해제
	printf("\n\nCongratulation\n 3초 후에 메인 메뉴로 돌아갑니다.\n");
	sleep(3);
}


