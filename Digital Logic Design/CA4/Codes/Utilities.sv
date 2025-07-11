module Register_8bit (clk, rst, en, d, q);
    input clk, rst, en;
    input[7:0] d;
    output reg[7:0] q;

    always @(posedge clk or posedge rst) begin
        if(rst) begin
            q <= 8'b0;
        end 
        else if(en) begin
            q <= d;
        end
    end
endmodule

module Register_16bit(clk, rst, en, d, q);
    input clk, rst, en;
    input[15:0] d;
    output reg[15:0] q;

    always @(posedge clk or posedge rst) begin
        if(rst) begin
            q <= 16'b0;
        end 
        else if(en) begin
            q <= d;
        end
    end
endmodule

module Register_24bit(clk, rst, en, d, q);
    input clk, rst, en;
    input[23:0] d;
    output reg[23:0] q;

    always @(posedge clk or posedge rst) begin
        if(rst) begin
            q <= 24'b0;
        end 
        else if(en) begin
            q <= d;
        end
    end
endmodule

module Counter_3bit(clk, load, en, load_in, count);
    input clk, load, en;
    input[2:0] load_in;
    output reg [2:0] count;

    always @(posedge clk) begin
        if(load) begin
            count <= load_in;
        end

        else if(en) begin
            count <= count + 1;
        end
    end
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

module Decoder_2to4(en, in, out);
    input en;
    input[1:0] in;
    output reg[3:0] out;

    always @(*) begin
        if(en) begin
            case (in)
                2'b00: out = 4'b0001;
                2'b01: out = 4'b0010;
                2'b10: out = 4'b0100;
                2'b11: out = 4'b1000;
                default: out = 4'b0000;
            endcase
        end 

        else begin
            out = 4'b0000;
        end
    end
endmodule

module Decoder_4to9(en, in, out);
    input en;
    input[3:0] in;
    output reg[8:0] out;

    always @(*) begin
        if(en) begin
            case (in)
                4'b0000: out = 9'b000000001;
                4'b0001: out = 9'b000000010;
                4'b0010: out = 9'b000000100;
                4'b0011: out = 9'b000001000;
                4'b0100: out = 9'b000010000;
                4'b0101: out = 9'b000100000;
                4'b0110: out = 9'b001000000;
                4'b0111: out = 9'b010000000;
                4'b1000: out = 9'b100000000;
                default: out = 9'b000000000;
            endcase
        end

        else begin
            out = 9'b000000000;
        end
    end
endmodule

module Mux_2to1(select, in1, in2, out);
    input select;
    input[7:0] in1, in2;
    output[7:0] out;
    assign out = select ? in2 : in1;
endmodule

module Mux_3to1_8bit(select, in1, in2, in3, out);
    input [1:0] select;
    input [7:0] in1, in2, in3;
    output reg [7:0] out;

    always @(*) begin
        case(select)
            2'b00: out = in1;
            2'b01: out = in2;
            2'b10: out = in3;
            default: out = 8'b00000000;
        endcase
    end
endmodule

module Mux_3to1_16bit(select, in1, in2, in3, out);
    input [1:0] select;
    input [15:0] in1, in2, in3;
    output reg [15:0] out;

    always @(*) begin
        case(select)
            2'b00: out = in1;
            2'b01: out = in2;
            2'b10: out = in3;
            default: out = 16'b0000000000000000;
        endcase
    end
endmodule

module Mux_9to1(select, in1, in2, in3, in4, in5, in6, in7, in8, in9, out);
    input[3:0] select;
    input[7:0] in1, in2, in3, in4, in5, in6, in7, in8, in9;
    output reg[7:0] out;

    always @(*) begin
        case(select)
            4'b0000: out = in1;
            4'b0001: out = in2;
            4'b0010: out = in3;
            4'b0011: out = in4;
            4'b0100: out = in5;
            4'b0101: out = in6;
            4'b0110: out = in7;
            4'b0111: out = in8;
            4'b1000: out = in9;
            default: out = 8'b00000000;
        endcase
    end
endmodule


module Demux_1to2(select, in, out1, out2);
    input select;
    input[15:0] in;
    output reg[15:0] out1, out2;

    always @(*) begin
        if(select) begin
            out1 = 16'd0;
            out2 = in;
        end 
        
        else begin
            out1 = in;
            out2 = 16'd0;
        end
    end
endmodule

module Demux_1to3_16bit(select, in, out1, out2, out3);
    input[1:0] select;
    input[15:0] in;
    output reg[15:0] out1, out2, out3;

    always @(*) begin
        case(select)
            2'b00: begin
                out1 = in;
                out2 = 16'd0;
                out3 = 16'd0;
            end

            2'b01: begin
                out1 = 16'd0;
                out2 = in;
                out3 = 16'd0;
            end

            2'b10: begin
                out1 = 16'd0;
                out2 = 16'd0;
                out3 = in;
            end
        endcase
    end
endmodule

module Demux_1to3_24bit(select, in, out1, out2, out3);
    input[1:0] select;
    input[23:0] in;
    output reg[23:0] out1, out2, out3;

    always @(*) begin
        case(select)
            2'b00: begin
                out1 = in;
                out2 = 24'd0;
                out3 = 24'd0;
            end

            2'b01: begin
                out1 = 24'd0;
                out2 = in;
                out3 = 24'd0;
            end

            2'b10: begin
                out1 = 24'd0;
                out2 = 24'd0;
                out3 = in;
            end
        endcase
    end
endmodule

module Multiplier_8bit(a, b, out);
    input signed[7:0] a, b;
    output signed[15:0] out;

    assign out = a * b;
endmodule

module Multiplier_8in16bit(a, b, out);
    input signed[7:0] a;
    input signed[15:0] b;
    output signed[23:0] out;

    assign out = a * b;
endmodule

module Subtractor_16bit(a, b, out);
    input[15:0] a, b;
    output[15:0] out;

    assign out = a - b;
endmodule

module Subtractor_24bit(a, b, out);
    input signed[23:0] a, b;
    output signed[23:0] out;

    assign out = a - b;
endmodule

module Adder_4bit(a, b, out);
    input[3:0] a, b;
    output[4:0] out;

    assign out = a + b;
endmodule

module Adder_24bit(a, b, out);
    input signed[23:0] a, b;
    output signed[24:0] out;

    assign out = a + b;
endmodule