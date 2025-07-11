`timescale 1ns/1ns
module ROM(addrBus, outBus);
    //parameter
    parameter  BW=8 ;
    parameter  N=16 ;
    //input
    input [$clog2(N) - 1 :0]addrBus;
    //output   
    output [BW - 1 :0] outBus;
    //memory declarations
    reg [BW - 1 :0] ROMData[0 : N - 1 ];
    reg [BW - 1 :0] outReg;

    integer i;
    initial begin
    for(i = 0; i < N; i = i+1)
        ROMData[i] = 8'b0; 
        $readmemb( "ROM_data.txt" ,ROMData,0 , (N-1) );   
    end

    assign outBus = ROMData[addrBus];
endmodule

