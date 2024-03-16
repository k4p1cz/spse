#include "header.h"

Seznam::Seznam() {
	prvni = nullptr;
	posledni = nullptr;
}

//Pridat knihu na zacatek
void Seznam::pridejNaZacatek(int c, string n, string a, float p) {
	Knihy* novyUzel = new Knihy(c, n, a, p);
	
	if (this->prvni == nullptr) {
		this->prvni = novyUzel;
	} else {
		novyUzel->setNasl(this->prvni);
		this->prvni->setPred(novyUzel);
		this->prvni = novyUzel;
	}
	
	cout <<  "------------------------------" << endl;
	cout << "Kniha byla ulozena na zacatek" << endl;
}

//Vypsat knihy v seznamu
void Seznam::vypisSeznam(){	
	Knihy* temp;
	
	int i = 1;
	
	for(temp = this->prvni; temp != nullptr; temp = temp->getNasl()) {
		cout <<  "------------------------------" << endl;
		cout << i << ". Id:  "<< temp->getCislo() << endl;
		cout << "   Nazev: " << temp->getNazev() << endl;
		cout << "   Autor: " << temp->getAutor() << endl;
		cout << "   Cena: " << temp->getCena() << endl;
		
		i++;
	}
	
	if(i == 1) cout << "Seznam je prazdny" << endl;
}

//Vypis pocet knih
int Seznam::pocetKnih(){
	Knihy* temp;
	
	int i = 0;
	
	for(temp = this->prvni; temp != nullptr; temp = temp->getNasl())
	{
		i++;
	}
	
	return i;
}

//Pridej knihu na konec
void Seznam::pridejNaKonec(int c, string n,string a, float p){
	Knihy* temp;
	Knihy* novyUzel = new Knihy(c, n, a, p);
	
	if(this->prvni == nullptr){
		this->prvni = novyUzel;
	}else{
		
		for(temp = this->prvni; temp != nullptr; temp = temp->getNasl())
		{
			this->posledni = temp;
		}
		
		novyUzel->setPred(this->posledni);
		this->posledni->setNasl(novyUzel);
		this->posledni = novyUzel;
	}
	
	cout <<  "------------------------------" << endl;
	cout << "Kniha byla ulozena na konec" << endl;
}

//Vypocitej prumernou cenu knihy
float Seznam::Prumer(){
	Knihy* temp;
	
	float pocet = 0;
	float prumer = 0;
	int i = 0;
	
	for(temp = this->prvni; temp != nullptr; temp = temp->getNasl()) {
		pocet += temp->getCena();
		i++;
	}
	
	if(i == 0){
		return 0;
	}
	else{
		prumer = pocet/i;
		return prumer;
	}
}


//Ulozit seznam do souboru
void Seznam::doSouboru(){
	fstream f;
	Knihy* temp;
	
	int cislo;
	string nazev;
	string autor;
	float cena;
	
	f.open("seznam.txt", ios::out);
	
	cout <<  "------------------------------" << endl;
	if(f.fail()){
		cout << "Nepodarilo se otevrit soubor" << endl;
		return;
	}
	
	for(temp = this->prvni; temp != nullptr; temp = temp->getNasl()) {
		cislo = temp->getCislo();
		nazev = temp->getNazev();
		autor = temp->getAutor();
		cena = temp->getCena();
		f << cislo << ";" << nazev << ";" << autor << ";" << cena << ";" << endl;
	}
	
	cout << "Seznam byl ulozen do souboru" << endl;
	f.close();
}

//Pridat knihy ze souboru do seznamu
void Seznam::zeSouboru(){
	fstream f;
	
	string slovo, nazev, autor;
	float cena;
	int cislo, i = 1;
	
	f.open("seznam.txt");
	
	cout <<  "------------------------------" << endl;
	if(f.fail())
	{
		cout << "Nepodarilo se otevrit soubor" << endl;
		return;
	}
	
	while(getline(f, slovo, ';')){
		if(i%4 == 1)
		{
			cislo = atoi(slovo.c_str());
		}
		else if (i%4 == 2){
			nazev = slovo;
		}
		else if(i%4 == 3){
			autor = slovo;
		}
		else if(i%4 == 0){
			cena = atof(slovo.c_str());
			
			Knihy* novyUzel = new Knihy(cislo, nazev, autor, cena);
			
			//Alternativa pouzit funkci pridejNaZacatek() nebo pridejNaKonec()
			if (this->prvni == nullptr) {
				this->prvni = novyUzel;
			} else {
				novyUzel->setNasl(this->prvni);
				this->prvni->setPred(novyUzel);
				this->prvni = novyUzel;
			}
		}
		i++;
	}	
	
	cout << "Knihy z souboru byly pridany do seznamu" << endl;
	f.close();
}

