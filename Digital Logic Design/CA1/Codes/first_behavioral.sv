`timescale 1ns/1ns
module sevenSegmentDecoderBehavioral(input w, x, y, z ,output[6:0] out);
    assign out[0] = (~x & ~z) | (x & z) | w;
    assign out[1] = (~x) | (~x & ~z) | (y & z);
    assign out[2] = z | ~y | x;
    assign out[3] = (~x & ~z) | (~x & y) | (y & ~z) | (x & ~y & z) | w;
    assign out[4] = (~x & ~z) | (y & ~z);
    assign out[5] = (~y & ~z) | (x & ~y) | (x & ~z) | w;
    assign out[6] = w | (x & ~y) | (~x & y) | (y & ~z);
    
endmodule