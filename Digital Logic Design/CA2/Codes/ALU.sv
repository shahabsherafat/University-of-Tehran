module Encoder_16_to_4(inp, out);
	input[15:0] inp;
	output[3:0] out;
   	logic[3:0] out;
	
	always @(inp)
	begin 
        case (inp)
            16'b1000000000000000: out = 4'b1111;
            16'b0100000000000000: out = 4'b1110;
            16'b0010000000000000: out = 4'b1101;
            16'b0001000000000000: out = 4'b1100;
            16'b0000100000000000: out = 4'b1011;
            16'b0000010000000000: out = 4'b1010;
            16'b0000001000000000: out = 4'b1001;
            16'b0000000100000000: out = 4'b1000;
            16'b0000000010000000: out = 4'b0111;
            16'b0000000001000000: out = 4'b0110;
            16'b0000000000100000: out = 4'b0101;
            16'b0000000000010000: out = 4'b0100;
            16'b0000000000001000: out = 4'b0011;
            16'b0000000000000100: out = 4'b0010;
            16'b0000000000000010: out = 4'b0001;
            16'b0000000000000001: out = 4'b0000;
        endcase
	end
endmodule

module Decoder_4_to_16(inp, out);
    input[3:0] inp;
	output[15:0] out;
    logic[15:0] out;

    always @(inp)
	begin
        case (inp)
            4'b1111: out = 16'b1000000000000000;
            4'b1110: out = 16'b0100000000000000;
            4'b1101: out = 16'b0010000000000000;
            4'b1100: out = 16'b0001000000000000;
            4'b1011: out = 16'b0000100000000000;
            4'b1010: out = 16'b0000010000000000;
            4'b1001: out = 16'b0000001000000000;
            4'b1000: out = 16'b0000000100000000;
            4'b0111: out = 16'b0000000010000000;
            4'b0110: out = 16'b0000000001000000;
            4'b0101: out = 16'b0000000000100000;
            4'b0100: out = 16'b0000000000010000;
            4'b0011: out = 16'b0000000000001000;
            4'b0010: out = 16'b0000000000000100;
            4'b0001: out = 16'b0000000000000010;
            4'b0000: out = 16'b0000000000000001;
        endcase
	end
endmodule

module Comparator_4_bit_signed(inp1, inp2, eq, gt, lt);
    input[3:0] inp1, inp2;
    output eq, gt, lt;
    wire[3:0] i;

    genvar k;
    generate
        for(k = 0; k < 4; k = k + 1) begin
            xnor(i[k], inp1[k], inp2[k]);
        end
    endgenerate

    and(eq, i[0], i[1], i[2], i[3]);

    wire[3:0] gt_items;
    and(gt_items[0], ~inp1[3], inp2[3]);
    and(gt_items[1], i[3], inp1[2], ~inp2[2]);
    and(gt_items[2], i[3], i[2], inp1[1], ~inp2[1]);
    and(gt_items[3], i[3], i[2], i[1], inp1[0], ~inp2[0]);
    or(gt, gt_items[0], gt_items[1], gt_items[2], gt_items[3]);

    nor(lt, gt, eq);
endmodule

module CarryLookaheadAdder_4bit_signed(inp1, inp2, cin, out, overflow);
    input[3:0] inp1, inp2;
    input cin;
    output overflow;
    output[3:0] out;

    wire[4:0] c;
    assign c[0] = cin;
    wire[3:0] p, g;

    wire[3:0] inp2_adjusted;
    genvar i;
    generate
        for(i = 0; i < 4; i = i + 1) begin
            xor(inp2_adjusted[i], inp2[i], cin);
        end
    endgenerate

    generate
        for(i = 0; i < 4; i = i + 1) begin
            xor(out[i], inp1[i], inp2_adjusted[i], c[i]);
        end
    endgenerate

    xor(overflow, c[4], c[3]);

    wire c1_and;
    wire[1:0] c2_ands;
    wire[2:0] c3_ands;
    wire[3:0] c4_ands;
    
    and(c1_and, c[0], p[0]);

    and(c2_ands[0], g[0], p[1]);
    and(c2_ands[1], p[1], p[0], c[0]);

    and(c3_ands[0], g[1], p[2]);
    and(c3_ands[1], g[0], p[2], p[1]);
    and(c3_ands[2], p[2], p[1], p[0], c[0]);

    and(c4_ands[0], g[2], p[3]);
    and(c4_ands[1], g[1], p[3], p[2]);
    and(c4_ands[2], g[0], p[3], p[2], p[1]);
    and(c4_ands[3], p[3], p[2], p[1], p[0], c[0]);

    or(c[1], g[0], c1_and);
    or(c[2], g[1], c2_ands[1], c2_ands[0]);
    or(c[3], g[2], c3_ands[2], c3_ands[1], c3_ands[0]);
    or(c[4], g[3], c4_ands[3], c4_ands[2], c4_ands[1], c4_ands[0]);

    generate
        for(i = 0; i < 4; i = i + 1) begin
            or(p[i], inp1[i], inp2_adjusted[i]);
            and(g[i], inp1[i], inp2_adjusted[i]);
        end
    endgenerate
