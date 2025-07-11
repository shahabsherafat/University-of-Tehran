`timescale 1ns/1ns
`include "A.sv"
`include "ROM.sv"
module A_TB();
    wire[7:0] data_in;
    wire[3:0] address_to_memory;
    wire[15:0] final_output;
    wire done;
    reg[3:0] start_address;
    reg start;
    reg clk;
    reg rst;

    initial begin
        clk = 0;
    end
    initial begin
        forever begin
            #2
            clk = ~clk;
        end
    end

    ROM rom(address_to_memory, data_in);
    DeterminantCalculator_2in2 main(clk, start_address, data_in, address_to_memory, start, done, rst, final_output);

    initial begin

        $dumpfile("out.vcd");
        $dumpvars(0, A_TB);

        rst = 1;
        #5 
        rst = 0;
        start_address = 1;
        #5
        start = 1;

        #40

        rst = 1;
        // start = 0;
        #5
        start = 1; 
        rst = 0;
        start_address = 2;
        #5

        #50

        $finish;

        
    end
endmodule



