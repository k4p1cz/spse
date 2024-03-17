#ifndef HEADERS_H
#define HEADERS_H
#include <iostream>
#include <fstream>
#include <filesystem>
using namespace std;

class Uzel{
private:
	// Parametry daneho uzlu
	int id;
	// Ukazatele na predchozi a nasledujici uzel
	Uzel* pred;
	Uzel* nasl;
public: 
	Uzel();
	Uzel(int e);
	friend istream &operator>>(istream &vstup, Uzel &x);
	void nastavNasl(Uzel* n){nasl = n;};
	void nastavPred(Uzel* p){pred = p;};
	Uzel* dejNasl(){return this->nasl;};
	Uzel* dejPred(){return this->pred;};
	int dejCislo();
};

class Seznam{
private:
	// Parametry seznamu
	string nazev;
	// Ukazatel na 1. uzel v seznamu
	Uzel* prvni;
public:
	Seznam();
	void pridejNaZacatek(int e);
	void pridejNaKonec(int e, bool notif);
	void vypisSeznam() const;
	void zapisDoSouboru();
	void nacistZeSouboru();
};

// filesystem.cpp

void fs_init();

#endif
