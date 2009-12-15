module count1(clk,rst,LS,HS);
	input clk,rst;
	output [3:0]HS,LS;
	reg [3:0]HS,LS;
	reg[26:0]tmp;
	always@(posedge clk)
	begin if(!rst)
					begin
					LS<=0;
					HS<=0;
					tmp<=0;
					end
			else
					tmp<=tmp+1;
					if(tmp==50000000)
					begin
					LS<=LS+1;
					if(LS==10)	
							begin
									HS<=HS+1;
									LS<=0;
					      end
					if(HS==6)
							begin
									HS<=0;
									LS<=0;
							end
					end
	end
endmodule				