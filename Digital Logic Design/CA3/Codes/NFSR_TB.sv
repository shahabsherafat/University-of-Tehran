`timescale 1ns/1ns

module NFSR_TB();
    logic clk, load;
    logic[23:0] seed;
    wire[23:0] par_out;
    wire ser_out;

    initial begin
        clk = 0;
    end
    always begin
        #20
        clk = ~clk;
    end

    NFSR nfsr(0, 1, load, clk, seed, par_out, ser_out);

    initial begin
        load = 1;
        seed = 24'h44ABA6;

        #25
        load = 0;
    end

endmodule