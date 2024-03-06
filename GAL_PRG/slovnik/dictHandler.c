#include "headers.h"

WORDLIST allList;

void loadData(){
	memset(allList.word, 0, 100);
	allList.length = 0;
	WORD word;
	FILE *f = fopen("data/translates.txt", "r");
	char *pom, radek[100];
	while(fgets(radek, 100, f) != NULL){
		pom = strtok(radek, ";");
		strcpy(word.en, pom);
		pom = strtok(NULL, ";");
		strcpy(word.cz, pom);
		pom = strtok(NULL, ";");
		word.lesson = atoi(pom);
		allList.word[allList.length] = word;
		allList.length++;
	}
}
void printData(){
	int i;
	WORD word;
	system("cls");
	printf("EN | CZ | LESSON\n");
	for(i=0; i<allList.length; i++){
		word = allList.word[i];
		printf("%s | %s | %d\n", word.en, word.cz, word.lesson);
	}
	printf("\n\n");
	system("pause");
}
void startTranslate(){
	int i;
	WORD word;
	int found = 0;
	int stop = 0;
	char wordToTranslate[100];
	do{
		system("cls");
		printf("-----TRANSLATE-----\n");
		printf("If you want to go back, write 'stop'\n\n");	
		printf("Enter word to translate: ");
		fflush(stdin);
		gets(wordToTranslate);
		if(strcmp(wordToTranslate, "stop") == 0){
			stop = 1;
		}else{
			// en
			for(i = 0; i < allList.length; i++){
				word = allList.word[i];
				if(strcmp(word.en, wordToTranslate) == 0){
					printf("\n%s -> %s", word.en, word.cz);
					printf("\n\n");
					found = 1;
					system("pause");
				}
			}
			//cz
			if(found != 1){
				for(i = 0; i < allList.length; i++){
					word = allList.word[i];
					if(strcmp(word.cz, wordToTranslate) == 0){
						printf("\n%s -> %s", word.cz, word.en);
						printf("\n\n");
						found = 1;
						system("pause");
					}
				}
			}
			if(found != 1){
				char c[100];
				printf("\n\nUnable to find the word you want...\n");
				printf("\n\nType 'add' to add this word to the dictionary: ");
				fflush(stdin);
				gets(c);
				if(strcmp(c, "add") == 0){
					addWordToDictionary(wordToTranslate);
					loadData();
					
				}
			}
		}
		
	}while(stop != 1);	
}
void addWordToDictionary(char e[]){
	char lang[100];
	int back = 0;
	int cont = 0;
	int lang_ = 0; // 0 - en ||  1 - cz
	do{
		system("cls");
		cont = 0;
		printf("-----ADD TO THE DICTIONARY-----\n");
		printf("-------1/2 SELECT LANUAGE-------\n");
		printf("Please, type 'cz' or 'en' to select language of your word\nor 'back' to go back:");
		fflush(stdin);
		gets(lang);
		if(strcmp(lang, "cz") == 0 || strcmp(lang, "en") == 0 || strcmp(lang, "back") == 0){
			cont = 1;
		}
	}while(cont != 1);
	if(strcmp(lang, "back") == 0){
		back = 1;
	}
	if(back != 1){
		if(strcmp(lang, "cz") == 0){
			lang_ = 1;
		}
		if(lang_ == 0){
			char translated[100];
			int lessonId = 0;
			system("cls");
			printf("-----ADD TO THE DICTIONARY-----\n");
			printf("-------------2/2-------------\n");
			printf("ADDING: ");
			puts(e);
			printf("\n");
			printf("Please, type translation to your word: ");
			fflush(stdin);
			gets(translated);
			printf("\nPlease, enter lesson ID: ");
			scanf("%d", &lessonId);
			addToFile(e, translated, lessonId);
			system("cls");
			printf("Successfully added to the dictionary!");
		}else{
			char translated[100];
			int lessonId = 0;
			system("cls");
			printf("-----ADD TO THE DICTIONARY-----\n");
			printf("-------------2/2-------------\n");
			printf("ADDING: ");
			puts(e);
			printf("\n");
			printf("Please, type translation to your word: ");
			fflush(stdin);
			gets(translated);
			printf("\nPlease, enter lesson ID: ");
			scanf("%d", &lessonId);
			addToFile(translated, e, lessonId);
			system("cls");
			printf("Successfully added to the dictionary!");
		}
		printf("\n\n\n");
		system("pause");
	}
}
void startRandomExam(){
	srand(time(NULL));
	int correctlyAnswered = 0;
	int wordCount = 0;
	WORDLIST history;
	WORD historyWord;
	WORD word;
	history.length = 0;
	char wordToTranslate[100];
	char answer[100];
	int wordPos = 0;
	for(int i = 0; i < RANDOM_EXAM_LENGTH; i++){
		system("cls");
		printf("-----RANDOM EXAM-----\n");
		printf("-----WORD %d/%d", i, RANDOM_EXAM_LENGTH);
		printf("\n\n\n");
		wordPos = rand() % allList.length;
		word = allList.word[wordPos];
		
		
		
		printf("Translate %s: ", word.en);
		fflush(stdin);
		gets(answer);
		strcpy(historyWord.cz, answer);
		strcpy(historyWord.en, word.en);
		historyWord.lesson = word.lesson;
		history.word[history.length] = historyWord;
		history.length++; 
		if(strcmp(answer, word.cz) == 0){
			correctlyAnswered++;
		}
	}
	system("cls");
	printf("-----RANDOM EXAM-----\n");
	printf("-------RESULTS-------\n");
	printf("\n--Your answers--\n");
	for(int i = 0; i < history.length; i++){
		char str[255];
		historyWord = history.word[i];
		sprintf(str, "%s -> %s", historyWord.en, historyWord.cz);
		puts(str);
	}
	printf("\n--Your results--\n");
	printf("Correctly answered: %d\n", correctlyAnswered);
	printf("Wrongly aswered: %d\n", RANDOM_EXAM_LENGTH - correctlyAnswered); // 10 - 100%
	printf("Overall: %d%/100%", (100*(correctlyAnswered))/RANDOM_EXAM_LENGTH);
	printf("\n\n\n");
	system("pause");
	
}
