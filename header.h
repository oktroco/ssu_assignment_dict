#ifndef header
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
#endif
