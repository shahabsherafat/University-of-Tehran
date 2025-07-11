
module Datapath(clk, x_in, n_iter, en1, en2, en3, en4, rst2, sel1, sel2, LA, LB, s, ready, iter_end, x_inv, mul_rst);
    parameter n = 8;
    input[n-1:0] x_in;
    input[3:0] n_iter;
    output[n+n-1:0] x_inv;

    //Now controlling variables:
    input clk,  en1, en2, en3, en4, rst2, sel1, sel2, LA, LB, s, mul_rst;
    output iter_end, ready;

    wire[3:0] count;
    Counter_4bit counter(clk, rst2, en2, 4'b0000, count);
    assign iter_end = (count == n_iter);

    wire[n-1:0] x;
    regne #(n) x_reg(x_in, clk, 1'b1, en1, x);

    wire[n+n-1:0] w1, next_y, in1;
    assign w1 = sel1 ? {next_y[n+n-3:0], 2'b00} : {1'b0, 1'b1, {(n+n-2){1'b0}}};
    regne #(n+n) y_reg(w1, clk, 1'b1, en3, in1);

    wire[n-1:0] in2;
    wire[n+n-1:0] subbed;
    assign in2 = sel2 ? subbed[n+n-1:n] : x;

    Multiplier #(n) multiplier(clk, mul_rst, LA, LB, s, in1[n+n-1:n], in2, next_y, ready);

    wire[n+n-1:0] w2;
    regne #(n+n) reg_mul1({next_y[n+n-3:0], 2'b00}, clk, 1'b1, en4, w2);

    Subtractor #(n+n) subtractor({1'b1, {(n+n-1){1'b0}}}, w2, subbed);
    assign x_inv = in1;
endmodule