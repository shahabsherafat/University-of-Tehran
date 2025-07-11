module Controller(clk, en1, en2, en3, en4, rst2, sel1, sel2, LA, LB, s, ready, iter_end, ack, req, rst, mul_rst);
    output en1, en2, en3, en4, rst2, sel1, sel2, LA, LB, s, ack, mul_rst;
    input clk, iter_end, ready, req, rst;

    reg en1, en2, en3, en4, rst2, sel1, sel2, LA, LB, s, ack, mul_rst;
    reg[2:0] y, Y;
    parameter IDLE = 0, LOAD = 1, MUL1 = 2, SAVE_MUL1 = 3, SUB = 4, MUL2 = 5, SAVE_Y = 6, REPORT = 7;

    always @(posedge rst, posedge clk) begin
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
                if(req) begin
                    en1 = 1;
                    en3 = 0;
                    mul_rst = 1;
                    rst2 = 0;
                    Y <= LOAD;
                end

                else begin
                    en1 = 0;
                    en2 = 0;
                    rst2 = 1;
                    sel1 = 0;
                    en3 = 1;
                    sel2 = 0;
                    en4 = 0;
                    ack = 0;
                    LA = 0;
                    LB = 0;
                    s = 0;
                    LA <= 1;
                    LB = 1;
                    mul_rst = 0;
                    Y <= IDLE;
                end
            end

            LOAD: begin
                sel1 = 1;
                LA <= 0;
                LB = 1;
                Y <= MUL1;
            end

            MUL1:
                if(!ready) begin
                    s = 1;
                    LA = 0;
                    LB = 0;
                    en2 = 0;
                    Y <= MUL1;
                end

                else begin
                    en4 = 1;
                    en2 = 0;
                    Y <= SAVE_MUL1;
                end

            SAVE_MUL1: begin
                en4 = 0;
                s = 0;
                Y <= SUB;
            end

            SUB: begin
                sel2 = 1;
                LA = 1; 
                LB = 1;
                Y <= MUL2;
            end

            MUL2:
                if(!ready) begin
                    s = 1;
                    LA = 0;
                    LB = 0;
                    Y <= MUL2;
                end

                else begin
                    en3 = 1;
                    Y <= SAVE_Y;
                end

            SAVE_Y: begin
                if(!iter_end) begin
                    en3 = 0;
                    sel2 = 0;
                    en2 = 1;
                    s = 0;
                    LA = 1;
                    LB = 1;
                    Y <= MUL1;
                end

                else begin
                    ack = 1;
                    Y <= REPORT;
                end
            end

            REPORT: begin
                if(req)
                    ack = 1;
                else
                    ack = 0;
            end
        endcase
    end
endmodule