#include "Vtb.h"
#include "verilated.h"
//#include "verilated_vcd_c.h"
#include "verilated_fst_c.h"




vluint64_t main_time = 0;       // Current simulation time
        // This is a 64-bit integer to reduce wrap over issues and
        // allow modulus.  You can also use a double, if you wish.

double sc_time_stamp () {       // Called by $time in Verilog
    return main_time;           // converts to double, to match
                                // what SystemC does
}

int main(int argc, char** argv, char** env) {
    Verilated::commandArgs(argc, argv);
    Vtb* top = new Vtb;
    
        Verilated::traceEverOn(true);
        //VerilatedVcdC* tfp = new VerilatedVcdC;
        VerilatedFstC* tfp = new VerilatedFstC;
        top->trace (tfp, 99);
        //tfp->open ("obj_dir/simx.vcd");
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
        tfp->dump (main_time);
    }
    tfp->close();
    delete top;
    exit(0);
}

