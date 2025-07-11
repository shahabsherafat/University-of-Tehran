`timescale 1ns/1ns

module Shift_Register_24bit(rst, shift_en, load, clk, ser_in, par_in, par_out, ser_out);
    input rst, shift_en, load, clk, ser_in;
    output ser_out;
    input[23:0] par_in;
    output[23:0] par_out; 

    genvar i;
    wire[23:0] Q_bar;

    wire first_D;
    assign first_D = (~load & ser_in) | (load & par_in[23]);
    DFF first_dff(rst, shift_en, clk, first_D, par_out[23], Q_bar[23]);

    generate
        for(i = 1; i < 24; i = i + 1) begin
            wire D;
            assign D = (~load & par_out[23 - i + 1]) | (load & par_in[23 - i]);
            DFF dff(rst, shift_en, clk, D, par_out[23 - i], Q_bar[23 - i]);
        end
    endgenerate

    assign ser_out = par_out[0];
endmodule

module Shift_Register_80bit(rst, shift_en, load, clk, ser_in, par_in, par_out, ser_out);
    input rst, shift_en, load, clk, ser_in;
    output ser_out;
    input[79:0] par_in;
    output[79:0] par_out; 

    genvar i;
    wire[79:0] Q_bar;

    wire first_D;
    assign first_D = (~load & ser_in) | (load & par_in[79]);
    DFF first_dff(rst, shift_en, clk, first_D, par_out[79], Q_bar[79]);

    generate
        for(i = 1; i < 80; i = i + 1) begin
            wire D;
            assign D = (~load & par_out[79 - i + 1]) | (load & par_in[79 - i]);
            DFF dff(rst, shift_en, clk, D, par_out[79 - i], Q_bar[79 - i]);
        end
    endgenerate

    assign ser_out = par_out[0];
endmodule