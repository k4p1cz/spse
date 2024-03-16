#ifndef header
#define header

#include <iostream>
#include <fstream>
using namespace std;

class Knihy{
private:
	int cislo;
	Knihy* pred;
	Knihy* nasl;
	string nazev;
	string autor;
	float cena;
	
public:
	Knihy();
	Knihy(int cis, string n, string a, float p);
	friend istream &operator>>(istream &vstup, Knihy &x);
	
	void setNasl(Knihy* n){nasl = n;};
	void setPred(Knihy* p){pred = p;};
	
	Knihy* getNasl(){return this->nasl;};
	Knihy* getPred(){return this->pred;};
	
	int getCislo(){return this->cislo;};
	void setCislo(int x){this->cislo = x;};
	
	string getNazev(){return this->nazev;};
	void setNazev(string x){this->nazev = x;};
	
	string getAutor(){return this->autor;};
	void setAutor(string x){this->autor = x;};
	
	float getCena(){return this->cena;};
	void setCena(float x){this->cena = x;};
};

class Seznam{
private:
	Knihy* prvni;
	Knihy* posledni;
	
public:
	Seznam();
	
	void pridejNaZacatek(int c, string n, string a, float p);
	void pridejNaKonec(int c, string n, string a, float p);
	
	void vypisSeznam();
	int pocetKnih();
	float Prumer();
	void doSouboru();
	void zeSouboru();
	void Odstranit();
	void Vyhledat();
	void Upravit();
	void pocetDelAutor();
	void minMax();
	void Seradit();
};

#endif
