# POSUVNY REGISTR
- Bude shiftovat bud z leva do prava nebo naopak
## Soubory
- app.vhd - main
- app_test_bench.vhd - test bench pro main
- app_top.vhd - top soubor
- puls.vhd - ke stazeni na intranetu u Ral
- debouncer.vhd - ke stateni na intranetu u Ral
## Nastaveni pinu
```vhdl
clk : in  STD_LOGIC;
ce : in  STD_LOGIC; -- chip enable
input : in  STD_LOGIC_VECTOR (7 downto 0);
clear : in  STD_LOGIC;
left : in  STD_LOGIC;
right : in  STD_LOGIC;
set : in  STD_LOGIC;
output : out  STD_LOGIC_VECTOR (7 downto 0)
```