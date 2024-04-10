library IEEE;
use IEEE.STD_LOGIC_1164.ALL;

entity app_top is
    Port ( mclk : in  STD_LOGIC; -- master CLK
           btn : in  STD_LOGIC_VECTOR (2 downto 0); -- Tlačítka
           led : out  STD_LOGIC_VECTOR (1 downto 0); -- LED diody
           seg : out  STD_LOGIC_VECTOR (6 downto 0); -- Sedmisegment
           an : out  STD_LOGIC_VECTOR (3 downto 0)); -- Anoda
end app_top;

architecture Behavioral of app_top is
signal mce : STD_LOGIC := '0'; -- master Chip Enable
signal btn_arr : STD_LOGIC := '0'; -- Tlačítko příjezdu
signal btn_dep : STD_LOGIC := '0'; -- Tlačítko odjezdu
signal btn_res : STD_LOGIC := '0'; -- Tlačítko reset
begin
	CLOCK: entity work.puls port map(
		clk => mclk,
		pulse => mce
	);
	BTN_ARRIVAL: entity work.debouncer port map(
		clk => mclk,
		ce => mce,
		btn_in => btn(0),
		btn_posedge => btn_arr 
	);
	BTN_DEPARTURE: entity work.debouncer port map(
		clk => mclk,
		ce => mce,
		btn_in => btn(1),
		btn_posedge => btn_dep 
	);
	BTN_RESET: entity work.debouncer port map(
		clk => mclk,
		ce => mce,
		btn_in => btn(2),
		btn_posedge => btn_res
	);
	APP: entity work.app port map(
		clk => mclk,
		ce => mce,
		arrival => btn_arr,
		departure => btn_dep,
		reset => btn_res,
		display => seg,
		semaphore => led
	);
	an <= "1110";
	


end Behavioral;

