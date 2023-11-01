#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct{
	int id;
	char nazev[50];
	int cena;
} ITEMS;

ITEMS allItems[999];
int allItems_length;

int startup();
void setupFiles();
void newItem();
int printItems();
void getAllItems(ITEMS allItems[999]);
int printItems2(ITEMS allItems[999]);

int main(){
	int mainRtrn;
	
	setupFiles();
	getAllItems(allItems);
	
	while(mainRtrn != 0){
		mainRtrn = startup(); // rtrn 1 - pokracovat, rtrn 0 - end
	}
	return 0;
}

int startup(){
	int choise = 0;
	system("cls");
	printf("----MAIN MENU----\n");
	printf("1. Print items\n");
	printf("2. New item\n");
	printf("3. Edit item\n");
	printf("4. Close app\n");
	printf("5. Print items 2\n");
	printf("-----------------\n\n");
	printf("Welcome! Please choose an option: ");
	scanf("%d", &choise);
	
	switch(choise){
	case 1:
		system("cls");
		return printItems();
	break;
	case 2:
		system("cls");
		newItem();
	break;
		
		
		
	case 4:
		system("cls");
		return 0;
	break;
	case 5:
		system("cls");
		return printItems2(allItems);
	break;
	default:
		return 1;	
	break;
	}
}
void setupFiles(){
	const char* dir = "data";
	mkdir(dir);
	return;
}
void newItem(){
	ITEMS newItem;
	
	FILE *f = fopen("data/data.txt", "a");
	if(f == NULL){
		return;
	}
	printf("---ADDING NEW ITEM---\n\n");
	printf("Items ID (number):\n");
	scanf("%d", &newItem.id);
	printf("Items name:\n");
	fflush(stdin);
	gets(newItem.nazev);
	printf("\nItems price:\n");
	scanf("%d", &newItem.cena);
	
	char *tmpText = newItem.nazev;
	
	fprintf(f, "%d;%s;%d\n", newItem.id, tmpText, newItem.cena);
	fclose(f);

	main();
}
int printItems(){
	FILE *f = fopen("data/data.txt", "r");
	if(f == NULL){
		return 1;
	}
	char line[256];
	const char s[2] = ";";
	while(fgets(line, sizeof(line), f) != NULL){
		char* token = strtok(line, s);
		
		while(token != NULL){
			printf(" %s", token);
			token = strtok(NULL, ";");
		}
	}
	
	fclose(f);
	
	printf("\n\n\n");
	
	system("pause");
	return 1;
}
void getAllItems(ITEMS allItems[999]){
	int i;
	int items_count = 0;
	FILE *f = fopen("data/data.txt", "r");
	if(f == NULL){
		return;
	}
	char line[100];
	const char s[2] = ";";
	int num;
	
	while(fgets(line, sizeof(line), f) != NULL){
		char* token = strtok(line, s);
		char* token2;
		i = 0;
		while(token != NULL){
			switch(i){
				case 0:
					token2 = token;
					num = atoi(token2);
					allItems[items_count].id = num;
				break;
				case 1:
					strcpy(allItems[items_count].nazev, token);
				break;
				case 2:
					token2 = token;
					num = atoi(token2);
					allItems[items_count].cena = num;
				break;
			}
			i++;
			token = strtok(NULL, ";");
		}
		items_count++;
	}
	allItems_length = items_count;
}
int printItems2(ITEMS allItems[999]){
	for(int i = 0; i < allItems_length; i++){
		printf("%d %s %d\n", allItems[i].id, allItems[i].nazev, allItems[i].cena);
	}
	
	printf("\n\n\n");
	system("pause");
	return 1;
}
