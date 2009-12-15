module display(in,out);
input [3:0]in;
output [6:0]out;
wire[3:0]in;
reg [6:0]out;
always @( in)
begin 
		case(in)
		4'd0:out=7'b0111_111;
		4'd1:out=7'b0000_110;
		4'd2:out=7'b1011_011;
		4'd3:out=7'b1001_111;
		4'd4:out=7'b1100_110;
		4'd5:out=7'b1101_101;
		4'd6:out=7'b1111_101;
		4'd7:out=7'b0000_111;
		4'd8:out=7'b1111_111;
		4'd9:out=7'b1101_111;
		default:out=7'b1111_111;
		endcase
end
endmodule