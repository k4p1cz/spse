#include <stdio.h>
#include <stdlib.h>

int mainMenu();

int main(void){
	int main_rtrn;
	
	while(main_rtrn != 0){
		main_rtrn = mainMenu();
	}
	
	
	return 0;
}

int mainMenu(){
	int choise;
	system("cls");
	printf("----MAIN MENU----\n");
	printf("-----------------\n\n");
	printf("Chose from options above: ");
	scanf("%d", &choise);
	
	switch(choise){

	default:
		return 1;
		break;
	}
	
}
