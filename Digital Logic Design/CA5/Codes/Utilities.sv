module shiftrne (R, L, E, w, Clock, Q);
    parameter n = 8;
    input[n-1:0] R;
    input L, E, w, Clock;
    output[n-1:0] Q;
    reg[n-1:0] Q;
    integer k;

    always @(posedge Clock)
    if (L)
        Q <= R;

    else if (E)
    begin
        for (k = n-1; k > 0; k = k-1)
            Q[k-1] <= Q[k];
        Q[n-1] <= w;
    end
endmodule

module shiftlne (R, L, E, w, Clock, Q);
    parameter n = 8;
    input[n-1:0] R;
    input L, E, w, Clock;
    output[n-1:0] Q;
    reg[n-1:0] Q;
    integer k;

    always @(posedge Clock)
    if (L)
        Q <= R;

    else if (E)
    begin
        Q[0] <= w;

        for (k = 1; k < n; k = k+1)
            Q[k] <= Q[k-1];
    end
endmodule

module regne (D, Clock, Resetn, E, Q);
    parameter n = 4;
    input [n-1:0] D;
    input Clock, Resetn, E;
    output [n-1:0] Q;
    reg [n-1:0] Q;

    always @(posedge Clock or negedge Resetn)
        if (Resetn == 0)
            Q <= 0;
        else if (E)
            Q <= D;
endmodule

module Counter_4bit(clk, load, en, load_in, count);
    input clk, load, en;
    input[3:0] load_in;
    output reg [3:0] count;

    always @(posedge clk) begin
        if (load) begin
            count <= load_in;
        end

        else if (en) begin
            count <= count + 1;
        end
    end
endmodule

module Subtractor(a, b, out);
    parameter n = 16;
    input[n-1:0] a, b;
    output[n-1:0] out;

    assign out = a - b;
endmodule