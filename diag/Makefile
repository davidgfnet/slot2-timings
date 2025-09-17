
all:
	iverilog -o 4_2.bin 4_2.v
	vvp 4_2.bin -lx2

	iverilog -o 2_1.bin 2_1.v
	vvp 2_1.bin -lx2

clean:
	rm -f *.bin *.vcd

