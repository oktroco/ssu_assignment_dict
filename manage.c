//오경택
//단어장 관리 메뉴 시작
void manage_init(void){
	system("clear");
	char num = 0;
	while(num != 5){
		fprintf(stderr, ">>영어 단어 암기 프로그램 : 단어장 관리<<\n");		//메뉴 출력
		fprintf(stderr, "1. 새 파일 추가하기\t2. 새 단어 추가하기\n");
		fprintf(stderr, "3. 단어장 보기\t\t4. 단어 파일 목록보기\n");
		fprintf(stderr, "5. 단어장 관리 종료\n");
		printf("\n\n번호를 입력하세요 : ");
		scanf("%hhd", &num);
		while(getchar() != '\n'); //입력버퍼 비우기

		if (num == 1)
			manage_add_dic();	//새 파일 추가
		else if (num == 2)
			manage_add_words(); //새 단어 추가
		else if (num == 3)
			view_file_words();	//단어장 보기
		else if (num == 4)
			view_dic_list();	//단어맞추기
		else if (num == 5)
			return;
		else
			fprintf(stderr, "잘못된 입력\n");	//1~5 사이의 입력이 아닐때 오류메세지 출력
	}
}

//오경택
//새 파일 추가
void manage_add_dic(void){
	FILE *f = fopen("dic.list", "r"); //dic.list 열기
	if(f == NULL){ //dic.list에 없는 파일이면 리턴
		fprintf(stderr, "dic.list를 찾을 수 없습니다.\n");
		return;
	}
	char last_name[20], tmp_name[20];
	int last_file_num = 1;
	while((fscanf(f, "%s\n", tmp_name)) != EOF) //last_name에 dic.list에 기록된 마지막 파일명 삽입
		strcpy(last_name, tmp_name);
	sscanf(last_name, "%d", &last_file_num); //last_name의 정수부분 받아오기
	sprintf(last_name, "%d", last_file_num + 1); //last_name에 최신파일번호 + 1 입력
	strcat(last_name, ".dic"); //last_name에 .dic입력(x.dic이 된 상태)
	FILE *new_f = fopen(last_name, "w"); //last_name의 파일명으로 새 파일 생성
	system("clear");
	printf(">>영어 단어 암기 프로그램 : 단어장 관리 : 새 파일 추가<<\n");
	input_words(new_f); //새 단어를 새 파일에 입력
	fclose(new_f); 
	fclose(f);
	FILE *f_append = fopen("dic.list", "a"); //dic.list에 새 파일명 추가
	fprintf(f_append, "%s\n", last_name);
	fclose(f_append);
	printf("새 단어장 %s가 추가되었습니다.\n\n", last_name);
	printf("넘어가려면 아무키나 누르세요.");
	getchar(); //아무키나 입력하면 메인으로 복귀
	system("clear");
}

//오경택
//새 단어 추가
void manage_add_words(void){
	FILE *dict;
	while((dict = read_file("a")) == NULL); //dict에 x.dic 파일 저장(읽을 때까지 반복)
	system("clear");
	printf(">>영어 단어 암기 프로그램 : 단어장 관리 : 새 단어 추가<<\n");
	input_words(dict); //새 단어를 불러온 파일에 입력
	fclose(dict);
	printf("단어장에 단어가 추가되었습니다.\n\n");
	printf("넘어가려면 아무키나 누르세요.");
	getchar(); //아무키나 입력하면 메인으로 복귀
	system("clear");
}
	
//오경택
//단어 입력 함수
void input_words(FILE *f){
	char word[109]; //공백, NULL문자를 포함하여 105 + 4개의 공간 할당
	int word_cnt = 0;
	printf("최대 20단어까지 입력가능하며, 단어입력을 끝내려면 .add를 입력해주세요");
	while(word_cnt < 20){
		printf("남은 단어 입력 수 : %d\n", 20 - word_cnt);
		printf("영어 단어와 한글 뜻을 띄어쓰기로 구분하여 입력하세요 : \n");
		scanf("%[^\n]", word); //영어, 한글뜻 받기(띄어쓰기가 포함된 문자열)
		while(getchar() != '\n');	//개행문자 혹은 나머지 입력버퍼 비우기
		if(!strcmp(word, ".add"))
			break;
		fprintf(f, "%s\n", word); //파일에 쓰기
		word_cnt++;
	}
}

//오경택
//단어장 보기
void view_file_words(void){
	FILE *dict;
	while((dict = read_file("r")) == NULL); //dict에 x.dic 파일 저장(읽을 때까지 반복)
	char tmp_word[124];
	printf("-------단어장-------\n");
	while(fscanf(dict, "%[^\n]\n", tmp_word) != EOF) //띄어쓰기를 포함하여 개행까지 받기
		printf("%s\n", tmp_word); //화면에 출력
	fclose(dict);
	printf("\n넘어가려면 아무키나 누르세요.");
	getchar();
	system("clear");
}

//오경택
//단어 파일 목록보기
void view_dic_list(void){
	FILE *dic_list = fopen("dic.list", "r"); 
	char tmp_dic[20];
	printf("-------단어장목록-------\n");
	short dic_cnt = 0; //출력 갯수(5개가 되면 개행)
	while(fscanf(dic_list, "%[^\n]\n", tmp_dic) != EOF){
		if(dic_cnt < 5){ //한 줄에 5개를 출력한 경우
			printf("%9s", tmp_dic);
			dic_cnt++;
		}
		else{ //한 줄에 5개를 출력하기 전인 경우
			printf("\n%9s", tmp_dic);
			dic_cnt = 0;
		}
	}
	fclose(dic_list);
	printf("\n\n넘어가려면 아무키나 누르세요.");
	getchar();
	system("clear");
}
