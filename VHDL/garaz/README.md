# GARAZ
- Tlacitky budeme ovladat prijizdejici auta do garaze, jakmile aut bude 5, rozsviti se cervena na semaforu (led) a dalsi auto nebude moci prijet. Dalsim tlacitkem budeme resetovat. Na sedmisegmentu se bude zobrazovat aktualni pocet aut.
## Soubory
- app.vhd - main
- app_test_bench.vhd - test bench pro main
- app_top.vhd - top soubor
- puls.vhd - ke stazeni na intranetu u Ral
- debouncer.vhd - ke stateni na intranetu u Ral
- app_top.bit - vygenerovany programovaci soubor
## Nastaveni pinu
```vhdl
clk : in  STD_LOGIC;
ce : in  STD_LOGIC;
arrival : in  STD_LOGIC;
departure : in  STD_LOGIC;
reset : in  STD_LOGIC;
semaphore : out  STD_LOGIC;
display : out  STD_LOGIC_VECTOR (6 downto 0));
```