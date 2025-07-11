`timescale 1ns/1ns

module LFSR(rst, shift_en, load, clk, seed, par_out, ser_out);
    input rst, shift_en, load, clk;
    output ser_out;
    input[79:0] seed;
    output[79:0] par_out;

    wire f;
    xor x1(f, par_out[62], par_out[51], par_out[38], par_out[23], par_out[13], par_out[0]);

    Shift_Register_80bit SR80(rst, shift_en, load, clk, f, seed, par_out, ser_out);
endmodule
