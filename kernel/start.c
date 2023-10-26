#include "types.h"
#include "param.h"
#include "aarch64.h"
#include "defs.h"
#include "mailbox.h"

// void main();

void start()
{
    if (!(r_mpidr_el1() & 0x3))
    {
        uart_init();

        uart_puts("Hello World!\n");
        uart_puts("Second time!\n");
        uart_hex_u64(get_board_serial());
        // echo
        while(1)
            uart_send(uart_getc());
    }
    else
    {
        return;
    }
}