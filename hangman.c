#define LOSE 0
#define WIN 1

void print_hangman(char *underbar, char* hanged_man, word_struct* word){        //행맨의 화면을 출력하는 함수
        printf(">>영어 단어 암기 프로그램 : 행맨<<\n");
        printf("(힌트) : %s\n\n\n", word -> kor);
		char tmp;
        for(tmp = 0; tmp < 20; tmp++)
                putchar('-');
        printf("+\n");
        printf("%20c\n", hanged_man[0]);
        printf("%19c%c%c\n", hanged_man[2], hanged_man[1], hanged_man[3]);
        printf("%19c%c\n\n\n", hanged_man[4], hanged_man[5]);
        printf("%s\n", underbar);
}


void man_status(char lose, char* hanged_man){           //매달려있는 행맨의 진행도를 저장하는 함수
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

word_struct* mklink(word_struct* head){		//행맨에 사용할 구조체를 가져옴
        int random_hang = rand() % cnt;     //난수 생성
	srand(time(NULL));
        word_struct *link = head;       //사용할 구조체 가져오기
        while(random_hang--)
                link = link -> next;
	return link;
}

void gameoff(_Bool w_or_l, char* progress, char* hanged_man, word_struct *link){	//승리와 패배 후의 작업
	system("clear");
        if(w_or_l == LOSE){          //패배할 경우
                man_status(6, hanged_man);
                print_hangman(progress, hanged_man, link);
                printf("\n\nGAMEOVER");
        }
        else{                   //승리했을 경우
                print_hangman(progress, hanged_man, link);
                printf("\n\nCONGRATULATION!!");
        }
        printf("\n엔터를 누르면 메인 메뉴로 돌아갑니다.");
        while(getchar() != '\n');       //'\n'이 나올때까지 무한반복
	system("clear");
}

void hang_man(void){		//행맨
        char tmp, win = 0, lose = 0, tries = 1;
        char progress[16], hanged_man[6] = {' ', ' ', ' ', ' ', ' ', ' '};      //progress는 행맨 밑 언더바에, hanged_man은 행맨을 그리는데 사용
        _Bool correct = 0, game_end = 1;      //단어를 맞췄는지 확인하는데 사용

	word_struct *head = (word_struct*)malloc(sizeof(word_struct));		//단어를 받아올 구조체 선언
        choose_dic(head); //연결리스트 불러옴
	word_struct *link = mklink(head);

	for(tmp = 0; tmp < strlen(link->eng); tmp++)            //단어가 나올 언더바 초기화
		progress[tmp] = '_';
	progress[tmp + 1] = '\0';

        while(game_end){
                system("clear");
                man_status(lose, hanged_man);
                print_hangman(progress, hanged_man, link);

                printf("\n%hhd번째 시도 : ", tries++);
                scanf("%c", &tmp);
                while(getchar() != '\n');       //입력버퍼 비우기
				int i;
                for(i  = 0; i < strlen(link -> eng); i++)   //받아온 단어를 비교
                        if((link -> eng)[i] == tmp){
                               win += 1;                //진행도를 증가시킴
                               progress[i] = tmp;
                               (link -> eng)[i] = EOF;  //같다면 본래 배열에 EOF를 넣어 다시 사용되지 않게함
                               correct = 1;
                        }
                correct ? 0 : (lose += 1);      //같은게 있었다면 lose는 증가하지 않음
                correct = 0;
		game_end = (lose != 6) && (win != strlen(link -> eng));	//게임의 종료여부를 판정
        }
	_Bool win_or_lose = (lose == 6) ? LOSE : WIN;
	gameoff(win_or_lose, progress, hanged_man, link);
        freeall(head);  //동적할당 해제
}
