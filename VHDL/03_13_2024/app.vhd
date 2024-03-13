-- posuvny registr

library IEEE;
use IEEE.STD_LOGIC_1164.ALL;

entity app is
    Port ( clk : in  STD_LOGIC;
           ce : in  STD_LOGIC; -- chip enable
           input : in  STD_LOGIC_VECTOR (7 downto 0);
           clear : in  STD_LOGIC;
           left : in  STD_LOGIC;
           right : in  STD_LOGIC;
           set : in  STD_LOGIC;
           output : out  STD_LOGIC_VECTOR (7 downto 0));
end app;

architecture Behavioral of app is
signal pattern: STD_LOGIC_VECTOR (7 downto 0) := (others => '0'); -- interni promenna
signal direction: STD_LOGIC := '0'; -- interni promenna
-- ":=" pouzivame proto, jelikoz : je PRIRAZENI
signal delay : natural := 100;
begin
	process(clk, ce, input, clear, left, right, set) -- process pouzivame, 
	begin
		if rising_edge(clk) then -- pokud je clk v nabezne hrane
			if ce = '1' then
				if set = '1' then
					pattern <= input; -- nahrajeme do interni promenne pattern
				elsif clear = '1' then
					pattern <= (others => '0'); -- pokud clear je v 1 tak nastavime pattern na 0
				elsif left = '1' then	
					direction <= '0';
				elsif right = '1' then
					direction <= '1';
				else
					if delay = 0 then
						if direction = '0' then
							pattern <= pattern(6 downto 0) & pattern(7); -- posunuti o jedno do leva 
						else
							pattern <= pattern(0) & pattern(7 downto 1); -- posunuti o jedno do prava
						end if;
						-- & = PRILEPIT
						-- nejprve kopirujeme prvnich x bitu a k tomu priradime 0/7 bit
						delay <= 100;
					else
						delay <= delay - 1;
					end if;
				end if;
			end if;
		end if;
	end process;
	output <= pattern;
end Behavioral;

