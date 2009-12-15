module selgen(clk,rst,sel);
	input clk,rst;
	output sel;
	reg [20:0]tmp;
	reg sel;
	always @(posedge clk)
	begin	if(!rst)	
				begin
				tmp<=0;
				sel<=1;
				end
				else
				begin
						tmp<=tmp+1;
						if(tmp==500000)
		           						sel<=sel+1;
				end
    end
endmodule