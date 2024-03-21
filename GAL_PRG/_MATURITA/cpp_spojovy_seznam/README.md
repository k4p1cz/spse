# Spojovy seznam C++
## Popis
- Vhodne na pripravu k maturite
- Udelal jsem par veci jinak, nez v lavici
	- Misto toho ukladat data primo do projektu je ukladam do appdata/roaming
	- V uzlu mam pouze jeden parametr - cele cislo
		- U maturity urcite bude zadani s vice parametry, ale hlavni princip spojoveho seznamu je stale stejny
- Co si myslim, ze neni vyreseno spravne/mohlo by se udelat jinak
	- Hodnekrat jsem pouzil for loop
		- Nevim, jestli to je z dlouhodobeho hlediska spravne reseni
	- Vsechny funkce nemaji navratovou hodnotu
		- Bylo by vhodne je minimalne predelat na typ bool a v main.cpp overovat jejich ocekavany prubeh
> [!NOTE]
> Je mozne, ze me reseni neni nejlepsi (nejsem expert pres C++). Pokud mate lepsi napad, jak neco vyresit, vytvorte prosim [ISSUE](https://github.com/k4p1cz/spse/issues). Do nazvu uvedte, ze mate napad na vylepseji spojoveho seznamu. Diky!
## Obsahuje
1. Pridani zaznamu na zacatek
2. Pridani zaznamu na konec
3. Zapsat seznam do souboru
4. Nacist seznam ze souboru
5. Vypsat seznam
6. Odstranit zaznam
7. Duplikovat zaznam (vcetne vyberu na jakou pozici zaznam duplikovat)
8. Otevrit slozku s daty (data se ukladaji do %appdata% - toto tu slozku rovnou otevre)
9. Vymazat slozku s daty (vymaze appdata a apka se restartuje)
10. Existence slozek v AppData se overuje automaticky na zacatku programu

## To do
1. Overeni, jestli uzivatel opravdu zadal int a ne string
2. Dynamicke zjisteni nazvu .exe
```cpp
	GetModuleFileName(NULL, buffer, MAX_PATH);
	string exePath(buffer);
	string folderPath = "cd " + exePath.substr(0, exePath.find_last_of("\\/"));
	system(folderPath.c_str());
	fileName = "" // zde zjisteni nazvu .exe
	system(fileName); // zde pouziti .exe nazvu
```
> [!IMPORTANT]
> Kdyby nahodou nastal nejaky problem, nebo byste behem testovani na neco narazili, vytvorte prosim [ISSUE](https://github.com/k4p1cz/spse/issues) . Do nazvu uvedte, ze mate problem se spojovym seznamem. Diky!