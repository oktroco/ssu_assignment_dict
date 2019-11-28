void match_eng(void){
	char dic_num, ans_word[15];
	int method;
	extern int cnt;
	word_struct *wordfile = (word_struct *)malloc(sizeof(word_struct));
	word_struct *word_array[cnt];
	choose_dic(wordfile);
	make_word_array(word_array, wordfile);
	printf("출력 방식(알파벳 순서대로: 1,무작위: 2): ");
	scanf("%d", &method);
	system("clear");
	printf(">>영어 단어 암기 프로그램 : 영어 단어 맞추기<<\n");
	if(method==1){
		int cor = 0;
		qsort(word_array, cnt, sizeof(word_struct), compare_word);
		int k;
		for(k=0;k<cnt;k++){
			printf("%s -> ",word_array[k]->kor);
			scanf("%s",ans_word);
			if(strcmp(ans_word, word_array[k]->eng) == 0)
				printf("correct!\n"), cor++;
			else if(strcmp(ans_word, ".quit"))
				break;
			else
				printf("incorrect!\n");
			while(getchar()!='\n');
		}
		printf("당신의 점수는 %.2f 점입니다.\n", (float)cor/(k+1)*100);
	}else if(method==2){
		int k,m,cor=0,random,a[30];
		srand(time(NULL));
		for(k=0;k<cnt;k++){
			random=rand()%30;
			for(m=0;m<k;m++){
				if(a[m]==random)
					k--;
			}
			a[k]=random;
		}for(k=0;k<cnt;k++){
			m=a[k];
			printf("%s -> ",word_array[m]->kor);
			scanf("%s",ans_word);
			if(ans_word==word_array[m]->eng)
				printf("correct!\n"),cor++;
			else if(strcmp(ans_word, ".quit"))
				break;
			else
				printf("incorrect!\n");
			while(getchar()!='\n');
		}
		printf("당신의 점수는 %.2f 점입니다.\n", (float)cor/(k+1)*100);
	}else
		printf("출력방식을 잘못 선택하셨습니다\n");
}
