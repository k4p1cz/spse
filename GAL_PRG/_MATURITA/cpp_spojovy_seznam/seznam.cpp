#include "header.h"

Seznam::Seznam(){
	nazev = "";
	prvni = nullptr; // inicializace
}

void Seznam::pridejNaZacatek(int e, bool notif) {
	system("cls");
	Uzel* novyUzel = new Uzel(e);
	
	if (this->prvni == nullptr) {
		this->prvni = novyUzel;
	}else {
		novyUzel->nastavNasl(this->prvni);
		this->prvni->nastavPred(novyUzel);
		this->prvni = novyUzel;
	}
	
	if(notif){
		cout << "Item byl ulozen na zacatek" << endl;
		system("pause");
	}
}
void Seznam::pridejNaKonec(int e, bool notif){
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
	if(notif){ // pokud chceme uzivatele obeznamit s zapsanim na konec
		cout << "Item byl ulozen na konec" << endl;
		system("pause");
	}
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
void Seznam::odstranitZaznam(){
	system("cls");
	Uzel* temp;
	int i = 1;
	// zjisteni poctu zaznamu
	for(temp = this->prvni; temp != nullptr; temp = temp->dejNasl()){
		i++;
	}
	int volba = 0;
	if(i == 1){
		cout << "Seznam je prazdny!" << endl;
		system("pause");
	}else{
		do{
			system("cls");
			i = 1;
			for(temp = this->prvni; temp != nullptr; temp = temp->dejNasl()) {
				cout << i << ". Cislo:  "<< temp->dejCislo() << endl;
				i++;
			}
			cout << endl;
			cout << "Zadej ID zaznamu, ktery chces odstranit: ";
			cin >> volba;
		}while(volba < 1 || volba > i-1);
		i = 0;
		volba--; // upravime si volbu, aby korespondovala s int i
		for(temp = this->prvni; temp != nullptr; temp = temp->dejNasl()) {
			if(volba == i){
				if(temp->dejPred() == nullptr){
					// 1. zaznam
					this->prvni = temp->dejNasl();
					temp->dejNasl()->nastavPred(nullptr);
				}else{
					if(temp->dejNasl() == nullptr){
						// posledni zaznam
						temp->dejPred()->nastavNasl(nullptr);
					}else{
						// zaznam mezi 1. a poslednim
						temp->dejNasl()->nastavPred(temp->dejPred());
						temp->dejPred()->nastavNasl(temp->dejNasl());
					}
				}
			}
			i++;
		}
		system("cls");
		cout << "Zaznam uspesne odstranen!" << endl;
		system("pause");
	}
}

void Seznam::duplikovatZaznam(){
	system("cls");
	int i = 1;
	int volba = 0;
	int dupeId = 0;
	Uzel* temp;
	Uzel* pridat;
	int hodnotaPridavanehoUzlu = 0;
	if(this->prvni == nullptr){ // neexistuje zadny zaznam
		cout << "Zadny zaznam neexistuje!" << endl;
		system("pause");
	}else{
		do{
			system("cls");
			for(temp = this->prvni; temp != nullptr; temp = temp->dejNasl()){
				cout << i << ". Cislo: " << temp->dejCislo() << endl;
				i++;
			}
			cout << "Zadej pozici zaznamu, ktery chces duplikovat: ";
			cin >> volba;
		}while(volba < 1 || volba > i-1); // nacitam pozici pro duplikaci
		// ciselne upravy zadanych hodnot
		dupeId = volba-1;
		volba = 0;
		i = 0;
		do{
			system("cls");
			for(temp = this->prvni; temp != nullptr; temp = temp->dejNasl()){
				if(i == dupeId){
					cout << "Duplikujete zaznam na " << i+1 << ". pozici s hodnotou " << temp->dejCislo() << endl; // oznameni uzivateli
					hodnotaPridavanehoUzlu = temp->dejCislo(); // zjistim hodnotu uzlu, ktery chce uzivatel duplikovat
				}
				i++;
			}
			// prehledna uzivatelska nabidka
			cout << "---------------" << endl;
			cout << "1. Duplikovat na zacatek" << endl;
			cout << "2. Duplikovat pred" << endl;
			cout << "3. Duplikovat za" << endl;
			cout << "4. Duplikovat na konec" << endl;
			cout << "5. Zrusit duplikovani" << endl;
			cout << "---------------" << endl;
			cout << "Jakou duplikaci chces zvolit: ";
			cin >> volba;
		}while(volba < 1 || volba > 5); // cekam na volbu uzivatele, kde zaznam duplikovat
		switch (volba) {
		case 1: // pokud uzivatel chce duplikovat na zacatek
			this->pridejNaZacatek(hodnotaPridavanehoUzlu, false); // pouziju vlastni funkci pridejnazacatek
			system("cls");
			cout << "Zaznam duplikovan na zacatek!" << endl;
			system("pause");
			break;
		case 2: // pokud uzivatel chce duplikovat pred jiz zadany zaznam
			i = 0;
			pridat = new Uzel(hodnotaPridavanehoUzlu); // novy uzel
			for(temp = this->prvni; temp != nullptr; temp = temp->dejNasl()){ // prochazim uzly
				if(i == dupeId){ // pokud se i rovna zaznamu, ktery chci duplikovat => temp je zaznam, ktery chci duplikovat
					if(temp->dejPred() == nullptr){
						// temp je 1. zaznam
						cout << "1. zaznam" << endl;
						temp->nastavPred(pridat);
						pridat->nastavNasl(temp);
						pridat->nastavPred(nullptr);
						this->prvni = pridat;
						/*
							Tyto funkce jsou celkem jasne, dle pojmenovani funkci.
						*/
						break;
					}else{
						if(temp->dejNasl() == nullptr){
							// temp je posledni zaznam
							cout << "posledni  zaznam" << endl;
							pridat->nastavNasl(temp);
							pridat->nastavPred(temp->dejPred());
							temp->dejPred()->nastavNasl(pridat);
							temp->nastavPred(pridat);
							break;
							/*
								Tyto funkce jsou celkem jasne, dle pojmenovani funkci.
							*/
						}else{
							// temp je zaznam mezi 1. a poslednim
							cout << "mezi" << endl;
							pridat->nastavNasl(temp);
							pridat->nastavPred(temp->dejPred());
							temp->dejPred()->nastavNasl(pridat);
							temp->nastavPred(pridat);
							break;
							/*
								Tyto funkce jsou celkem jasne, dle pojmenovani funkci.
							*/
						}
					}
				}
				i++;
			}
			system("cls");
			cout << "Zaznam duplikovan pred!" << endl;
			system("pause");
			break;
		case 3:
			pridat = new Uzel(hodnotaPridavanehoUzlu); // vytvarim novy uzel
			i = 0;
			for(temp = this->prvni; temp != nullptr; temp = temp->dejNasl()){ // prochazim uzly
				if(i == dupeId){ // pokud se temp rovna zaznamu, ktery chci duplikovat
					if(temp->dejPred() == nullptr){
						// temp je 1. zaznam
						pridat->nastavPred(temp);
						pridat->nastavNasl(temp->dejNasl());
						temp->dejNasl()->nastavPred(pridat);
						temp->nastavNasl(pridat);
						/*
							Tyto funkce jsou celkem jasne, dle pojmenovani funkci.
						*/
					}else{
						if(temp->dejNasl() == nullptr){
							// temp je posledni zaznam
							pridat->nastavPred(temp);
							pridat->nastavNasl(nullptr);
							temp->nastavNasl(pridat);
							/*
								Tyto funkce jsou celkem jasne, dle pojmenovani funkci.
							*/
						}else{
							// temp je zaznam mezi 1. a poslednim zaznamem
							pridat->nastavNasl(temp->dejNasl());
							pridat->nastavPred(temp);
							temp->dejPred()->nastavPred(pridat);
							temp->nastavNasl(pridat);
							/*
								Tyto funkce jsou celkem jasne, dle pojmenovani funkci.
							*/
						}
					}
				}
				i++;
			}
			system("cls");
			cout << "Zaznam duplikovan za!" << endl;
			system("pause");
			break;
		case 4:
			this->pridejNaKonec(hodnotaPridavanehoUzlu, false); // pouzivam svou funkci pridejNaKonec(), jelikoz fungovali je stejne
			system("cls");
			cout << "Zaznam duplikovan na konec!" << endl;
			system("pause");
			break;
		case 5:
			system("cls");
			cout << "Zrusili jste duplikovani..." << endl;
			system("pause");
			break;
		}
	}
}
