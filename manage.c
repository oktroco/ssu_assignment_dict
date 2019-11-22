void manage_init(void){
	//word_struct *word = (word_struct *)malloc(sizeof(word_struct)); //첫 구조체word
	//choose_dic(word); //파일선택 후 자기참조구조체 생성
 	//word_struct *word_array[cnt];
	//make_word_array(word_array, word); //포인터배열 생성

	system("clear");
	char num = 0;
	while(num != 5){
		fprintf(stderr, ">>영어 단어 암기 프로그램 : 단어장 관리<<\n");		//메뉴 출력
		fprintf(stderr, "1. 새 파일 추가하기\t2. 새 단어 추가하기\n");
		fprintf(stderr, "3. 단어장 보기\t 4. 단어 파일 목록보기\n");
		fprintf(stderr, "5. 단어장 관리 종료\n");
		printf("\n\n번호를 입력하세요 : ");
		scanf("%hhd", &num);
		while(getchar() != '\n'); //입력버퍼 비우기

		if (num == 1)
			manage_add_dic();	//단어장관리
		else if (num == 2)
			manage_add_words();
		else if (num == 3)
			;	//플래시카드
		else if (num == 4)
			;	//단어맞추기
		else if (num == 5)
			;
		else
			fprintf(stderr, "잘못된 입력\n");	//1~5 사이의 입력이 아닐때 오류메세지 출력
		putchar('\n');
	}
}

void manage_add_dic(void){
	FILE *f = fopen("dic.list", "r");
	if(f == NULL){
		fprintf(stderr, "dic.list를 찾을 수 없습니다.\n");
		return;
	}
	char last_name[20], tmp_name[20];
	int last_file_num = 1;
	while((fscanf(f, "%s\n", tmp_name)) != EOF)
		strcpy(last_name, tmp_name);
	sscanf(last_name, "%d", &last_file_num);
	sprintf(last_name, "%d", last_file_num + 1);
	strcat(last_name, ".dic");
	FILE *new_f = fopen(last_name, "w");
	input_words(new_f);
	fclose(new_f);
	fclose(f);
	FILE *f_append = fopen("dic.list", "a");
	fprintf(f_append, "%s\n", last_name);
	fclose(f_append);
	system("clear");
	printf("새 단어장 %s가 추가되었습니다.\n\n", last_name);
}

void manage_add_words(void){
	FILE *dict;
	while((dict = read_file("a")) == NULL); //dict에 x.dic 파일 저장(읽을 때까지 반복)
	input_words(dict);
	fclose(dict);
	system("clear");
	printf("단어장에 단어가 추가되었습니다.\n\n");
}
	

void input_words(FILE *f){
	char eng[16], kor[93];
	int word_cnt = 0;
	while(word_cnt < 20){
		printf("최대 20단어까지 입력가능하며, 단어입력을 끝내려면 .add를 입력해주세요");
		printf("남은 단어 입력 수 : %d\n", 20 - word_cnt);
		printf("영어 단어를 입력하세요(최대 15자) : \n");
		scanf("%s", eng);
		while(getchar() != '\n');								//(추가) 개행문자 혹은 나머지 입력버퍼 비우기
		if(!strcmp(eng, ".add"))
			break;
		printf("한글 뜻을 입력하세요(뜻은 최대 3개, 띄어쓰기로 구분, 모든 한글 뜻 합쳐서 30자까지 : \n");
		scanf("%[^\n]", kor);
		while(getchar() != '\n');								//(추가) 개행문자 혹은 나머지 입력버퍼 비우기
		fprintf(f, "%s %s\n", eng, kor);
		printf("%s : %s \n추가완료\n\n", eng, kor);
		word_cnt++;
	}
}
