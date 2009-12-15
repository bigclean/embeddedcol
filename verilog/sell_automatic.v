`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date:    12:51:36 12/17/2008 
// Design Name: 
// Module Name:    autoseller 
// Project Name: 
// Target Devices: 
// Tool versions: 
// Description: 
//
// Dependencies: 
//
// Revision: 
// Revision 0.01 - File Created
// Additional Comments: 
//
//////////////////////////////////////////////////////////////////////////////////
module autoseller(one_dollar,half_dollar,collect,
            half_out,dispense,reset,clk);

parameter idle=0,a=1,b=2,c=3,d=4;
      //idle,half,one,two,three为中间状态变量，代表投入币值的几种情况 

input one_dollar,half_dollar,reset,clk;
output collect,half_out,dispense;
reg collect,half_out,dispense;
reg [2:0]D;
reg[25:0]tmp;

always @(posedge clk) 
		begin 
      if (!reset) 
		begin
          dispense <=0;collect<=0;half_out<=0;D<=idle;tmp<=0;
      end
		tmp<=tmp+1;
		if(tmp==50000000)
		begin
      case(D)
         idle:   begin
						if(!half_dollar) D<=a;
						else if (!one_dollar) begin D<= b; end
					  tmp<=0;
					  end
            a:   begin
						if(!half_dollar) D<=b;
                 else if (!one_dollar) begin D<= c;end
					  tmp<=0;
					  end
            b:   begin
					if(!half_dollar) D<=c;
                 else if (!one_dollar) begin D<=d; end
					  tmp<=0;
					  end
            c:   begin
					if(!half_dollar) D<=d;
                 else if (!one_dollar)
                   begin
                    dispense<=1;
                    collect<=1; D<=idle;
                   end
						 tmp<=0;
						 end
             d:   begin
					if(!half_dollar)
                    begin
                      collect<=1;D<=idle;
                    end
                   else if(!one_dollar)
                    begin
                     dispense<=1;collect<=1;    //售出饮料
                     half_out<=1;D<=idle;       //找零
                    end
						  tmp<=0;
						  end
               endcase
         end
			end
endmodule  