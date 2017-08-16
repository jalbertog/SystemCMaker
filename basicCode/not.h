#ifndef NotGATE_H
#define NotGATE_H

#include <systemc.h>
#include <iostream>

class NotGate: public sc_module
{
	public:
		sc_in <bool> a_in;
		sc_out <bool> c_out;

	    SC_CTOR(NotGate)
        {
		    SC_METHOD(operation)
		        sensitive << a_in;
		}

	private:
	inline void operation ()
    { 
        c_out.write(not a_in.read()); 
    }

};

#endif
