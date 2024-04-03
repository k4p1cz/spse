LIBRARY ieee;
USE ieee.std_logic_1164.ALL;
 
ENTITY app_test_bench IS
END app_test_bench;
 
ARCHITECTURE behavior OF app_test_bench IS 
 
    COMPONENT app
    PORT(
         clk : IN  std_logic;
         ce : IN  std_logic;
         arrival : IN  std_logic;
         departure : IN  std_logic;
         reset : IN  std_logic;
         semaphore : OUT  std_logic;
         display : OUT  std_logic_vector(6 downto 0)
        );
    END COMPONENT;
    

   --Inputs
   signal clk : std_logic := '0';
   signal ce : std_logic := '0';
   signal arrival : std_logic := '0';
   signal departure : std_logic := '0';
   signal reset : std_logic := '0';

 	--Outputs
   signal semaphore : std_logic;
   signal display : std_logic_vector(6 downto 0);

   -- Clock period definitions
   constant clk_period : time := 10 ns;
 
BEGIN
 
	-- Instantiate the Unit Under Test (UUT)
   uut: app PORT MAP (
          clk => clk,
          ce => ce,
          arrival => arrival,
          departure => departure,
          reset => reset,
          semaphore => semaphore,
          display => display
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
		wait for clk_period;
		ce <= '1';
		reset <= '0';
		departure <= '0';
		arrival <= '0';
      wait for clk_period*10;
		arrival <= '1';
		wait for clk_period*10;
		arrival <= '0';
		departure <= '1';
		wait for clk_period*10;
		departure <= '0';
		reset <= '1';
		wait for clk_period;
		reset <= '0';

      wait;
   end process;

END;
