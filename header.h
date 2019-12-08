#ifndef HEADER
	#define HEADER
	#include <stdio.h>
	#include <stdlib.h>
	#include <string.h>
	#include <time.h>
	#include <unistd.h>
	#define PRINT_STR(x) printf(#x" : %s\n", x)
	typedef struct word_struct{
		char eng[16]; //영어단어 15자 + '\0'
		char kor[93]; //한글단어 30자 + 공백 최대 2개 + '\0' (한글은 한글자에 utf-8기준 3바이트)
		struct word_struct *next; //자기 참조를 위한 포인터변수
	} word_struct;
	int make_struct(FILE *dict, word_struct *word);
	FILE *read_file(char *type);
	int choose_dic(word_struct *word);
	void make_word_array(word_struct **word_array, word_struct *word, int cnt);
	int compare_word(const void *a, const void *b);
	void hang_man(void);
	void manage_init(void);
	void manage_add_dic(void);
	void manage_add_words(void);
	void input_words(FILE *f);
	void view_file_words(void);
	void view_dic_list(void);
	void freeall(word_struct*);
	void flasch(void);
	void match_eng(void);
	#include "manage.c"
	#include "hangman.c"
	#include "matcheng.c"
	#include "flash.c"
#endif
