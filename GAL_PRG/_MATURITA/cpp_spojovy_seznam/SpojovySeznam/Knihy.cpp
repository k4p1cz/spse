#include "header.h"

Knihy::Knihy(){
	cislo = 0;
	pred = nullptr;
	nasl = nullptr;
	autor = "Nezadan";
	cena = 0;
}

Knihy::Knihy(int c, string n, string a, float p){
	cislo = c;
	pred = nullptr;
	nasl = nullptr;
	nazev = n;
	autor = a;
	cena = p;
}

istream &operator>>(istream &vstup, Knihy &x) {
	cout << "Zadejte cislo: ";
	vstup >> x.cislo;
	
	cout << "Zadejte nazev: ";
	fflush(stdin);
	getline(vstup, x.nazev);
	
	cout << "Zadejte autora: ";
	fflush(stdin);
	getline(vstup, x.autor);
	
	//Cena nemuze byt <= 0
	do{
		cout << "Zadejte cenu: ";
		vstup >> x.cena;
	}while(x.cena <= 0);
	
	return vstup;
}
