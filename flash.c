//최재혁//
void flash(void){
	srand(time(NULL));//rand()함수를 쓰기위한 조건
	printf(">>영어 단어 암기 프로그램 : 플래쉬카드<<\n");//메뉴 출력
	int cnt, time, how, i, j;// 함수에 필요한 정수형 자료 선언
	word_struct *word = (word_struct*)malloc(sizeof(word_struct));//구조체 포인터 선언
	cnt = choose_dic(word);//단어장 선택
	int num[cnt];//무작위 출력에 필요한 정수 배열 선언
	printf("속도(초) : ");
	scanf("%d", &time);//출력 속도 입력
	word_struct *word_arry[cnt];//단어장 안의 단어 크기만큼의 구조체 포인터 배열 선언
	make_word_array(word_arry, word, cnt);//배열 안에 구조체 포인터 저장
	printf("출력방식(알파벳 순서대로 : 1, 무작위 : 2)");
	scanf("%d", &how);//출력방식 입력
	if(how==1){
		system("clear");
		qsort(word_arry, cnt, sizeof(word_struct*), compare_word);//단어 정렬
		for(i=0; i<cnt; i++){
			printf(">>영어 단어 암기 프로그램 : 영어 단어 맞추기<<\n");
			printf("\n \n \n \n \n \n \n \t \t \t \t%s\n",word_arry[i]->eng);//영어 단어장 출력
			sleep(time);//time 만큼 출력 시간 지정
			system("clear");//화면정리
			printf(">>영어 단어 암기 프로그램 : 영어 단어 맞추기<<\n");
			printf("\n \n \n \n \n \n \n \t \t \t \t%s\n",word_arry[i]->kor);//한글 단어장 출력
			sleep(time);//time 만큰 출력 시간 지정
			system("clear");//화면정리
		}
	}
	else if(how==2){
		system("clear");
		for(i=0; i<cnt; i++){
			num[i]=rand()%cnt;//랜덤 출력 번호 저장
		}
		for(i=0; i<cnt; i++){
			for(j=0;j<i;j++){
				while(num[i]==num[j]){
					num[i]=rand()%cnt;//중복되는 num[i]에 새로운 수를 배정하고 다시 중복을 검사한다.
					if(num[i]!=num[j])
						break;//중복되지 않으면 while문이 멈춘다.
				}
			}
		}
		for(i=0;i<cnt;i++){
			printf("\n \n \n \n \n \n \n \t \t \t \t%s\n", word_arry[num[i]]->eng);//영어 단어 출력
			sleep(time);//잠시 멈춤 딜레이
			system("clear");//화면 정리
			printf("\n \n \n \n \n \n \n \t \t \t \t%s\n", word_arry[num[i]]->kor);//한글 단어 출력
			sleep(time);//잠시 멈춤 딜레이
			system("clear");//화면정리
		}
	}
	freeall(word);
}
