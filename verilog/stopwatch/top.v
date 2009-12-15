module top(clk,rst,out,outsel);
input clk,rst;
output [6:0]out;
output [1:0]outsel;
wire [6:0]HS,LS;
wire [6:0]out1,out2;
wire sel;
count1 a1(clk,rst,LS,HS);  //genereate HS and LS signal
display  a2(LS,out1);    //Decoder signal out1
display  a3(HS,out2);
selgen   a4(clk,rst,sel);
mux2  a5(out1,out2,sel,out,outsel);
endmodule