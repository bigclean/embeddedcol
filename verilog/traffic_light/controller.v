module controller(clk,rst,en5,en25,fin5,fin25,
							r1,y1,g1,r2,y2,g2);
input clk,rst,fin5,fin25;
output en5,en25,r1,y1,g1,r2,y2,g2;
reg en5,en25,r1,y1,g1,r2,y2,g2;
reg [1:0]state;
parameter S0=0,S1=1,S2=2,S3=3;
always @(posedge clk)
	begin
	   if(!rst)	begin
						r1=0;y1=0;g1=0;
						r2=0;y2=0;g2=0;
						en5=0;en25=0;
				   end
	   else     begin
				   case(state)
				   S0:   begin
							y1=1;g1=1;r1=0;
							r2=1;y2=1;g2=0;
							en25=1;en5=0;
							if(fin25==1)  state=S1;
				         end
				   S1:   begin
							y1=1;g1=1;r1=0;
							r2=1;g2=1;y2=0;
							en25=0;en5=1;
							if(fin5==1)  state=S2;
					      end
				   S2:   begin
							y1=1;r1=1;g1=0;
							g2=1;y2=1;r2=0;
							en25=1;en5=0;
							if(fin25==1)  state=S3;
					      end
				   S3:   begin
							r1=1;g1=1;y1=0;
							g2=1;y2=1;r2=0;
							en25=0;en5=1;
							if(fin5==1)  state=S0;
					      end
				   endcase
				end
	   end
	endmodule