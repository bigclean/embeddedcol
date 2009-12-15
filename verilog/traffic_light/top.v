module top(clk,rst,r1,y1,g1,r2,y2,g2);
input clk,rst;
output r1,y1,g1,r2,y2,g2;
wire fin5,fin25,en5,en25;
controller m1(clk,rst,en5,en25,fin5,fin25,r1,y1,g1,r2,y2,g2);
time25 m2(clk,rst,en25,fin25);
time5  m3(clk,rst,en5,fin5);
endmodule