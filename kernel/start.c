#include "types.h"
#include "param.h"
#include "aarch64.h"
#include "defs.h"
#include "mailbox.h"

// void main();

void start()
{
    if (!(r_mpidr_el1() & 0x3)) // Core 0
    {
        uart_init();

        uart_puts("Hello World!\n");

        // echo
        while(1)
            uart_sendc(uart_getc());
    }
    else // Other cores
    {
        return;
    }
}