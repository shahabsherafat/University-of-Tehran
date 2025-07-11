`timescale 1ns/1ns

module Reciprocal_TB();
    reg[16-1:0] x_in;
    reg[3:0] n_iter;
    wire[16+16-1:0] x_inv;

    reg clk, req, rst;
    reg ack;

    initial begin
        clk = 0;
    end
    initial begin
        forever begin
            #2
            clk = ~clk;
        end
    end

    Reciprocal main(clk, req, x_in, n_iter, rst, ack, x_inv);

    initial begin
        $dumpfile("out.vcd");
        $dumpvars(0, Reciprocal_TB);

        rst = 1;
        #5 

        rst = 0;
        x_in = 8'b01110100;
        n_iter = 15;
        #4

        req = 1;
        #2000

        $finish;
    end
endmodule
