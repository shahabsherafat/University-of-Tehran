`include "A.sv"

module Addresser(num, previous, next);
    input[1:0] num, previous;
    output reg[3:0] next;

    always @(*) begin
        case(num)
            2'b00: 
                case(previous)
                    2'b00: next = 4'd4;
                    2'b01: next = 4'd5;
                    2'b10: next = 4'd7;
                    2'b11: next = 4'd8;
                    default: next = 4'd0;
                endcase

            2'b01: 
                case(previous)
                    2'b00: next = 4'd3;
                    2'b01: next = 4'd5;
                    2'b10: next = 4'd6;
                    2'b11: next = 4'd8;
                    default: next = 4'd0;
                endcase

            2'b10: 
                case(previous)
                    2'b00: next = 4'd3;
                    2'b01: next = 4'd4;
                    2'b10: next = 4'd6;
                    2'b11: next = 4'd7;
                    default: next = 4'd0;
                endcase

            default:
                next = 4'd0;
        endcase
    end
endmodule

module B_Datapath(clk, start_address, data_in, address_to_memory, cal_end, det_done, det_start, det_rst, 
                  reset_all, count_load, load_end, mul_end, count_en, dec_en1, dec_en2, final_output);
    input[3:0] start_address;
    input[7:0] data_in;
    output[3:0] address_to_memory;
    output[24:0] final_output;

    //Now controlling variables:
    input clk, reset_all, det_start, det_rst, count_load, count_en, dec_en1, dec_en2;
    output mul_end, load_end, cal_end, det_done;

    wire[3:0] count;
    Counter_4bit counter(clk, count_load, count_en, 4'b0000, count);

    wire[8:0] reg_ens1;
    Decoder_4to9 decoder1(dec_en1, count, reg_ens1);

    wire[7:0] abcdefghi[0:8];
    wire[7:0] a = abcdefghi[0];
    wire[7:0] b = abcdefghi[1];
    wire[7:0] c = abcdefghi[2];
    wire[7:0] d = abcdefghi[3];
    wire[7:0] e = abcdefghi[4];
    wire[7:0] f = abcdefghi[5];
    wire[7:0] g = abcdefghi[6];
    wire[7:0] h = abcdefghi[7];
    wire[7:0] i = abcdefghi[8];

    genvar j;
    generate
        for(j = 0; j < 9; j = j + 1) begin
            Register_8bit register(clk, reset_all, reg_ens1[j], data_in, abcdefghi[j]);
        end
    endgenerate
    and(load_end, count[3], count[0]);

    wire[7:0] det_data_in;
    wire[3:0] p;
    wire[15:0] det_final_output;
    wire[3:0] next;
    Addresser addresser({count[1], count[0]}, {p[1], p[0]}, next);
    Mux_9to1 mux1(next, abcdefghi[0], abcdefghi[1], abcdefghi[2], abcdefghi[3], abcdefghi[4], abcdefghi[5],
                  abcdefghi[6], abcdefghi[7], abcdefghi[8], det_data_in);
    DeterminantCalculator_2in2 main(clk, 4'b0000, det_data_in, p, det_start, det_done, det_rst, det_final_output);
    and(cal_end, count[1], count[0]);

    wire[15:0] demux1_out1, demux1_out2, demux1_out3;
    Demux_1to3_16bit demux1({count[1], count[0]}, det_final_output, demux1_out1, demux1_out2, demux1_out3);
    wire[3:0] reg_ens2;
    Decoder_2to4 decoder2(det_done, {count[1], count[0]}, reg_ens2);
    wire[15:0] dets[0:2];
    Register_16bit reg1(clk, reset_all, reg_ens2[0], demux1_out1, dets[0]);
    Register_16bit reg2(clk, reset_all, reg_ens2[1], demux1_out2, dets[1]);
    Register_16bit reg3(clk, reset_all, reg_ens2[2], demux1_out3, dets[2]);
    wire[15:0] cur_det;
    Mux_3to1_16bit mux2({count[1], count[0]}, dets[0], dets[1], dets[2], cur_det);

    wire[7:0] mutliplicant;
    Mux_3to1_8bit mux3({count[1], count[0]}, abcdefghi[0], abcdefghi[1], abcdefghi[2], mutliplicant);
    wire[23:0] sub_det;
    Multiplier_8in16bit multiplier(mutliplicant, cur_det, sub_det);
    and(mul_end, count[1], count[0]);

    wire[23:0] demux2_out1, demux2_out2, demux2_out3;
    Demux_1to3_24bit demux2({count[1], count[0]}, sub_det, demux2_out1, demux2_out2, demux2_out3);
    wire[3:0] reg_ens3;
    Decoder_2to4 decoder3(dec_en2, {count[1], count[0]}, reg_ens3);
    wire[23:0] sub_dets[0:2];
    wire[23:0] s1 = sub_dets[0];
    wire[23:0] s2 = sub_dets[1];
    wire[23:0] s3 = sub_dets[2];
    Register_24bit reg4(clk, reset_all, reg_ens3[0], demux2_out1, sub_dets[0]);
    Register_24bit reg5(clk, reset_all, reg_ens3[1], demux2_out2, sub_dets[1]);
    Register_24bit reg6(clk, reset_all, reg_ens3[2], demux2_out3, sub_dets[2]);

    wire[23:0] subtracted;
    Subtractor_24bit subtractor(sub_dets[0], sub_dets[1], subtracted);
    Adder_24bit adder(subtracted, sub_dets[2], final_output);

    Adder_4bit adder2(count, start_address, address_to_memory);
endmodule