#ifndef ORGATE_H
#define ORGATE_H

#include <systemc.h>
#include <iostream>

class OrGate: public sc_module
{
	public:
		sc_in <bool> a_in, b_in;
		sc_out <bool> c_out;

	    SC_CTOR(OrGate)
        {
		    SC_METHOD(operation)
		        sensitive << a_in << b_in;
		}

	private:
	inline void operation ()
    { 
        c_out.write(a_in.read() or b_in.read()); 
    }

};

#endif
