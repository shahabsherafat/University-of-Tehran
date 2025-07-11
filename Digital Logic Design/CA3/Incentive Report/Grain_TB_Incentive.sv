`timescale 1ns/1ns

module Grain_TB_Incentive();
    logic clk, load;
    logic [103:0] seed;
    wire current_ser_out;

    integer num_of_0 = 0;
    integer num_of_1 = 0;
    integer num_of_00 = 0;
    integer num_of_01 = 0;
    integer num_of_10 = 0;
    integer num_of_11 = 0;
    integer flag = 0;
    integer i = 1;
    integer file;

    logic previous_ser_out = 0;

    initial begin
        clk = 0;
    end

    initial begin
        repeat(2000) begin
            #20
            clk = ~clk;
        end

        $fdisplay(file, "\nFinal Report:\n");
        $fdisplay(file, "Num of 0s: %0d\n", num_of_0);
        $fdisplay(file, "Num of 1s: %0d\n", num_of_1);
        $fdisplay(file, "Num of 00s: %0d\n", num_of_00);
        $fdisplay(file, "Num of 01s: %0d\n", num_of_01);
        $fdisplay(file, "Num of 10s: %0d\n", num_of_10);
        $fdisplay(file, "Num of 11s: %0d\n", num_of_11);
        $fclose(file);
    end

    Grain grain(0, 1, load, clk, seed, current_ser_out);

    initial begin
        load = 1;
        seed = 104'h44ABA694D473A40BD028EC0E2A;
        file = $fopen("incentive_report.txt", "w");

        #25
        load = 0;
    end

    initial begin
        @(posedge clk);

        case(current_ser_out)
            0: num_of_0 = num_of_0 + 1;
            1: num_of_1 = num_of_1 + 1;
        endcase
        previous_ser_out = current_ser_out;

        flag = 1;
        $fdisplay(file, "Repetition %0d: random generated number = %b\n", i, current_ser_out);
        i = i + 1;
    end

    always @(posedge clk) begin
        if(flag) begin
            $fdisplay(file, "Repetition %0d: random generated number = %b\n", i, current_ser_out);

            case(current_ser_out)
                0: num_of_0 = num_of_0 + 1;
                1: num_of_1 = num_of_1 + 1;
            endcase

            case({previous_ser_out, current_ser_out})
                2'b00: num_of_00 = num_of_00 + 1;
                2'b01: num_of_01 = num_of_01 + 1;
                2'b10: num_of_10 = num_of_10 + 1;
                2'b11: num_of_11 = num_of_11 + 1;
            endcase

            previous_ser_out = current_ser_out;
            i = i + 1;
        end
    end


endmodule