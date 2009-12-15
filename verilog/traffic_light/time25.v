module time25(clk,rst,en25,fin25);
input clk,rst,en25;
output fin25;
reg fin25;
reg [40:0]tmp;
always @(posedge clk)
begin	if(!rst||!en25)    begin
					          tmp<=0;
					          fin25<=0;
								 end
			else begin
					tmp<=tmp+1;
					if(tmp==250000000)
							begin
							fin25<=1;
							tmp<=0;
							end
					end
end
endmodule