module mux2(sel,in1,in2,out,outsel);
input [6:0]in1,in2;
input sel;
output [6:0]out;
output [1:0]outsel;
wire [6:0]in1,in2;
wire sel;
wire [6:0]out;
wire [1:0]outsel;
assign out=sel?in1:in2;    //output module
assign outsel=sel?1:2;     //outsel signal control which LED light works
endmodule