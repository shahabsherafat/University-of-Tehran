`timescale 1ns/1ns

module D_flip_flop_TB();
    logic clk, en, rst, D;
    wire Q, Q_bar;

    initial begin
        clk = 0;
        D = 0;
        en = 0;
        rst = 0;
    end
    always begin
        #20
        clk = ~clk;
    end

    DFF test_dff(rst, en, clk, D, Q, Q_bar);

    initial begin
        #10
        D = 1;
        en = 1;

        #15
        en = 0;

        #5
        D = 0;

        #5
        rst = 1;

        #5
        rst = 0;

        #15
        en = 1;

        #10
        rst = 1;

        #5
        D = 1;

        #35
        rst = 0;

        #5
        D = 0;

        #15
        en = 0;

        #30
        D = 1;

        #25
        en = 1;
    end

endmodule