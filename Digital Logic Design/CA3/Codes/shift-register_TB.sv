`timescale 1ns/1ns

module Shift_Register_24bit_TB();
    logic clk, en, rst, load, ser_in, ser_out;
    logic[23:0] par_in, par_out;

    initial begin
        clk = 0;
        load = 0;
        ser_in = 0;
        ser_out = 0;
        en = 0;
        rst = 0;
    end
    always begin
        #20
        clk = ~clk;
    end

    Shift_Register_24bit SR24(rst, en, load, clk, ser_in, par_in, par_out, ser_out);

    initial begin
        load = 1;
        par_in =24'b100111001010011001010010;
        en = 1;

        #25
        rst = 1;

        #70
        rst = 0;

        #10
        load = 0;

        #35
        rst = 0;
        en = 1;

        #45
        en = 0;

        #25
        ser_in = 1;
        en = 1;

        #40
        ser_in = 0;
    end

endmodule

module Shift_Register_80bit_TB();
    logic clk, en, rst, load, ser_in, ser_out;
    logic[23:0] par_in, par_out;

    initial begin
        clk = 0;
        load = 0;
        ser_in = 0;
        ser_out = 0;
        en = 0;
        rst = 0;
    end
    always begin
        #20
        clk = ~clk;
    end

    Shift_Register_80bit SR80(rst, en, load, clk, ser_in, par_in, par_out, ser_out);

    initial begin
        load = 1;
        par_in = 80'b10010101010111001101100010111001010101011100110110001011100101010101110011011000;
        en = 1;

        #25
        rst = 1;

        #70
        rst = 0;

        #10
        load = 0;

        #35
        rst = 0;
        en = 1;

        #45
        en = 0;

        #25
        ser_in = 1;
        en = 1;

        #40
        ser_in = 0;
    end

endmodule