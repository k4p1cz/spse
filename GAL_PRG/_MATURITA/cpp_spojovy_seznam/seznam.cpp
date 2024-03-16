#include "header.h"

Seznam::Seznam(){
	nazev = "";
	prvni = nullptr; // inicializace
}

void Seznam::pridejNaZacatek(int e) {
	system("cls");
	Uzel* novyUzel = new Uzel(e);
	
	if (this->prvni == nullptr) {
		this->prvni = novyUzel;
	}else {
		novyUzel->nastavNasl(this->prvni);
		this->prvni->nastavPred(novyUzel);
		this->prvni = novyUzel;
	}
	
	cout << "Item byl ulozen na zacatek" << endl;
	system("pause");
}
void Seznam::pridejNaKonec(int e){
	system("cls");
	Uzel* temp;
	Uzel* novyUzel = new Uzel(e);
	if(this->prvni == nullptr){ // pokud nemame zadny item
		this->prvni = novyUzel;
	}else{
		for(temp = this->prvni; temp->dejNasl() != nullptr; temp = temp->dejNasl()){} // ziskame posledni item
		temp->nastavNasl(novyUzel);
		novyUzel->nastavPred(temp);
	}
	cout << "Item byl ulozen na konec" << endl;
	system("pause");
}
void Seznam::vypisSeznam() const{	
	system("cls");
	Uzel* temp;
	int i = 1;
	for(temp = this->prvni; temp != nullptr; temp = temp->dejNasl()) {
		cout << i << ". Cislo:  "<< temp->dejCislo() << endl;
		i++;
	}
	
	if(i == 1) cout << "Seznam je prazdny" << endl;
	cout << "\n";
	system("pause");
}
