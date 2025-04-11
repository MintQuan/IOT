	component system is
		port (
			clk_clk                            : in    std_logic := 'X'; -- clk
			dht11_0_external_connection_export : inout std_logic := 'X'; -- export
			reset_reset_n                      : in    std_logic := 'X'  -- reset_n
		);
	end component system;

	u0 : component system
		port map (
			clk_clk                            => CONNECTED_TO_clk_clk,                            --                         clk.clk
			dht11_0_external_connection_export => CONNECTED_TO_dht11_0_external_connection_export, -- dht11_0_external_connection.export
			reset_reset_n                      => CONNECTED_TO_reset_reset_n                       --                       reset.reset_n
		);

