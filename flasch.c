void flasch(void){
	extern int cnt;
	int num[cnt];
	srand(time(NULL));
	printf(">>영어 단어 암기 프로그램 : 플래쉬카드<<");
	int time, how, i, j;
	word_struct *word=(word_struct*)malloc(sizeof(word_struct));
	printf("속도(초) : ");
	scanf("%d", &time);
	choose_dic(word);
	word_struct *word_arry[cnt];
	make_word_array(word_arry, word);
	printf("출력방식(알파벳 순서대로 : 1, 무작위 : 2)");
	scanf("%d", &how);
	if(how==1){
		qsort(word_arry, cnt, sizeof(word_struct*), compare_word);
		for(i=0; i<cnt; i++){
			printf("%s",word_arry[i]->eng);
			sleep(time);
			printf("%s",word_arry[i]->kor);
			sleep(time);
		}
	}
	else{
		for(i=0; i<cnt; i++){
			num[i]=rand()%cnt;
		}
		for(i=0; i<cnt; i++){
			for(j=0;j<i;i++){
				while(num[i]==num[j]){
					num[i]=rand()%cnt;
					if(num[i]!=num[j])
						break;
				}
			}
		}
		for(i=0;i<cnt;i++){
			printf("%s", word_arry[num[i]]->eng);
			sleep(time);
			printf("%s", word_arry[num[i]]->kor);
			sleep(time);
		}
	}
}
