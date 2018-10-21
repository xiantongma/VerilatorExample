# verilator verilog/systemverilog simulator example 

waveform



## direction struction

├── doc //document

├── dut //dut source code

├── sim //testbench source code

└── work //run simulation direction

## addtion options

### fst waveformat

flags += --trace-fst

### sim_main.cpp

```cpp
#include "verilated_fst_c.h"
```

```cpp
int main(int argc, char** argv, char** env) {
    Verilated::commandArgs(argc, argv);
    Vtb* top = new Vtb;

	// dump fst waveform, initial
    Verilated::traceEverOn(true);
	VerilatedFstC* tfp = new VerilatedFstC;
    top->trace (tfp, 99);
    tfp->open ("simx.fst");

	top->rstb = 0;           // Set some inputs

    while (!Verilated::gotFinish()) {
        if (main_time > 10) {
            top->rstb = 1;   // Deassert reset
        }
        if ((main_time % 10) == 1) {
            top->clk = 1;       // Toggle clock
        }
        if ((main_time % 10) == 6) {
            top->clk = 0;
        }
        top->eval();            // Evaluate model
        //cout << top->out << endl;       // Read a output
        main_time++;            // Time passes...

		// dump fst waveform, dump waveform in current time
        tfp->dump (main_time);
    }
	// dump fst waveform, close waveform file
    tfp->close();

    delete top;
    exit(0);
}

#### makefile



## reference

	verilator simulation document
	https://www.veripool.org/projects/verilator/wiki/Intro
