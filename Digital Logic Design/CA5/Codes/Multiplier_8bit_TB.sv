`timescale 1ns/1ns

module Multiplier_8bit_TB();
    reg LA, LB;
    reg[7:0] A, B;
    reg start;
    reg Resetn;
    reg Clock;
    wire Ready;
    wire[15:0] final_output;
    
    initial begin
        Clock = 0;
    end
    initial begin
        forever begin
            #2
            Clock = ~Clock;
        end
    end
    
    Multiplier #(8) multiplier(Clock, Resetn, LA, LB, start, A, B, final_output, Ready);

    initial begin
        $dumpfile("out.vcd");
        $dumpvars(0, Multiplier_8bit_TB);

        Resetn = 0;
        #5
        Resetn = 1;
        #5 

        A = 8'd35;
        B = 8'd107;
        LA = 1; LB = 1;
        #5

        LA = 0; LB = 0;
        start = 1;
        #50

        start = 0;
        #5

        A = 8'd87;
        B = 8'd12;
        LA = 1; LB = 1;
        #5

        LA = 0; LB = 0;
        start = 1;
        #50

        start = 0;
        #5

        A = 8'd86;
        B = 8'd179;
        LA = 1; LB = 1;
        #5

        LA = 0; LB = 0;
        start = 1;
        #50

        start = 0;
        #5

        A = 8'd52;
        B = 8'd112;
        LA = 1; LB = 1;
        #5

        LA = 0; LB = 0;
        start = 1;
        #50

        start = 0;
        #5

        A = 8'd95;
        B = 8'd216;
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