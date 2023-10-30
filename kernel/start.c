#include "types.h"
#include "param.h"
#include "aarch64.h"
#include "defs.h"
#include "mailbox.h"
#include "sd.h"

extern uint64 end;

// void main();

void start()
{
    if (!(r_mpidr_el1() & 0x3)) // Core 0
    {
        uart_init();

        uart_puts("Hello World!\n");

        uart_puts("Waiting 1000000 CPU cycles (ARM CPU): ");
        delay_cycles(1000000);
        uart_puts("OK\n");

        uart_puts("Waiting 1000000 microsec (ARM CPU): ");
        delay_msec(1000000);
        uart_puts("OK\n");

        uart_puts("Waiting 1000000 microsec (BCM System Timer): ");

        if(get_system_timer()==0) {
            uart_puts("Not available\n");
        } else {
            delay_msec_st(1000000);
            uart_puts("OK\n");
        }

        // initialize EMMC and detect SD card type
        if(sd_init()==SD_OK) {
        // read the master boot record after our bss segment
            if(sd_readblock(0,(void *)(&end),1)) {
                // dump it to serial console
                uart_dump(&end);
        }

        uart_puts("Finished dumping first sector of SD card.\n");

    }

        // echo
        while(1)
            uart_sendc(uart_getc());
    }
    else // Other cores
    {
        return;
    }
}