//Odstranit knihu
void Seznam::Odstranit(){
	Knihy* temp;
	
	int id, cislo;
	bool control = false;
	
	cout << "Zadejte ID k odstraneni: ";
	cin >> id;
	
	for(temp = this->prvni; temp != nullptr; temp = temp->getNasl()) {		
		cislo = temp->getCislo();
		
		if(cislo == id) {
			if(temp->getPred() == nullptr) {
				if(temp->getPred() == nullptr) {
					this->prvni = nullptr;
				}
				else {
					temp->getNasl()->setPred(nullptr);
					this->prvni = temp->getNasl();
				}	
			}
			else if(temp->getNasl() == nullptr) {
				temp->getPred()->setNasl(nullptr);
			}
			else {
				temp->getPred()->setNasl(temp->getNasl());
				temp->getNasl()->setPred(temp->getPred());
			}
			
			delete temp;
			temp = nullptr;
			control = true;
			break;
		}
	}
	
	if(control == true)
	{
		cout << "Kniha byla odstranena z seznamu" << endl;
	}else{
		cout << "ID nebylo nalezeno" << endl;
	}
}

//Vyhledat knihy podle polozek
void Seznam::Vyhledat(){
	Knihy* temp;
	
	int id, id_temp, i = 0;
	char volba;	
	string nazev, nazev_temp, autor, autor_temp;
	float cena, cena_temp;
	bool control = false;
	
	cout << "a.) ... ID" << endl;
	cout << "b.) ... Nazev" << endl;
	cout << "c.) ... Autor" << endl;
	cout << "d.) ... Cena" << endl;
	
	cin >> volba;
	
	cout <<  "------------------------------" << endl;
	if(volba == 'a'){
		cout << "Zadejte ID: ";
		cin >> id;
		
		for ( temp = this->prvni; temp != nullptr; temp = temp->getNasl()) {		
			id_temp = temp->getCislo();
			
			if(id_temp == id)
			{
				nazev = temp->getNazev();
				autor = temp->getAutor();
				cena = temp->getCena();
				i++;
				
				cout <<  "------------------------------" << endl;
				cout << i << ". Id:  "<< id << endl;
				cout << "   Nazev: " << nazev << endl;
				cout << "   Autor: " << autor << endl;
				cout << "   Cena: " << cena << endl;
				
				control = true;
			}
		}
		
	}
	else if(volba == 'b'){
		cout << "Zadejte nazev: ";
		fflush(stdin);
		getline(cin, nazev);
		
		for(temp = this->prvni; temp != nullptr; temp = temp->getNasl()) {		
			nazev_temp = temp->getNazev();
			
			if(nazev == nazev_temp)
			{
				id = temp->getCislo();
				autor = temp->getAutor();
				cena = temp->getCena();
				i++;
				
				cout <<  "------------------------------" << endl;
				cout << i << ". Id:  "<< id << endl;
				cout << "   Nazev: " << nazev << endl;
				cout << "   Autor: " << autor << endl;
				cout << "   Cena: " << cena << endl;
				
				control = true;
			}
		}
	}
	else if(volba == 'c'){
		cout << "Zadejte autora: ";
		fflush(stdin);
		getline(cin, autor);
		
		for(temp = this->prvni; temp != nullptr; temp = temp->getNasl()) {		
			autor_temp = temp->getAutor();
			
			if(autor == autor_temp)
			{
				id = temp->getCislo();
				nazev = temp->getNazev();
				cena = temp->getCena();
				i++;
				
				cout <<  "------------------------------" << endl;
				cout << i << ". Id:  "<< id << endl;
				cout << "   Nazev: " << nazev << endl;
				cout << "   Autor: " << autor << endl;
				cout << "   Cena: " << cena << endl;
				
				control = true;
			}
		}
	}
	else if(volba == 'd'){
		cout << "Zadejte cenu: ";
		cin >> cena;
		
		for ( temp = this->prvni; temp != nullptr; temp = temp->getNasl()) {		
			cena_temp = temp->getCena();
			
			if(cena == cena_temp)
			{
				id = temp->getCislo();
				autor = temp->getAutor();
				nazev = temp->getNazev();
				i++;
				
				cout <<  "------------------------------" << endl;
				cout << i << ". Id:  "<< id << endl;
				cout << "   Nazev: " << nazev << endl;
				cout << "   Autor: " << autor << endl;
				cout << "   Cena: " << cena << endl;
				
				control = true;
			}
		}
	}
	
	if(control == true){
		cout <<  "------------------------------" << endl;
		cout << "Kniha byla nalezena" << endl;
	}
	else{
		cout << "Zadna kniha nebyla nalezena" << endl;
	}
}

