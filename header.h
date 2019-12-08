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
	int make_struct(FILE *dict, word_struct *word); //오경택
	FILE *read_file(char *type); //오경택
	int choose_dic(word_struct *word); //오경택
	void make_word_array(word_struct **word_array, word_struct *word, int cnt); //오경택
	int compare_word(const void *a, const void *b); //오경택
	void hang_man(void); //박동진
	void manage_init(void); //오경택
	void manage_add_dic(void); //오경택
	void manage_add_words(void); //오경택
	void input_words(FILE *f); //오경택
	void view_file_words(void); //오경택
	void view_dic_list(void); //오경택
	void freeall(word_struct*); //박동진
	void flasch(void); 
	void match_eng(void); //오현승
	#include "manage.c" //오경택
	#include "hangman.c" //박동진
	#include "matcheng.c" //오현승
	#include "flash.c" //최재혁
#endif
