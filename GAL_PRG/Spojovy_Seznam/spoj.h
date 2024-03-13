#ifndef SPOJ_H
#define SPOJ_H
#include <iostream>
using namespace std;

class Uzel {
private:
	int cislo; //data
	Uzel* pred; //ukazatel na predchozi v seznamu
	Uzel* nasl; //ukazatel na dalsi v seznamu
public:
	Uzel(); //kostruktory
	Uzel(int c);
	void NastavNasl(Uzel* novy); //setery pro nasledujici a predchozi
	void NastavPred(Uzel* novy);
	Uzel* DejNasl(); //getery
	Uzel* DejPred();
	int DejCislo();
};

class Seznam {
private:	
	Uzel* prvni; //ukazatel na prvni
public:
	Seznam(); //konstruktor
	void PridejNaZacatek(int c); //prida do seznamu na zacatek
	void VypisSeznam() const; //vypise seznam
	void PridejNaKonec(int c); //prida na konec
};

#endif
