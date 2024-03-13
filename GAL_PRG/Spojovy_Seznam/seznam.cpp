#include "spoj.h"
Seznam::Seznam() {
	prvni = nullptr;   //inicializace spojového seznamu v konstruktoru
}

void Seznam::PridejNaZacatek(int c) { //prida do seznamu na zacatek
	Uzel* novyUzel = new Uzel(c); //ukazatel na novy uzel
	if (this->prvni == nullptr) { //kdyz je prvni v seznamu tak se da na pozici prvni
		this->prvni = novyUzel;
	} else {
		novyUzel->NastavNasl(this->prvni); //kdyz ne, tak nastavime, ze jeho nasledujici je ten co byl doted prvni
		this->prvni->NastavPred(novyUzel); //nastavim ze pred prvnim je novy
		this->prvni = novyUzel; //a na prvnim miste bude novy uzel
	}
}

void Seznam::VypisSeznam() const {
	Uzel* pom;
	for ( pom = this->prvni; pom != nullptr; pom = pom->DejNasl()) {
		cout << pom->DejCislo() << ", ";
	}
	cout << endl;
}

void Seznam::PridejNaKonec(int c){
	Uzel* novyUzel = new Uzel(c); //ukazatel na novy uzel
	if (this->prvni == nullptr) { //kdyz je prvni v seznamu tak se da na pozici prvni
		this->prvni = novyUzel;
	} else {
		for(this->prvni;this->prvni != nullptr; this->prvni=this->prvni ->DejNasl());
		this->prvni->NastavNasl(novyUzel); //kdyz ne, tak nastavime, ze jeho nasledujici je ten co byl doted prvni
		novyUzel->NastavPred(this->prvni); //nastavim ze pred prvnim je novy
		this->prvni = novyUzel; //a na prvnim miste bude novy uzel
	}
}
