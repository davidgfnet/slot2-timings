
`timescale 1ns / 1ps

// Rounding clock timings to 60ns (it's actually 59.6ns)

module tb();

reg phi = 0;
reg ncs = 1;
reg nrd = 1;
reg nwr = 1;
reg [15:0] data = 16'bz;

always #30 phi = !phi;

initial begin
    $dumpfile("2_1.vcd");

    $dumpvars(0, phi);
    $dumpvars(0, ncs);
    $dumpvars(0, nrd);
    $dumpvars(0, nwr);
    $dumpvars(0, data);

    # 50;
    data = 16'hADD8;
    # 10;
    ncs = 0;
    # 60;
    data = 16'bz;
    nrd = 0;
    # 30
    data = 16'hDA7A;
    # 30;
    nrd = 1;
    # 10;
    data = 16'bz;
    # 50;
    nrd = 0;
    # 30;
    data = 16'hDA7A;
    # 30;
    ncs = 1;
    nrd = 1;
    # 10;
    data = 16'bz;

    # 200;
    $finish;

end

endmodule
