`include "Utilities.sv"

module A_Datapath(clk, start_address, data_in, address_to_memory,
                  reset_all, dec_en, mul_select, mul_end, load_end, en_1, en_2, final_output);
    input[3:0] start_address;
    input[7:0] data_in;
    output[3:0] address_to_memory;
    output[15:0] final_output;

    //Now controlling variables:
    input clk, reset_all, mul_select, dec_en, en_1, en_2;
    output mul_end, load_end;

    wire reset_all_bar;
    not(reset_all_bar, reset_all);

    wire[2:0] count;
    Counter_3bit counter(clk, reset_all, reset_all_bar, 3'b000, count);

    wire[3:0] reg_ens;
    Decoder_2to4 decoder(dec_en, {count[1], count[0]}, reg_ens);

    wire[7:0] abcd[0:3];
    wire[7:0] a = abcd[0];
    wire[7:0] b = abcd[1];
    wire[7:0] c = abcd[2];
    wire[7:0] d = abcd[3];
    genvar i;
    generate
        for(i = 0; i < 4; i = i + 1) begin
            Register_8bit register(clk, reset_all, reg_ens[i], data_in, abcd[i]);
        end
    endgenerate
    assign load_end = count[2];

    wire[7:0] in1, in2;
    Mux_2to1 mux1(mul_select, abcd[0], abcd[1], in1);
    Mux_2to1 mux2(mul_select, abcd[3], abcd[2], in2);

    wire[15:0] ad_or_bc;
    Multiplier_8bit multiplier(in1, in2, ad_or_bc);
    and(mul_end, count[2], count[1]);

    wire[15:0] demux_out1, demux_out2;
    Demux_1to2 dumux(mul_select, ad_or_bc, demux_out1, demux_out2);

    wire[15:0] ad, bc;
    Register_16bit reg1(clk, reset_all, en_1, demux_out1, ad); 
    Register_16bit reg2(clk, reset_all, en_2, demux_out2, bc);

    Subtractor_16bit subtractor(ad, bc, final_output);

    Adder_4bit adder({1'b0, 1'b0, count[1], count[0]}, start_address, address_to_memory);
endmodule