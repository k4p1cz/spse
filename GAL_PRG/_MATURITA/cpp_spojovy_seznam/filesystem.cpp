#include "header.h"

namespace fs = filesystem;


void fs_init(){ // funkce, ktera vytvori dulezite slozky v appdata/roaming
	string appdata = getenv("APPDATA");
	string folderPath = appdata+"\\cpp_spojovy_seznam\\data";
	if(!fs::exists(folderPath)){
		if(fs::create_directories(folderPath)){}else{
			system("cls");
			cout << "ERROR: Nepodarilo se vytvorit potrebne slozky!" << endl;
			cout << "ERROR PATH: " << folderPath << endl << endl;
			system("pause");			
		}
	}
}

void Seznam::zapisDoSouboru(){
	system("cls");
	string filename;
	string path;
	string appdata = getenv("APPDATA");
	
	cout << "Zadej nazev souboru: "; 
	fflush(stdin);
	cin >> filename;
	
	filename = filename + ".txt";
	path = appdata + "\\cpp_spojovy_seznam\\data\\" + filename;
	
	ofstream file(path); // otevre/vytvori soubor pro zapis
	if(file.fail()){
		cout << "ERROR: Nepodarilo se otevrit soubbor" << endl;
		cout << "ERROR PATH: " << path << endl;
		system("pause");
	}else{
		Uzel* temp;
		for(temp = this->prvni; temp != nullptr; temp = temp->dejNasl()){
			file << temp->dejCislo() << ";";
		}
		file.close();
		cout << "Data byly uspesne zapsana do souboru " << filename << endl;
		system("pause");
	}
}
void Seznam::nacistZeSouboru(){
	system("cls");
	string filename;
	string path;
	string appdata = getenv("APPDATA");
	
	cout << "Zadej nazev souboru: "; 
	fflush(stdin);
	cin >> filename;
	
	filename = filename + ".txt";
	path = appdata + "\\cpp_spojovy_seznam\\data\\" + filename;
	
	fstream file(path); // otevre/vytvori soubor pro cteni
	if(file.fail()){
		cout << "ERROR: Nepodarilo se otevrit soubbor" << endl;
		cout << "ERROR PATH: " << path << endl;
		system("pause");
	}else{
		string slovo;
		int cislo;
		this->prvni = nullptr; // nastavime 1. zaznam na NULL
		while(getline(file, slovo, ';')){ // tady uz jen ziskame data, vytvorime novy uzel a pridame jej na konec
			cislo = atoi(slovo.c_str());
			Uzel* novyUzel = new Uzel(cislo);
			this->pridejNaKonec(novyUzel->dejCislo(), false);
			// pokud bychom meli vice zaznamu, muzeme vyuzit toto reseni
			/*
			if(i%4 == 1)
				cislo = atoi(slovo.c_str());
			}else if (i%4 == 2){
				nazev = slovo;
			}else if(i%4 == 3){
				autor = slovo;
			}else if(i%4 == 0){
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
			*/
		}
		file.close();
		cout << "Data byly uspesne nacteny ze souboru!";
		system("pause");
	}
	
	
}


