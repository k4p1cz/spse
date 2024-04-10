library IEEE;
use IEEE.STD_LOGIC_1164.ALL;

entity app is
    Port ( clk : in  STD_LOGIC; -- Clock
           ce : in  STD_LOGIC; -- Chip Enable
           arrival : in  STD_LOGIC; -- Vstup tlačítka (příjezd)
           departure : in  STD_LOGIC; -- Vstup tlačítka (odjezd)
           reset : in  STD_LOGIC; -- Vstup tlačítka (reset)
           display : out  STD_LOGIC_VECTOR (6 downto 0); -- Výstup na sedmisegment
           semaphore : out  STD_LOGIC_VECTOR (1 downto 0)); -- Semafor (2 led diody)
end app;

architecture Behavioral of app is
type state_type is (s0,s1,s2,s3,s4); -- s0-s3 = auta, s4 = plno
signal state, next_state : state_type;	
begin
	SYNC_PROC: process (clk)
   begin
      if rising_edge(clk) then -- Náběžná hrana CLK
			if(ce = '1') then
				if (reset = '1') then
					state <= s0;
				else
					state <= next_state;
				end if;    
			end if;     
      end if;
   end process;
	
	OUTPUT_DECODE: process (state)
   begin
      if(state = s0 or state = s1 or state = s2 or state = s3) then
			semaphore <= "10";
		elsif(state = s4) then
			semaphore <= "01";
		else
			semaphore <= "11";
		end if;
   end process;
	
	NEXT_STATE_DECODE: process (state, departure, arrival)
   begin
      next_state <= state;  
      case (state) is
         when s0 =>
				if(departure = '0' and arrival = '1')then
					next_state <= s1; 
				end if;
         when s1 =>
				if(departure = '1' and arrival = '0')then
					next_state <= s0; 
				elsif(departure = '0' and arrival = '1')then
					next_state <= s2;
				else
					next_state <= s1;
				end if;
        when s2 =>
				if(departure = '1' and arrival = '0')then
					next_state <= s1; 
				elsif(departure = '0' and arrival = '1')then
					next_state <= s3;
				else
					next_state <= s2;
				end if;
			when s3 =>
				if(departure = '1' and arrival = '0')then
					next_state <= s2; 
				elsif(departure = '0' and arrival = '1')then
					next_state <= s4;
				else
					next_state <= s3;
				end if;
			when s4 =>
				if(departure = '1' and arrival = '0')then
					next_state <= s3; 
				elsif(departure = '0' and arrival = '1')then
					next_state <= s4;
				else
					next_state <= s4;
				end if;
			when others => null;
      end case;      
   end process;

	with state select
	display <=  "1111001" when s3,   --1
					"0100100" when s2,   --2
					"0110000" when s1,   --3
					"0011001" when s0,   --4
					"1000000" when s4;   --0

end Behavioral;

