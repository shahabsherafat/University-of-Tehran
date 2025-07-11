module B_Controller(clk, rst, start, reset_all, count_load, count_en, det_start, det_rst,
                    dec_en1, dec_en2, mul_end, load_end, cal_end, det_done, done);

    input clk, rst, start, mul_end, load_end, cal_end, det_done;
    output reg reset_all, count_load, count_en, det_start, det_rst, dec_en1, dec_en2, done;

    reg[2:0] y, Y;
    parameter IDLE = 0, LOAD = 1, DET_CAL_2IN2 = 2, SAVING_DETS = 3, MULTIPLICATION = 4, SAVING_MULS = 5, FINAL_CALS = 6;

    always @(negedge rst, posedge clk) begin
        if(rst) begin
            y <= IDLE;
        end

        else begin
            y <= Y;
        end
    end

    always @(*) begin
        case(y)
            IDLE: begin
                if(start && !rst) begin
                    reset_all = 0; 
                    dec_en1 = 1;
                    count_load = 1;
                    count_en = 1;
                    Y <= LOAD;
                end

                else begin
                    reset_all = 1;
                    count_load = 1;
                    count_en = 0;
                    dec_en1 = 0;
                    dec_en2 = 0;
                    det_start = 0;
                    det_rst = 1;
                    done = 0;
                    Y <= IDLE;
                end
            end

            LOAD:
                if(load_end == 0) begin
                    count_load = 0;
                    Y <= LOAD;
                end
                else begin
                    count_load = 1;
                    count_en = 0;
                    dec_en1 = 0;
                    det_start = 1;
                    det_rst = 0;
                    Y <= DET_CAL_2IN2;
                end

            DET_CAL_2IN2:
                if(det_done == 0) begin
                    count_load = 0;
                    det_rst = 0;
                    Y <= DET_CAL_2IN2;
                end

                else begin
                    count_en = 1;
                    Y <= SAVING_DETS;
                end

            SAVING_DETS:
                if(!cal_end) begin
                    det_rst = 1;
                    count_en = 0;
                    Y <= DET_CAL_2IN2;
                end
                else begin
                    dec_en2 = 1;
                    count_en = 0;
                    count_load = 1;
                    det_start = 0;
                    Y <= MULTIPLICATION;
                end

            MULTIPLICATION: begin
                count_en = 1;
                count_load = 0;
                Y <= SAVING_MULS;
            end

            SAVING_MULS:
                if(mul_end == 0) begin
                    count_en = 0;
                    Y <= MULTIPLICATION;
                end

                else begin
                    $display("alalal, time = %d, muk end == %d", $time, mul_end);
                    dec_en2 = 0;
                    Y <= FINAL_CALS;
                end

            FINAL_CALS: begin
                done = 1;
                Y <= IDLE;
            end
        endcase
    end
endmodule