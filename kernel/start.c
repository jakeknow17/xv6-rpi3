#include "types.h"
#include "param.h"
#include "aarch64.h"
#include "defs.h"

// void main();

// entry.S needs one stack per CPU.
// __attribute__ ((aligned (16))) char stack0[4096 * NCPU];
// char stack0[4096 * NCPU];

void start()
{
    if (!(r_mpidr_el1() & 0x3))
    {
        uart_init();
        uart_puts("Hello World!\n");
        uart_puts("Second time!\n");
    }
    else
    {
        return;
    }
}