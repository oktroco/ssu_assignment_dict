void flasch(void){
	printf(">>영어 단어 암기 프로그램 : 플래쉬카드<<");
	int time, how;
	word_struct *word=(word_struct*)malloc(sizeof(word_struct));
	printf("속도(초) : ");
	scanf("%d", &time);
	choose_dic(word);
	word_struct *word_arry[cnt];
	make_word_arry(word_arry, word);
	printf("출력방식(알파벳 순서대로 : 1, 무작위 : 2)");
	scanf("%d", &how);
	if(how==1)
		qsort(word_arry, cnt, sizeof(word_struct*), compare_word);
	time*=1000;
	for(int i=0; i<cnt; i++){
		printf("%s",word_arry[i]->eng);
		sleep(time);
		printf("%s", word_arry[i]->kor);
		sleep(time);
	}
}
