# Spojovy seznam C++
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

## To do
1. Overeni, jestli uzivatel opravdu zadal int a ne string
2. Dynamicke zjisteni nazvu .exe
```cpp
	GetModuleFileName(NULL, buffer, MAX_PATH);
	string exePath(buffer);
	string folderPath = "cd " + exePath.substr(0, exePath.find_last_of("\\/"));
	system(folderPath.c_str());
	filename = "" // zde zjisteni nazvu .exe
	system(fileName); // zde pouziti .exe nazvu
```
> [!IMPORTANT]
> Kdyby nahodou nastal nejaky problem, nebo byste behem testovani na neco narazili, vytvorte prosim [ISSUE](https://github.com/k4p1cz/spse/issues) . Do nazvu uvedte, ze mate problem se spojovym seznamem. Diky!