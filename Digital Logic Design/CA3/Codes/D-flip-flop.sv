`timescale 1ns/1ns

module DFF(rst, en, clk, D, Q, Q_bar);
    input D, rst, en, clk;
    output Q, Q_bar;
    wire Qm, Qm_bar, clk_bar;
    D_Latch master(rst, 1'b1, clk_bar, D, Qm, Qm_bar);
    not not1(clk_bar, clk);
    D_Latch slave(rst, en, clk, Qm, Q, Q_bar);
endmodule

