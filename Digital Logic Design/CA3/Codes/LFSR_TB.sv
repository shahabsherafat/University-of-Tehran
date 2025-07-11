`timescale 1ns/1ns

module LFSR_TB();
    logic clk, load;
    logic[79:0] seed;
    wire[79:0] par_out;
    wire ser_out;

    initial begin
        clk = 0;
    end
    always begin
        #20
        clk = ~clk;
    end

    LFSR lfsr(0, 1, load, clk, seed, par_out, ser_out);

    initial begin
        load = 1;
        seed = 80'h94D473A40BD028EC0E2A;

        #25
        load = 0;
    end

endmodule