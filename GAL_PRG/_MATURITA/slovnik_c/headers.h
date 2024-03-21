#ifndef HEADERS_H
#define HEADERS_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct{
	char en[100];
	char cz[100];
	int lekce;
}SLOVO; // definujeme si slovo

typedef struct{
	SLOVO slovo[999];
	int pocetZaznamu;
}SLOVNIK; // definujeme si slovnik

SLOVNIK pridatSlovo(SLOVNIK e);
void vypsatSlovnik(SLOVNIK slovnik);
SLOVNIK nacistSlovnikZeSouboru();
void pridatDoSouboru(char cz[], char en[], int lekce);
SLOVNIK odstranitZaznam(SLOVNIK e);
void prepsatZapisy(SLOVNIK e);
void prekladSlova(SLOVNIK e);
#endif