//Upravit knihu v seznamu
void Seznam::Upravit(){
	Knihy* temp;
	
	int id, id_temp;
	string nazev, autor;
	float cena;
	bool control = false;
	
	cout << "Zadejte ID: ";
	cin >> id;
	
	for(temp = this->prvni; temp != nullptr; temp = temp->getNasl()) {		
		id_temp = temp->getCislo();
		
		if(id_temp == id){
			cout <<  "------------------------------" << endl;
			cout << "Id: " << temp->getCislo() << endl;
			cout << "Nazev: " << temp->getNazev() << endl;
			cout << "Autor: " << temp->getAutor() << endl;
			cout << "Cena: " << temp->getCena() << endl;
			cout <<  "------------------------------" << endl;
			
			cout << "Zadejte novy nazev: ";
			fflush(stdin);
			getline(cin, nazev);
			
			cout << "Zadejte noveho autora: ";
			fflush(stdin);
			getline(cin, autor);
			
			cout << "Zadejte novou cenu: ";
			cin >> cena;
			
			temp->setNazev(nazev);
			temp->setAutor(autor);
			temp->setCena(cena);
			
			cout <<  "------------------------------" << endl;
			cout << "Kniha byla upravena" << endl;
			control = true;
		}
	}
	
	if(control == false)
	{
		cout << "ID nenalezeno" << endl;
	}
	
}

//Vypise pocet a nazvy del od autora
void Seznam::pocetDelAutor(){
	Knihy* temp;
	
	string autor_temp, autor, kniha;
	int pocet = 0;
	
	cout << "Zadejte jmeno autora: ";
	fflush(stdin);
	getline(cin, autor_temp);
	
	for(temp = this->prvni; temp != nullptr; temp = temp->getNasl()) {		
		autor = temp->getAutor();
		
		if(autor == autor_temp)
		{
			pocet++;
			kniha = temp->getNazev();
			cout << pocet << ". Dilo: " << kniha << endl;
		}
	}
	
	cout <<  "------------------------------" << endl;
	if(pocet == 0)
	{
		cout << "Autor nenalezen" << endl;
	}
	else cout << "Pocet knih od autora: " << pocet << endl;
}

//Vypise maximalni a minimalni cenu knihy
void Seznam::minMax(){
	Knihy* temp;
	
	string nazev;
	float cena_temp = 0, cena;
	
	for(temp = this->prvni; temp != nullptr; temp = temp->getNasl()) {
		cena = temp->getCena();
		
		if(cena > cena_temp){
			cena_temp = cena;
			nazev = temp->getNazev();
		} 
	}
	
	if(cena_temp == 0){
		cout << "Seznam je prazdny" << endl;
		return;
	}
	
	cout << "Nejvetsi cena je: " << cena_temp << " Kc,-" << endl;
	cout << "Nazev: " << nazev << endl;
	
	for(temp = this->prvni; temp != nullptr; temp = temp->getNasl()) {
		cena = temp->getCena();
		
		if(cena_temp > cena){
			cena_temp = cena;
			nazev = temp->getNazev();
		} 
	}
	
	cout << "Nejmensi cena je: " << cena_temp << " Kc,-" << endl;
	cout << "Nazev: " << nazev << endl;
}

//Seradi knihy v seznamu podle ID nebo podle nazvu
void Seznam::Seradit(){
	Knihy* temp;
	
	bool swapped, control = false;
	char volba;
	
	cout << "a.) Seradit podle ID" << endl;
	cout << "b.) Seradit podle nazvu" << endl;
	
	cin >> volba;
	
	switch(volba){
	case 'a':
		do {
			swapped = false;
			Knihy* current = this->prvni;
			
			while(current->getNasl() != nullptr) {
				if(current->getCislo() > current->getNasl()->getCislo()) {
					temp = current->getNasl();
					current->setNasl(temp->getNasl());
					temp->setNasl(current);
					
					if(current == this->prvni) {
						this->prvni = temp;
					}
					else {
						current->getPred()->setNasl(temp);
					}
					
					temp->setPred(current->getPred());
					current->setPred(temp);
					
					swapped = true;
				}
				else {
					current = current->getNasl();
				}
			}
		}while(swapped);
		
		control = true;
		break;
		
	case 'b':
		do {
			swapped = false;
			Knihy* current = prvni;
			
			while(current->getNasl() != nullptr) {
				if(current->getNazev() > current->getNasl()->getNazev()) {
					temp = current->getNasl();
					current->setNasl(temp->getNasl());
					temp->setNasl(current);
					
					if(current == this->prvni) {
						this->prvni = temp;
					}
					else {
						current->getPred()->setNasl(temp);
					}
					
					temp->setPred(current->getPred());
					current->setPred(temp);
					
					swapped = true;
				}
				else {
					current = current->getNasl();
				}
			}
		}while(swapped);
		
		control = true;
		break;
	}
	
	cout <<  "------------------------------" << endl;
	if(control == true) {
		cout << "Seznam byl serazen" << endl;
	}
	else {
		cout << "Seznam nebyl serazen" << endl;
	}
}
