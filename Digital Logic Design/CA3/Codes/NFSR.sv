`timescale 1ns/1ns

module NFSR(rst, shift_en, load, clk, seed, par_out, ser_out);
    input rst, shift_en, load, clk;
    output ser_out;
    input[23:0] seed;
    output[23:0] par_out;

    wire g;
    assign g = par_out[0] ^ par_out[5] ^ par_out[6] ^ par_out[9] ^ par_out[17] ^ par_out[22] ^
               (par_out[4] & par_out[13]) ^ (par_out[8] & par_out[16]) ^ (par_out[5] & par_out[11] & par_out[14]) ^
               (par_out[2] & par_out[5] & par_out[8] & par_out[10]);

    Shift_Register_24bit SR24(rst, shift_en, load, clk, g, seed, par_out, ser_out);
endmodule