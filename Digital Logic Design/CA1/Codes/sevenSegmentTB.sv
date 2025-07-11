`timescale 1ns/1ns
module sevenSegment_TB();
	logic w_input, x_input, y_input, z_input;
	wire[6:0] test_output;
	wire a, b, c, d, e, f, g;
	assign a = test_output[0]; 
	assign b = test_output[1]; 
	assign c = test_output[2]; 
	assign d = test_output[3]; 
	assign e = test_output[4]; 
	assign f = test_output[5]; 
	assign g = test_output[6]; 
	sevenSegmentDecoderBehavioral SSTB(w_input, x_input, y_input, z_input, test_output);
	
	initial begin
		w_input = 1'b0;
		x_input = 1'b0;
		y_input = 1'b0;
		z_input = 1'b0;

		#15
		z_input = 1;

		#15
		z_input = 0;
		y_input = 1;

		#15
		z_input = 1;
		
		#15
		x_input = 1;
		y_input = 0;
		z_input = 0;

		#15
		z_input = 1;

		#15
		z_input = 0;
		y_input = 1;

		#15
		z_input = 1;

		#15
		x_input = 0;
		y_input = 0;
		z_input = 0;
		w_input = 1;

		#15
		z_input = 1;

		#15
		z_input = 0;
		y_input = 1;
	end

endmodule







