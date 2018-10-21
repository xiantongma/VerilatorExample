module tb(
	input clk,
	input rstb	
);
	bit [31:0] mem [0:15];
	initial begin
		$display("hello");
		$readmemh("flash.in", mem);
		for (int i=0; i<4; i++) begin
			$display("%08x",mem[i]);
		end
		//#5ms;
		//#5;
	end

	int cycle =0;
	always @(posedge clk)
		cycle <= cycle + 1;

	always @(posedge clk)
		if (cycle ==100) begin
			$display("%t ns %m", $time);
			$finish;
		end
		
endmodule
