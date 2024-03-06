#ifndef HEADERS_H
#define HEADERS_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define RANDOM_EXAM_LENGTH 5

typedef struct{
	char en[100];
	char cz[100];
	int lesson;
	int id;
}WORD;
typedef struct{
	WORD word[100];
	int length;
}WORDLIST;


// userMenu.c
void init();
void startUserMenu();
void startTranslate();

// dictHandler.c
void loadData();
void printData();
void addWordToDictionary(char e[]);
void startRandomExam();

// utils.c
void addToFile(char en[], char cz[], int id);
int createFile();

#endif
