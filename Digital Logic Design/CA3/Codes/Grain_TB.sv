`timescale 1ns/1ns

module Grain_TB();
    logic clk, load;
    logic[103:0] seed;
    wire ser_out;

    initial begin
        clk = 0;
    end
    always begin
        #20
        clk = ~clk;
    end

    Grain grain(0, 1, load, clk, seed, ser_out);

    initial begin
        load = 1;
        seed = 104'h44ABA694D473A40BD028EC0E2A;

        #25
        load = 0;
    end
endmodule