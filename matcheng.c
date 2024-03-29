//오현승
void match_eng(void){
	char ans_word[15]; //답을 입력받는 변수
	int method; //출력방식 결정 변수
	int cnt;
	word_struct *wordfile = (word_struct *)malloc(sizeof(word_struct)); //단어 선언
	cnt = choose_dic(wordfile); //단어장 선택
	word_struct *word_array[cnt]; //단어 배열 선언
	make_word_array(word_array, wordfile, cnt); //단어 배열 생성
	printf("출력 방식(알파벳 순서대로: 1,무작위: 2): ");
	scanf("%d", &method); //출력 방식 결정
	system("clear");
	printf(">>영어 단어 암기 프로그램 : 영어 단어 맞추기<<\n");
	if(method==1){ //알파벳 순서대로
		int cor = 0; //맞은 개수
		int que = 0; //문제 개수
		int end = 1; //while을 끝내기 위한 변수
		int k=0;
		qsort(word_array, cnt, sizeof(word_struct *), compare_word); //알파벳 순서 정렬
		while(end){
			for(k=0;k<cnt;k++){
				que++; //문제 개수++
				printf("%s -> ",word_array[k]->kor); 
				scanf("%s",ans_word); //답 입력
				if(strcmp(ans_word, word_array[k]->eng) == 0)
					printf("correct!\n"), cor++; //맞은 개수++
				else if(strcmp(ans_word, ".quit")==0){ //강제 종료
					end--; //while을 나오기 위해 0으로 만듬
					while(getchar()!='\n');
					break;
				}else
					printf("incorrect!\n");
				while(getchar()!='\n');
			}
		}printf("당신의 점수는 %.2f 점입니다.", (float)cor/((float)que)*100); //점수 출력
	}else if(method==2){ //무작위
		int k,m,cor=0,random,a[cnt]; //임시변수2개, 맞은 개수,랜덤 숫자,랜덤 숫자 배열 변수
		int que = 0; //문제 개수
		int end = 1; // while을 끝내기 위한 변수
		srand(time(NULL)); //무작위
		while(end){
			for(k=0;k<cnt;k++){
				random=rand()%cnt; //무작위 숫자 생성
				a[k]=random;
				for(m=0;m<k;m++){ //중복 검사
					if(a[m]==random){
						k--; //중복일 경우 다시 돌아가서 숫자 생성
					}
				}
			}for(k=0;k<cnt;k++){
				que++; //문제 개수++
				m=a[k]; //랜덤 숫자를 m에 저장
				printf("%s -> ",word_array[m]->kor); //m번째 단어 출력
				scanf("%s",ans_word); //답 입력
				if(strcmp(ans_word,word_array[m]->eng)==0)
					printf("correct!\n"),cor++; //맞은 개수++
				else if(strcmp(ans_word, ".quit")==0){ //강제 종료
					end--; //while을 나오기 위해 0으로 만듬
					while(getchar()!='\n');
					break;
				}else
					printf("incorrect!\n");
				while(getchar()!='\n');
			}
		}printf("당신의 점수는 %.2f 점입니다.", (float)cor/((float)que)*100);
	}else
		printf("출력방식을 잘못 선택하셨습니다\n");
	while(getchar()!='\n');
	freeall(wordfile);
	system("clear");
}
