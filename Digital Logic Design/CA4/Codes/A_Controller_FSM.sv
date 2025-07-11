module A_Controller(clk, rst, start, reset_all, dec_en, mul_select, mul_end, load_end, en_1, en_2, done);
    input clk, rst, start, mul_end, load_end;
    output reset_all, mul_select, dec_en, en_1, en_2, done;

    reg mul_select, dec_en, en_1, en_2, reset_all, done;
    reg[1:0] y, Y;
    parameter IDLE = 0, LOAD = 1, MULTIPLICATION = 2, SUBTRACTION = 3;

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
                    dec_en = 1;
                    Y <= LOAD;
                end

                else begin
                    reset_all = 1;
                    dec_en = 0;
                    en_1 = 0;
                    en_2 = 0;
                    done = 0;
                    Y <= IDLE;
                end
            end

            LOAD:
                if(!load_end) 
                    Y <= LOAD;
                
                else begin
                    mul_select = 0;
                    dec_en = 0;
                    en_1 = 1;
                    en_2 = 0;
                    Y <= MULTIPLICATION;
                end

            MULTIPLICATION:
                if(!mul_end) begin
                    mul_select = 1;
                    en_1 = 0;
                    en_2 = 1;
                    Y <= MULTIPLICATION;
                end
                else begin
                    en_2 = 0;
                    Y <= SUBTRACTION;
                end

            SUBTRACTION: begin
                Y <= IDLE;
                done = 1;
            end
        endcase
    end
endmodule