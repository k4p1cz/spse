#include "headers.h"

SLOVNIK nacistSlovnikZeSouboru(){
	SLOVO temp;
	SLOVNIK e;
	e.pocetZaznamu = 0;
	char radek[999], *pom;
	FILE *f;
	f = fopen("data/slovnik.txt", "r");
	if(f == NULL){ // soubor neexistuje
		fclose(f);
		f = fopen("data/slovnik.txt", "w"); // zkusime soubor znovu vytvorit
		fclose(f);
		f = fopen("data/slovnik.txt", "r"); // zkusime soubor znovu otevrit
		if(f == NULL){ // soubor neexistuje
			system("mkdir data"); // vytvorime slozku data
			fclose(f);
			f = fopen("data/slovnik.txt", "w"); // zkusime soubor znovu vytvorit
			fclose(f);
			f = fopen("data/slovnik.txt", "r"); // zkusime soubor znovu otevrit
			if(f == NULL){ // soubor neexistuje
				system("cls");
				printf("CHYBA PRI NACTENI DAT!\nSLOVNIK BUDE PRAZDNY!\n\n");
				system("pause");
				return e; // error -> vracime prazdny slovnik
			}
		}
	}
	while(fgets(radek, 100, f) != NULL){ // nacitame data po radku
		pom = strtok(radek, ";"); // vezmeme 1. slovo az po ;
		strcpy(temp.cz, pom);
		pom = strtok(NULL, ";"); // dalsi slovo az po ;
		strcpy(temp.en, pom);
		pom = strtok(NULL, ";"); // dalsi slovo az po ;
		temp.lekce = atoi(pom); // atoi() prevede string na int
		e.slovo[e.pocetZaznamu] = temp;
		e.pocetZaznamu++;
	}
	fclose(f);
	return e;
}
void pridatDoSouboru(char cz[], char en[], int lekce){
	FILE *f;
	char temp[100];
	f = fopen("data/slovnik.txt", "a"); // 'a' je mod pro pridavani a ne prepisovani
	if(f == NULL){
		system("cls");
		printf("CHYBA PRI ZAPISU DAT!\nDATA NEMUSI BYT ULOZENA!\n\n");
		system("pause");
	}else{
		sprintf(temp, "%s;%s;%d;\n", cz, en, lekce); // prevedeme vse na string - muzeme pouzit i snprintf()
		fputs(temp, f); // fputs() zapise string do souboru
		fclose(f);
	}
}
void prepsatZapisy(SLOVNIK e){
	FILE *f;
	int i;
	char temp[100];
	f = fopen("data/slovnik.txt", "w");
	if(f == NULL){
		system("cls");
		printf("CHYBA PRI ZAPISU DAT!\nDATA NEMUSI BYT ULOZENA!\n\n");
		system("pause");
	}else{
		for(i = 0; i < e.pocetZaznamu; i++){
			sprintf(temp, "%s;%s;%d;\n", e.slovo[i].cz, e.slovo[i].en, e.slovo[i].lekce);
			fputs(temp, f);
		}
		fclose(f);
	}
}
