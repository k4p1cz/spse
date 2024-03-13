LIBRARY ieee;
USE ieee.std_logic_1164.ALL;
 
-- Uncomment the following library declaration if using
-- arithmetic functions with Signed or Unsigned values
--USE ieee.numeric_std.ALL;
 
ENTITY app_test_bench IS
END app_test_bench;
 
ARCHITECTURE behavior OF app_test_bench IS 
 
    -- Component Declaration for the Unit Under Test (UUT)
 
    COMPONENT app
    PORT(
         clk : IN  std_logic;
         ce : IN  std_logic;
         input : IN  std_logic_vector(7 downto 0);
         clear : IN  std_logic;
         left : IN  std_logic;
         right : IN  std_logic;
         set : IN  std_logic;
         output : OUT  std_logic_vector(7 downto 0)
        );
    END COMPONENT;
    

   --Inputs
   signal clk : std_logic := '0';
   signal ce : std_logic := '0';
   signal input : std_logic_vector(7 downto 0) := (others => '0');
   signal clear : std_logic := '0';
   signal left : std_logic := '0';
   signal right : std_logic := '0';
   signal set : std_logic := '0';

 	--Outputs
   signal output : std_logic_vector(7 downto 0);

   -- Clock period definitions
   constant clk_period : time := 10 ns;
 
BEGIN
 
	-- Instantiate the Unit Under Test (UUT)
   uut: app PORT MAP (
          clk => clk,
          ce => ce,
          input => input,
          clear => clear,
          left => left,
          right => right,
          set => set,
          output => output
        );

   -- Clock process definitions
   clk_process :process
   begin
		clk <= '0';
		wait for clk_period/2;
		clk <= '1';
		wait for clk_period/2;
   end process;
 

   -- Stimulus process
   stim_proc: process 
   begin		
      -- hold reset state for 100 ns.
      wait for 100 ns;	

      wait for clk_period*10;
		ce <= '1';
		clear <= '0';
		input <= "00110011";
		wait for clk_period;
		set <= '1';
		wait for clk_period;
		set <= '0';
		left <= '1';
		wait for clk_period;
		left <= '0';
		wait for clk_period*100;
		right <= '1';
		wait for clk_period;
		right <= '0';
		wait for clk_period*100;
		clear <= '1';
      wait;
   end process;

END;
