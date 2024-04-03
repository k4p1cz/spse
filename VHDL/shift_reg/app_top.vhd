library IEEE;
use IEEE.STD_LOGIC_1164.ALL;

entity app_top is
    Port ( mclk : in  STD_LOGIC;
           button : in  STD_LOGIC_VECTOR (4 downto 0);
           switch : in  STD_LOGIC_VECTOR (7 downto 0);
           led : out  STD_LOGIC_VECTOR (7 downto 0));
end app_top;
architecture Behavioral of app_top is
signal mce			: STD_LOGIC := '0';
signal btn_clear	: STD_LOGIC := '0';
signal btn_left	: STD_LOGIC := '0';
signal btn_right	: STD_LOGIC := '0';
signal btn_set		: STD_LOGIC := '0';
begin

CLOCK: entity work.puls port map(
	clk => mclk,
	pulse => mce
);

B_CLEAR: entity work.debouncer port map(
	clk => mclk,
	ce => mce,
	btn_in => button(0),
	btn_posedge => btn_clear
);
B_LEFT: entity work.debouncer port map(
	clk => mclk,
	ce => mce,
	btn_in => button(1),
	btn_posedge => btn_left
);
B_RIGHT: entity work.debouncer port map(
	clk => mclk,
	ce => mce,
	btn_in => button(2),
	btn_posedge => btn_right
);
B_SET: entity work.debouncer port map(
	clk => mclk,
	ce => mce,
	btn_in => button(3),
	btn_posedge => btn_set
);
SHIFT_REG: entity work.app port map(
	clk => mclk,
	ce => mce,
	input => switch,
	clear => btn_clear,
	left => btn_left,
	right => btn_right,
	set => btn_set,
	output => led
);
	


end Behavioral;

