`timescale 1ns/1ns

module NFSR_edited(rst, shift_en, load, clk, seed, par_out, ser_out, ser_in_);
    input rst, shift_en, load, clk, ser_in_;
    output ser_out;
    input[23:0] seed;
    output[23:0] par_out;

    wire f;
    assign f = par_out[0] ^ par_out[5] ^ par_out[6] ^ par_out[9] ^ par_out[17] ^ par_out[22] ^
               (par_out[4] & par_out[13]) ^ (par_out[8] & par_out[16]) ^ (par_out[5] & par_out[11] & par_out[14]) ^
               (par_out[2] & par_out[5] & par_out[8] & par_out[10]) ^ ser_in_;

    Shift_Register_24bit SR24(rst, shift_en, load, clk, f, seed, par_out, ser_out);
endmodule

module Grain(rst, shift_en, load, clk, seed, ser_out);
    input rst, shift_en, load, clk;
    output ser_out;
    input[103:0] seed;
    wire[79:0] par_out_L, seed_lfsr;
    wire[23:0] par_out_N, seed_nfsr;
    wire ser_in_, ser_out_;

    assign seed_nfsr = seed[103:80];
    assign seed_lfsr = seed[79:0];

    LFSR lfsr(0, 1, load, clk, seed_lfsr, par_out_L, ser_in_);
    NFSR_edited nfsr(0, 1, load, clk, seed_nfsr, par_out_N, ser_out_, ser_in_);

    wire h;
    assign h =  par_out_L[0] ^ par_out_L[3] ^
               (par_out_L[1] & par_out_L[2]) ^ par_out_N[0] ^ (par_out_N[1] & par_out_L[5]) ^
               (par_out_N[3] & par_out_L[7]) ^
               (par_out_L[8] & par_out_L[13] & par_out_N[5]) ^ par_out_N[2];

    assign ser_out = ser_out_ ^ h;
endmodule
