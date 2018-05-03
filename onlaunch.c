#include "onlaunch.h"

uint32_t bootcount(uint8_t function)
{
    //do some uart stuff to improt the actual bootcount from eprom
    uint32_t bootcount_import = 0; // This is a dummy variable.

    if(function == 1) // Add 1 and then return current bootcount
    {
        bootcount++;
        //Write the new bootvalue to eprom:
        return bootcount;
    }
    else if(function == 2) // subtract 1 and then return current bootcount
    {
        bootcount--;    
        //Write the new bootvalue to eprom:
        return bootcount;
    }
    else
    {
        return  bootcount;
    }
}