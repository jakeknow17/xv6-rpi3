#include "types.h"
#include "param.h"

// void main();

// entry.S needs one stack per CPU.
__attribute__ ((aligned (16))) char stack0[4096 * NCPU];
// char stack0[4096 * NCPU];

void start()
{
    while(1)
    {
        // do nothing
    }
}