#ifndef XORGATE_H
#define XORGATE_H

#include <systemc.h>
#include <iostream>

class XorGate: public sc_module
{
	public:
		sc_in <bool> a_in, b_in;
		sc_out <bool> c_out;

	    SC_CTOR(XorGate)
        {
		    SC_METHOD(operation)
		        sensitive << a_in << b_in;
		}

	private:
	inline void operation ()
    { 
        c_out.write(a_in.read() xor b_in.read()); 
    }

};

#endif
