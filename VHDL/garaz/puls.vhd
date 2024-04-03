library IEEE;
use IEEE.STD_LOGIC_1164.ALL;
use IEEE.STD_LOGIC_ARITH.ALL;

entity puls is
  generic (
      div_factor  : integer := 50000);  -- 100 ms
  port(
      clk   : in std_logic;
      pulse : out std_logic
  );
end puls;

Architecture Behavioral of puls is
signal counter : integer := 0;

begin
process(clk)
  begin
    if(rising_edge(clk)) then        
        if counter = div_factor - 1 then
            pulse <= '1';
            counter <= 0;
        else
            counter <= counter + 1;
            pulse <= '0';
        end if;
    end if;
end process;
end Behavioral;
