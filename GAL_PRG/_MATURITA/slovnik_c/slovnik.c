#include "headers.h"

SLOVNIK pridatSlovo(SLOVNIK e){
	system("cls");
	int duplicitniZaznam = 0;
	char ok[999];
	int i = 0;
	SLOVO temp;
	do{
		do{
			system("cls");
			printf("PRIDANI SLOVA\n------------------\n");
			printf("Zadejte slovo v cestine ('zrusit_' vas vrati zpet): ");
			fflush(stdin);
			gets(temp.cz);
			if(strcmp(temp.cz, "zrusit_") == 0){
				return e;
			}else{
				// overeni, ze slovo se jiz ve slovniku nenachazi
				for(i=0; i<e.pocetZaznamu; i++){ // prochazim slovnik
					if(strcmp(e.slovo[i].cz, temp.cz) == 0){ // porovnavam slova
						duplicitniZaznam = 1;
						system("cls");
						printf("Slovo %s jiz ve slovniku existuje!\nZadejte prosim jine slovo...\n\n", temp.cz);
						system("pause");
						break;
					}
				}
			}
		}while(duplicitniZaznam == 1);
		duplicitniZaznam = 0;
		do{
			system("cls");
			printf("PRIDANI SLOVA\n------------------\n");
			printf("Prelozte prosim slovo %s do anglictiny ('zrusit_' vas vrati zpet do nabidky): ", temp.cz);
			fflush(stdin);
			gets(temp.en);
			if(strcmp(temp.en, "zrusit_") == 0){
				return e;
			}else{
				// overovat, ze anglicke slovo se jiz ve slovniku nenachazi je za me zbytecne, ale pouzije se ten stejny kod
			}
		}while(duplicitniZaznam == 1); // smicku tady nechavam, aby bylo jasne, ze muzeme znovu overovat duplicitu
		system("cls");
		printf("PRIDANI SLOVA\n------------------\n");
		printf("Zadejte cislo lekce prekladu %s - %s: ", temp.cz, temp.en);
		fflush(stdin);
		scanf("%d", &temp.lekce);
		system("cls");
		printf("PRIDANI SLOVA\n------------------\n");
		printf("Overte prosim, ze zadany preklad je v poradku\n\n");
		printf("%s - %s\nLekce: %d\n\n", temp.cz, temp.en, temp.lekce);
		printf("'Ano' pro potvrzeni: ");
		fflush(stdin);
		gets(ok);
	}while(strcmp(ok, "Ano") != 0);
	e.slovo[e.pocetZaznamu] = temp;
	e.pocetZaznamu++;
	pridatDoSouboru(temp.cz, temp.en, temp.lekce);
	system("cls");
	printf("Slovo %s uspesne pridano do slovniku!\n\n", temp.cz);
	system("pause");
	return e;
}

void vypsatSlovnik(SLOVNIK slovnik){
	system("cls");
	int i;
	printf("|CZ|EN|LEKCE\n");
	for(i=0; i<slovnik.pocetZaznamu; i++){
		printf("%s | %s | %d\n", slovnik.slovo[i].cz, slovnik.slovo[i].en, slovnik.slovo[i].lekce);
	}
	printf("\n\n");
	system("pause");
}

SLOVNIK odstranitZaznam(SLOVNIK e){
	system("cls");
	int i;
	int odstranitId;
	SLOVO prazdneSlovo;
	do{
		system("cls");
		odstranitId = 0;
		printf("ID | CZ | EN | LEKCE\n");
		for(i = 0; i < e.pocetZaznamu; i++){
			printf("%d. | %s | %s | %d\n", i+1, e.slovo[i].cz, e.slovo[i].en, e.slovo[i].lekce);
		}
		printf("Vyberte, ktere slovo chcete odstranit: ");
		fflush(stdin);
		scanf("%d", &odstranitId);
	}while(odstranitId < 1 || odstranitId > i);
	odstranitId--; // upravime si 'odstranitId', aby odpovidalo nasledujicimu 'i'
	for(i = 0; i < e.pocetZaznamu; i++){
		if(i >= odstranitId){ // jakmile je id slova stejne jako id odstranovaneho zaznamu => nasli jsme odstranovany zaznam
			if(i == e.pocetZaznamu){ // pokud ostranovany zaznam je posledni zaznam
				e.slovo[i] = prazdneSlovo;
			}else{
				e.slovo[i] = e.slovo[i+1]; // shiftujeme zaznamy do leva
			}
		}
	}
	e.pocetZaznamu--;
	prepsatZapisy(e);
	system("cls");
	printf("Slovo uspesne odstraneno ze slovniku!\n\n");
	system("pause");

	return e;	
}

void prekladSlova(SLOVNIK e){
	system("cls");
	char slovo[100];
	int i;
	int found = 0; // 0 - nenalezeno, 1 - nalezeno, 2 - uzivatel si preje odejit
	do{
		system("cls");
		printf("PREKLAD SLOVA\n---------------\n");
		printf("Zadejte slovo, ktere chcete prelozit ('zpet_' vas presune zpet): ");
		fflush(stdin);
		gets(slovo);
		if(strcmp(slovo, "zpet_") == 0) found = 2;
		for(i=0;i<e.pocetZaznamu;i++){
			if(strcmp(slovo, e.slovo[i].cz) == 0){
				printf("\n%s : %s (Lekce %d)\n\n", e.slovo[i].cz, e.slovo[i].en, e.slovo[i].lekce);
				found = 1;
				break;
			}
			if(strcmp(slovo, e.slovo[i].en) == 0){
				printf("\n%s : %s (Lekce %d)\n\n", e.slovo[i].en, e.slovo[i].cz, e.slovo[i].lekce);
				found = 1;
				break;
			}
		}
		if(found == 0){
			system("cls");
			printf("System nenalezl slovo, ktere chcete prelozit.\n\n");
			system("pause");
		}
	}while(found == 0);
	if(found != 2){
		printf("Prejete si prelozit dalsi slovo ('Ano'): ");
		fflush(stdin);
		gets(slovo);
		if(strcmp(slovo, "Ano") == 0 || strcmp(slovo, "ano") == 0){
			prekladSlova(e);
		}
	}

}
