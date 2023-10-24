#include "types.h"
#include "param.h"
#include "aarch64.h"
#include "defs.h"

// void main();

// entry.S needs one stack per CPU.
__attribute__ ((aligned (16))) char stack0[4096 * NCPU];
// char stack0[4096 * NCPU];

void start()
{
    uart_init();
    uart_puts("Hello World!\n");
    uart_puts("Second time!\n");
    char txt[3];
    txt[0] = (char)r_mpidr_el1();
    txt[1] = '\n';
    txt[2] = 0;
    uart_puts(txt);
    if (txt[0] == 0)
        uart_puts("Zero!\n");
    else
        uart_puts("Else!\n");
    // if (r_mpidr_el1() == 0)
    // {
    //     uart_init();
    //     uart_puts("Hello World!\n");
    // }
    // else
    // {
    //     while(1);
    // }
}