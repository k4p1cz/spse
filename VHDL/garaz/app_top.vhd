library IEEE;
use IEEE.STD_LOGIC_1164.ALL;

entity app_top is
    Port ( mclk : in  STD_LOGIC;
           btn : in  STD_LOGIC_VECTOR (2 downto 0);
           led0 : out  STD_LOGIC;
           seg : out  STD_LOGIC_VECTOR (6 downto 0);
           an : out  STD_LOGIC_VECTOR (3 downto 0));
end app_top;

architecture Behavioral of app_top is
signal mce : STD_LOGIC := '0';
signal sem : STD_LOGIC := '0';
signal btn_arr : STD_LOGIC := '0';
signal btn_res : STD_LOGIC := '0';
signal btn_dep : STD_LOGIC := '0';
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
	Inst_app: entity work.app PORT MAP(
		clk => mclk,
		ce => mce,
		arrival => btn_arr,
		departure => btn_dep,
		reset => btn_res,
		semaphore => led0,
		display => seg
	);
	
	an <= "1110";
	


end Behavioral;

