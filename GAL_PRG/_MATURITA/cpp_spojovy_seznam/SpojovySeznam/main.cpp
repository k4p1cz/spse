#include "header.h"

int main() {
	int pocet;
	float prumer;
	char volba;
	Knihy x;
	Seznam s;
	
	do{
		//Uzivatelska nabidka
		cout <<  "------------------------------" << endl;
		cout << "a.) Pridej knihu na zacatek" << endl;
		cout << "b.) Pridej knihu na konec" << endl;
		cout << "c.) Pocet knih" << endl;
		cout << "d.) Vypis seznam" << endl;
		cout << "e.) Prumerna cena knihy" << endl;
		cout << "f.) Pridani ze seznamu do souboru" << endl;
		cout << "g.) Pridani ze souboru do seznamu" << endl;
		cout << "h.) Vyhledani podle polozky" << endl;
		cout << "i.) Uprava knihy podle ID" << endl;
		cout << "j.) Odstraneni knihy" << endl;
		cout << "k.) Pocet knih od zadaneho autora" << endl;
		cout << "l.) Minimalni a maximalni cena knihy" << endl;
		cout << "m.) Seradit knihy v seznamu" << endl;
		cout << "x.) Konec" << endl;
		cout <<  "------------------------------" << endl;
		cin >> volba;
		
		switch(volba){
		case 'a':
			cin >> x;
			s.pridejNaZacatek(x.getCislo(), x.getNazev(), x.getAutor(), x.getCena());
			break;
			
		case 'b':
			cin >> x;
			s.pridejNaKonec(x.getCislo(), x.getNazev(), x.getAutor(), x.getCena());
			break;
			
		case 'c':
			pocet = s.pocetKnih();
			cout << "Pocet knih v seznamu je: " << pocet << endl;
			break;
			
		case 'd':
			s.vypisSeznam();
			break;
			
		case 'e':
			prumer = s.Prumer();
			if(prumer == 0){
				cout << "Seznam je prazdny" << endl;
			}
			else{
				cout << "Prumerna cena je: " << prumer << endl;	
			}
			break;
			
		case 'f':
			s.doSouboru();
			break;
			
		case 'g':
			s.zeSouboru();
			break;
			
		case 'h':
			s.Vyhledat();
			break;
			
		case 'i':
			s.Upravit();
			break;
			
		case 'j': 
			s.Odstranit();
			break;
		
		case 'k': 
			s.pocetDelAutor();
			break;
			
		case 'l':
			s.minMax();
			break;
			
		case 'm':
			s.Seradit();
			break;
		}
		
	}while(volba != 'x');
	
	system ("pause");
	return 0;
}
