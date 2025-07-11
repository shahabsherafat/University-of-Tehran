
module Reciprocal(clk, req, x_in, n_iter, rst, ack, x_inv);
    parameter n = 8;
    input[n-1:0] x_in;
    input[3:0] n_iter;
    output[n+n-1:0] x_inv;

    input clk, req, rst;
    output ack;

    wire en1, en2, en3, en4, rst2, sel1, sel2, LA, LB, s, ready, iter_end, mul_rst;

    Controller control(clk, en1, en2, en3, en4, rst2, sel1, sel2, LA, LB, s, ready, iter_end, ack, req, rst, mul_rst);
    Datapath datapath(clk, x_in, n_iter, en1, en2, en3, en4, rst2, sel1, sel2, LA, LB, s, ready, iter_end, x_inv, mul_rst);
endmodule