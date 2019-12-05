void flasch(void){
	srand(time(NULL));
	printf(">>영어 단어 암기 프로그램 : 플래쉬카드<<\n");
	int cnt, time, how, i, j;
	word_struct *word = (word_struct*)malloc(sizeof(word_struct));
	cnt = choose_dic(word);
	int num[cnt];
	printf("속도(초) : ");
	scanf("%d", &time);
	word_struct *word_arry[cnt];
	make_word_array(word_arry, word, cnt);
	printf("출력방식(알파벳 순서대로 : 1, 무작위 : 2)");
	scanf("%d", &how);
	if(how==1){
		qsort(word_arry, cnt, sizeof(word_struct*), compare_word);
		for(i=0; i<cnt; i++){
			printf("%s\n",word_arry[i]->eng);
			sleep(time);
			printf("%s\n",word_arry[i]->kor);
			sleep(time);
		}
	}
	else if(how==2){
		for(i=0; i<cnt; i++){
			num[i]=rand()%cnt;
		}
		for(i=0; i<cnt; i++){
			for(j=0;j<i;j++){
				while(num[i]==num[j]){
					num[i]=rand()%cnt;
					if(num[i]!=num[j])
						break;
				}
			}
		}
		for(i=0;i<cnt;i++){
			printf("%s\n", word_arry[num[i]]->eng);
			sleep(time);
			printf("%s\n", word_arry[num[i]]->kor);
			sleep(time);
		}
	}
}