endmodule

module ALU(Opc, inp1, inp2, result, overflow);
    input[2:0] Opc;
    input[3:0] inp1, inp2;
    output[3:0] result;
    output overflow;

    wire cin, eq, gt, lt, temp_overflow;
    wire[3:0] sum;
    logic[3:0] min_by_adder, max_by_adder, min_by_comparator, max_by_comparator;

    assign cin = (~Opc[2] & Opc[1]) | (Opc[2] & ~Opc[1] & ~Opc[0]);
    CarryLookaheadAdder_4bit_signed cla(inp1, inp2, cin, sum, temp_overflow);

    always @(sum) begin
        max_by_adder = sum[3] ? inp2 : inp1;
        min_by_adder = sum[3] ? inp1 : inp2;
    end

    Comparator_4_bit_signed cmp(inp1, inp2, eq, gt, lt);

    always @(lt) begin
        max_by_comparator = lt ? inp2 : inp1;
        min_by_comparator = lt ? inp1 : inp2;
    end

    logic[3:0] result;
    logic overflow;
    always @(Opc or inp1 or inp2) begin
        overflow = ((~Opc[2] & Opc[1]) | (Opc[2] & ~Opc[1] & ~Opc[0]) | (~Opc[2] & ~Opc[1] & Opc[0])) & temp_overflow;

        case(Opc)
            3'b001: result = sum;
            3'b010: result = sum;
            3'b011: result = min_by_adder;
            3'b100: result = max_by_adder;
            3'b101: result = min_by_comparator;
            3'b110: result = max_by_comparator;
            3'b111: result = inp2;
        endcase
    end
endmodule

module sevenSegmentDecoder(input[3:0] inp , output[6:0] sign, output[6:0] magintude);
    logic x, y, z, w;
    always @(inp) begin
        if(inp[3] == 1'b1) begin
            {x, y, z, w} = ~inp + 1'b1;
        end

        else begin
            {x, y, z, w} = inp;
        end
    end

    assign sign = inp[3] ? 6'b1000000 : 6'b0000000;

    wire xbar_zbar, x_z, ybar_zbar, y_z, xbar_y, y_zbar, x_ybar_z, x_zbar, x_ybar;
    wire w_bar, x_bar, y_bar, z_bar;

    not #(1) g1(w_bar, w);
    not #(1) g2(x_bar, x);
    not #(1) g3(y_bar, y);
    not #(1) g4(z_bar, z);

    and #(2) g5(xbar_zbar, x_bar, z_bar);
    and #(2) g6(x_z, x, z);
    and #(2) g7(ybar_zbar, y_bar, z_bar);
    and #(2) g8(y_z, y, z);
    and #(2) g9(xbar_y, x_bar, y);
    and #(2) g10(y_zbar, y, z_bar);
    and #(2) g11(x_ybar_z, x, y_bar, z);
    and #(2) g12(x_zbar, x, z_bar);
    and #(2) g13(x_ybar, x, y_bar);

    or #(3) g14(magintude[0], xbar_zbar, x_z, w);
    or #(3) g15(magintude[1], x_bar, ybar_zbar, y_z);
    or #(3) g16(magintude[2], x, y_bar, z);
    or #(3) g17(magintude[3], xbar_zbar, xbar_y, y_zbar, x_ybar_z, w);
    or #(3) g18(magintude[4], xbar_zbar, y_zbar);
    or #(3) g19(magintude[5], ybar_zbar, x_ybar, x_zbar, w);
    or #(3) g20(magintude[6], w, x_ybar, xbar_y, y_zbar);
endmodule

module Top_Module(Opc, inp1, inp2, out, overflow);
    input[15:0] inp1, inp2;
    input[2:0] Opc;
    output[15:0] out;
    output overflow;

    wire[3:0] inp1_encoded, inp2_encoded;
    Encoder_16_to_4 enc1(inp1, inp1_encoded);
    Encoder_16_to_4 enc2(inp2, inp2_encoded);

    wire[3:0] result;
    ALU main_alu(Opc, inp1_encoded, inp2_encoded, result, overflow);
    Decoder_4_to_16 dec(result, out);

    wire[6:0] sign, magintude;
    sevenSegmentDecoder ssd(result, sign, magintude);

endmodule