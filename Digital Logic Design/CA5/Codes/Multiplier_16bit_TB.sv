`timescale 1ns/1ns

module Multiplier_16bit_TB();
    reg LA, LB;
    reg[15:0] A, B;
    reg start;
    reg Resetn;
    reg Clock;
    wire Ready;
    wire[31:0] final_output;
    
    initial begin
        Clock = 0;
    end
    initial begin
        forever begin
            #2
            Clock = ~Clock;
        end
    end
    
    Multiplier #(16) multiplier(Clock, Resetn, LA, LB, start, A, B, final_output, Ready);

    initial begin
        $dumpfile("out.vcd");
        $dumpvars(0, Multiplier_16bit_TB);

        Resetn = 0;
        #5
        Resetn = 1;
        #5 

        A = 16'd3545;
        B = 16'd1097;
        LA = 1; LB = 1;
        #5

        LA = 0; LB = 0;
        start = 1;
        #50

        start = 0;
        #5

        A = 16'd9987;
        B = 16'd1122;
        LA = 1; LB = 1;
        #5

        LA = 0; LB = 0;
        start = 1;
        #50

        start = 0;
        #5

        A = 16'd8006;
        B = 16'd1799;
        LA = 1; LB = 1;
        #5

        LA = 0; LB = 0;
        start = 1;
        #50

        start = 0;
        #5

        A = 16'd5122;
        B = 16'd13212;
        LA = 1; LB = 1;
        #5

        LA = 0; LB = 0;
        start = 1;
        #50

        start = 0;
        #5

        A = 16'd60095;
        B = 16'd58216;
        LA = 1; LB = 1;
        #5

        LA = 0; LB = 0;
        start = 1;
        #50

        start = 0;
        #5

        $finish;
    end
endmodule