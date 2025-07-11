`timescale 1ns/1ns
module sevenSegmentDecoder(input w, x, y, z ,output[6:0] out);
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

    or #(3) g14(out[0], xbar_zbar, x_z, w);
    or #(3) g15(out[1], x_bar, ybar_zbar, y_z);
    or #(3) g16(out[2], x, y_bar, z);
    or #(3) g17(out[3], xbar_zbar, xbar_y, y_zbar, x_ybar_z, w);
    or #(3) g18(out[4], xbar_zbar, y_zbar);
    or #(3) g19(out[5], ybar_zbar, x_ybar, x_zbar, w);
    or #(3) g20(out[6], w, x_ybar, xbar_y, y_zbar);
     
endmodule