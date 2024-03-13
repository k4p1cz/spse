#include "spoj.h"

Uzel::Uzel(){ //kostruktory
	this->cislo=0; //cislo je 0
	this->nasl=nullptr; //musim nastavit ukazatel na null;
	this->pred=nullptr;
}

Uzel::Uzel(int c){
	this->cislo=c;
	this->nasl=nullptr;
	this->pred=nullptr;
}

void Uzel::NastavNasl(Uzel* novy){ //setery pro nasledujici a predchozi
	nasl = novy;
}

void Uzel::NastavPred(Uzel* novy){
	pred = novy ;
}
Uzel* Uzel::DejNasl(){ //getery
	return this->nasl;
}
Uzel* Uzel::DejPred(){ //getery
	return this->pred;
}
int Uzel::DejCislo(){
	return this->cislo;
}
