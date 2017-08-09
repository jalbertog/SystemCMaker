#ifndef SUM1BIT_H
#define SUM1BIT_H

#include<systemc.h>
#include<and.h>
#include<or.h>


class sum1bit : public sc_module
{
    public:
        sc_in<bool> a_in;
        sc_in<bool> b_in;


        sc_out<bool> c_out;


        SC_CTOR(sum1bit)
        {
            and_1 = new And(a_in);

            

            // for future
            
        }


        ~sum1bit()
        {
            
        }
    private:

        And *and1;

        // for future
        


};

#endif
