`timescale 1ns/1ns

module D_Latch(rst, en, clk, D, Q, Q_bar);
    input rst, en, clk, D;
    output Q, Q_bar;
    wire active, D_bar, w1, w2, rst_bar;

    not not1(D_bar, D);
    not not2(rst_bar, rst);
    //Asynchronous enable:
    and a1(active, clk, en);
    nand n1(w1, D, active, rst_bar);
    nand n2(w2, D_bar, active);

    nand n3(Q, w1, Q_bar);
    nand n4(Q_bar, w2, Q, rst_bar);
endmodule