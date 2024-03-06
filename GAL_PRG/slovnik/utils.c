#include "headers.h"

int createFile(){
	FILE *f;
	f = fopen("data/translates.txt", "r");
	if(f == NULL){
		fclose(f);
		system("mkdir data");
		f = fopen("data/translates.txt", "w");
		fclose(f);
		return 0;
	}else{
		return 1;
	}
}
void addToFile(char en[], char cz[], int id){
	FILE *f;
	f = fopen("data/translates.txt", "a");
	if(f == NULL){
		printf("\n\nUNABLE TO OPEN FILE!\n\n");
	}
	char str[255];
	sprintf(str, "\n%s;%s;%d;", en, cz, id);
	fputs(str, f);
	fclose(f);
}
