#include "headers.h"



void init(){
	if(createFile() != 0){
		loadData();
		startUserMenu();
	}

}
void startUserMenu(){
	int c = 0;
	do{
		system("cls");
		printf("----------------------\n");
		printf("1. Preklad\n");
		printf("2. Zkouseni z 2. lekce\n");
		printf("3. Nahodne zkouseni\n");
		printf("4. Odstraneni slova ze slovniku\n");
		printf("5. Vypsani aktualniho slovniku\n");
		printf("----------------------\n");
		fflush(stdin);
		scanf("%d", &c);
	}while(c < 1 || c > 5);
	switch (c) {
	case 1:
		startTranslate();
		break;
	case 2:
		//TODO
		break;
	case 3:
		startRandomExam();
		break;
	case 4:
		
		break;
	case 5:
		printData();
		break;
	}
}

