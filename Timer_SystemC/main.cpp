// main.cpp
#include "systemc.h"
#include "timer.h"


int sc_main(int argc, char* argv[])


{

   sc_signal<bool> START, TIMEOUT;

   sc_time clkPrd(10, SC_NS);// period
   sc_clock CLOCK("clock", clkPrd);	// timer
   // Binding
   timer tm("timer");
 	 tm.clock(CLOCK);
   tm.start(START);
   tm.timeout(TIMEOUT);

  	// tracing

    sc_trace_file *tf = sc_create_vcd_trace_file("RESULT.vcd");


    sc_trace(tf, tm.clock, "clock");  // clock first
    sc_trace(tf, tm.start, "start");  // start second
    sc_trace(tf, tm.timeout, "timeout"); // timeout third
    sc_trace(tf, tm.count, "count"); // count fourth


    // 3 cycles delay ---> first time
    START.write(1);

    sc_start(3*clkPrd);

    // start counting ---> first time
    START.write(0);

    sc_start(3*clkPrd);

    // reset before count reaches 0; 3 cycles delay  ---> first time
    START.write(1);

    sc_start(3*clkPrd);

    // start counting again until count = 0
    START.write(0);

    sc_start(5*clkPrd);

    // reset after count = 0; 3 cycles delay
    START.write(1);

    sc_start(3*clkPrd);

    // start counting ---> second time
    START.write(0);

    sc_start(3*clkPrd);

    // reset before count reaches 0 ---> second time
    START.write(1);

    sc_start(1*clkPrd);

    // start counting again until count = 0 ---> second time
    START.write(0);

    sc_start(6*clkPrd);

    // reset after count = 0; 3 cycles delay  ---> second time
    START.write(1);

    sc_start(3*clkPrd);

  	sc_close_vcd_trace_file(tf);

  return(0);
  }
