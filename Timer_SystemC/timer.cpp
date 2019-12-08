// timer.cpp
#include "timer.h"
#include "systemc.h"
void timer::runtimer()
{
	while(1)
  {
		if (start.read())
    {
		    cout << "Timer: timer start detected "<< endl;
		    count = 5;
		    timeout.write(0);
		}
    else
    {
		    if (count == 0) timeout.write(1);
        else
          {
		        count--;
		        timeout.write(0);
		      }
		}
		wait();
	}
}
