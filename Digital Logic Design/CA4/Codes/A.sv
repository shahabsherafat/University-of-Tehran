`include "A_Controller_FSM.sv"
`include "A_Datapath.sv"

module DeterminantCalculator_2in2(clk, start_address, data_in, address_to_memory, start, done, rst, final_output);
    input[3:0] start_address;
    input[7:0] data_in;
    output[3:0] address_to_memory;
    output[15:0] final_output;

    input clk, start, rst;
    output done;

    wire mul_select, dec_en, en_1, en_2, mul_end, load_end, reset_all;

    A_Datapath datapath(clk, start_address, data_in, address_to_memory,
                        reset_all, dec_en, mul_select, mul_end, load_end, en_1, en_2, final_output);
    A_Controller controller(clk, rst, start, reset_all, dec_en, mul_select, mul_end, load_end, en_1, en_2, done);

endmodule