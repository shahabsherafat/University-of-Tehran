`timescale 1ns/1ns

module ComparatorTB();
    logic[3:0] inp1, inp2;
    wire eq, gt, lt;
    Comparator_4_bit_signed cmp(inp1, inp2, eq, gt, lt);
    initial begin
        inp1 = 4'b1011;
        inp2 = 4'b0010;
        #50
        inp1 = 4'b0111;
        inp2 = 4'b0101;
        #50
        inp1 = 4'b1111;
        inp2 = 4'b1111;
        #50
        inp1 = 4'b1011;
        inp2 = 4'b1010;
    end
endmodule

module CLATB();
    logic[3:0] inp1, inp2;
    logic cin;
    wire[3:0] out;
    wire overflow;
    CarryLookaheadAdder_4bit_signed cla(inp1, inp2, cin, out, overflow);

    initial begin
        inp1 = 4'b1011;
        inp2 = 4'b0010;
        cin = 1'b0;
        #50
        inp1 = 4'b0111;
        inp2 = 4'b0101;
	cin = 1'b0;
        #50
        inp1 = 4'b1111;
        inp2 = 4'b1111;
	cin = 1'b1;
        #50
        inp1 = 4'b1011;
        inp2 = 4'b1010;
	cin = 1'b1;
	#50
        inp1 = 4'b0110;
        inp2 = 4'b1010;
	cin = 1'b0;
	#50
        inp1 = 4'b0010;
        inp2 = 4'b0110;
	cin = 1'b1;
    end
endmodule

module ALUTB();
    logic[3:0] inp1, inp2;
    logic[2:0] Opc;
    wire[3:0] out;
    wire overflow;
    ALU alu(Opc, inp1, inp2, out, overflow);

    initial begin
        inp1 = 4'b0011;
        inp2 = 4'b1010;
        Opc = 3'b001;
        #10
        inp1 = 4'b1001;
        inp2 = 4'b1011;
	Opc = 3'b001;
        #10
        inp1 = 4'b0110;
        inp2 = 4'b0010;
	Opc = 3'b001;
        #10

        inp1 = 4'b0011;
        inp2 = 4'b1010;
        Opc = 3'b010;
        #10
        inp1 = 4'b1001;
        inp2 = 4'b1011;
	Opc = 3'b010;
        #10
        inp1 = 4'b0110;
        inp2 = 4'b0010;
	Opc = 3'b010;
        #10

        inp1 = 4'b0011;
        inp2 = 4'b1010;
        Opc = 3'b011;
        #10
        inp1 = 4'b1001;
        inp2 = 4'b1011;
	Opc = 3'b011;
        #10
        inp1 = 4'b0110;
        inp2 = 4'b0010;
	Opc = 3'b011;
        #10

        inp1 = 4'b0011;
        inp2 = 4'b1010;
        Opc = 3'b100;
        #10
        inp1 = 4'b1001;
        inp2 = 4'b1011;
	Opc = 3'b100;
        #10
        inp1 = 4'b0110;
        inp2 = 4'b0010;
	Opc = 3'b100;
        #10

        inp1 = 4'b0011;
        inp2 = 4'b1010;
        Opc = 3'b101;
        #10
        inp1 = 4'b1001;
        inp2 = 4'b1011;
	Opc = 3'b101;
        #10
        inp1 = 4'b0110;
        inp2 = 4'b0010;
	Opc = 3'b101;
        #10

        inp1 = 4'b0011;
        inp2 = 4'b1010;
        Opc = 3'b110;
        #10
        inp1 = 4'b1001;
        inp2 = 4'b1011;
	Opc = 3'b110;
        #10
        inp1 = 4'b0110;
        inp2 = 4'b0010;
	Opc = 3'b110;
        #10

        inp1 = 4'b0011;
        inp2 = 4'b1010;
        Opc = 3'b111;
        #10
        inp1 = 4'b1001;
        inp2 = 4'b1011;
	Opc = 3'b111;
        #10
        inp1 = 4'b0110;
        inp2 = 4'b0010;
	Opc = 3'b111;
        #10 
        
        Opc = 3'b000;
    end
endmodule

module Top_Module_TB();
    logic[15:0] inp1, inp2;
    logic[2:0] Opc;
    wire[15:0] out;
    wire overflow;
    Top_Module tm(Opc, inp1, inp2, out, overflow);

    initial begin
        inp1 = 16'b0000000000001000;
        inp2 = 16'b0000010000000000;
        Opc = 3'b001;
        #10
        inp1 = 16'b0000001000000000;
        inp2 = 16'b0000100000000000;
	Opc = 3'b001;
        #10
        inp1 = 16'b0000000001000000;
        inp2 = 16'b0000000000000100;
	Opc = 3'b001;
        #10

        inp1 = 16'b0000000000001000;
        inp2 = 16'b0000010000000000;
        Opc = 3'b010;
        #10
        inp1 = 16'b0000001000000000;
        inp2 = 16'b0000100000000000;
	Opc = 3'b010;
        #10
        inp1 = 16'b0000000001000000;
        inp2 = 16'b0000000000000100;
	Opc = 3'b010;
        #10

        inp1 = 16'b0000000000001000;
        inp2 = 16'b0000010000000000;
        Opc = 3'b011;
        #10
        inp1 = 16'b0000001000000000;
        inp2 = 16'b0000100000000000;
	Opc = 3'b011;
        #10
        inp1 = 16'b0000000001000000;
        inp2 = 16'b0000000000000100;
	Opc = 3'b011;
        #10

        inp1 = 16'b0000000000001000;
        inp2 = 16'b0000010000000000;
        Opc = 3'b100;
        #10
        inp1 = 16'b0000001000000000;
        inp2 = 16'b0000100000000000;
	Opc = 3'b100;
        #10
        inp1 = 16'b0000000001000000;
        inp2 = 16'b0000000000000100;
	Opc = 3'b100;
        #10

        inp1 = 16'b0000000000001000;
        inp2 = 16'b0000010000000000;
        Opc = 3'b101;
        #10
        inp1 = 16'b0000001000000000;
        inp2 = 16'b0000100000000000;
	Opc = 3'b101;
        #10
        inp1 = 16'b0000000001000000;
        inp2 = 16'b0000000000000100;
	Opc = 3'b101;
        #10

        inp1 = 16'b0000000000001000;
        inp2 = 16'b0000010000000000;
        Opc = 3'b110;
        #10
        inp1 = 16'b0000001000000000;
        inp2 = 16'b0000100000000000;
	Opc = 3'b110;
        #10
        inp1 = 16'b0000000001000000;
        inp2 = 16'b0000000000000100;
	Opc = 3'b110;
        #10

        inp1 = 16'b0000000000001000;
        inp2 = 16'b0000010000000000;
        Opc = 3'b111;
        #10
        inp1 = 16'b0000001000000000;
        inp2 = 16'b0000100000000000;
	Opc = 3'b111;
        #10
        inp1 = 16'b0000000001000000;
        inp2 = 16'b0000000000000100;
	Opc = 3'b111;
        #10
        
        Opc = 3'b000;
    end
endmodule