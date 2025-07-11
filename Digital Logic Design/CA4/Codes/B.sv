`include "B_Controller_FSM.sv"
`include "B_Datapath.sv"

module DeterminantCalculator_3in3(clk, start_address, data_in, address_to_memory, start, done, rst, final_output);
    input[3:0] start_address;
    input[7:0] data_in;
    output[3:0] address_to_memory;
    output[24:0] final_output;

    input clk, start, rst;
    output done;

    wire reset_all, det_start, det_rst, count_load, count_en, dec_en1, dec_en2, mul_end, load_end, cal_end, det_done;

    B_Datapath datapath(clk, start_address, data_in, address_to_memory, cal_end, det_done, det_start, det_rst, 
                        reset_all, count_load, load_end, mul_end, count_en, dec_en1, dec_en2, final_output);
    B_Controller controller(clk, rst, start, reset_all, count_load, count_en, det_start, det_rst,
                            dec_en1, dec_en2, mul_end, load_end, cal_end, det_done, done);

endmodule