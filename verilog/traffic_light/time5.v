module time5(clk,rst,en5,fin5);
input clk,rst,en5;
output fin5;
reg fin5;
reg [40:0]tmp;
always @(posedge clk)
begin	if(!rst||!en5)  begin
					           tmp<=0;
					           fin5<=0;
					           end
			else begin
					tmp<=tmp+1;
					if(tmp==50000000)
							begin
							fin5<=1;
							tmp<=0;
							end
					end
end
endmodule