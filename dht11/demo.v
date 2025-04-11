module demo
(
input 	  	 CLOCK_50,
input  [0:0] KEY,
inout  reg dht11
);
system nios_system(
.clk_clk(CLOCK_50),
.reset_reset_n(KEY[0]),
.dht11_0_external_connection_export(dht11)
);
endmodule