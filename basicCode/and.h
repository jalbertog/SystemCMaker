#ifndef ANDGATE_H
#define ANDGATE_H

#include <systemc.h>
#include <iostream>

class AndGate: public sc_module
{
	public:
		sc_in <bool> a_in, b_in;
		sc_out <bool> c_out;

	    SC_CTOR(AndGate)
        {
		    SC_METHOD(operation)
		        sensitive << a_in << b_in;
		}

	private:
	inline void operation ()
    { 
        c_out.write(a_in.read() and b_in.read()); 
    }

};

#endif
