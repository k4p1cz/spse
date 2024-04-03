library IEEE;
use IEEE.STD_LOGIC_1164.ALL;

entity app is
    Port ( clk : in  STD_LOGIC;
           ce : in  STD_LOGIC;
           arrival : in  STD_LOGIC;
           departure : in  STD_LOGIC;
           reset : in  STD_LOGIC;
           semaphore : out  STD_LOGIC;
           display : out  STD_LOGIC_VECTOR (6 downto 0));
end app;


architecture spse of app is
	-- state_type a state najdeme v helpu pro meelyho automat
	type state_type is (s0,s1,s2,s3,s4,s5); -- s0-s4 jsou auta a s5 znamena, ze je plno
   signal state, next_state : state_type; 
begin
	SYNC_PROC: process (clk)
   begin
      if rising_edge(clk) then
			if (ce = '1') then
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
      if (state = s5) then
         semaphore <= '1';
      else
         semaphore <= '0';
      end if;
   end process;

	NEXT_STATE_DECODE: process (state, arrival, departure)
   begin
      next_state <= state;
      case (state) is
         when s0 =>
            if (arrival = '1' and departure = '0') then
               next_state <= s1;
            else
					next_state <= s0; -- zustane ve stejnem stavu
				end if;
         when s1 =>
            if (arrival = '1' and departure = '0') then
               next_state <= s2; -- prijezd
            elsif (arrival = '0' and departure = '1') then
					next_state <= s0; -- odjezd
				else
					next_state <= s1; -- prijezd i odjezd
				end if;
         when s2 =>
            if (arrival = '1' and departure = '0') then
               next_state <= s3; -- prijezd
            elsif (arrival = '0' and departure = '1') then
					next_state <= s1; -- odjezd
				else
					next_state <= s2; -- prijezd i odjezd
				end if;
			when s3 => 
				if (arrival = '1' and departure = '0') then
               next_state <= s4; -- prijezd
            elsif (arrival = '0' and departure = '1') then
					next_state <= s2; -- odjezd
				else
					next_state <= s3; -- prijezd i odjezd
				end if;
			when s4 =>
				if (arrival = '1' and departure = '0') then
               next_state <= s5; -- prijezd
            elsif (arrival = '0' and departure = '1') then
					next_state <= s3; -- odjezd
				else
					next_state <= s4; -- prijezd i odjezd
				end if;
			when s5 =>
				if(arrival = '1' and departure = '0') then
					next_state <= s5; -- nemuze prijet dalsi
				elsif (arrival = '0' and departure = '1') then
					next_state <= s4; -- odjezd
				else
					next_state <= s5;
				end if;	
         when others => null;
      end case; 
   end process;
	
	
	with state select
   display
		<= "1111001" when s1,    --1
         "0100100" when s2,    --2
         "0110000" when s3,    --3
         "0011001" when s4,	   --4
         "0010010" when s5,		--5
         "1000000" when others;  --0
end spse;

