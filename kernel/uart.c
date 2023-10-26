#include "memlayout.h"
#include "types.h"
#include "mailbox.h"

void uart_init()
{
    register unsigned int r;

    *PL011_CR = 0;              // turn off UART0

    // Set up clock for consistent divisor values
    set_device_clock_rate(MBOX_CLK_ID_UART, 4000000, 1);

    // Map UART0 to GPIO pins
    r = *GPFSEL1;               // GPFSEL1 controls function select for GPIO 10-19
    r &= ~((7<<12)|(7<<15));    // Clear GPIO14 (bits 14-12) and GPIO15 (bits 17-15)
    r |= (4<<12)|(4<<15);       // Set GPIO14 and GPIO15 to ALT0 (bit pattern 100)
    *GPFSEL1 = r;
    *GPPUD = 0;            // enable pins 14 and 15
    r=150; while(r--) { asm volatile("nop"); }
    *GPPUDCLK0 = (1<<14)|(1<<15);
    r=150; while(r--) { asm volatile("nop"); }
    *GPPUDCLK0 = 0;        // flush GPIO setup

    *PL011_ICR = 0x7FF;    // clear interrupts
    *PL011_IBRD = 2;       // 115200 baud
    *PL011_FBRD = 0xB;
    *PL011_LCRH = 0x7<<4;  // 8n1, enable FIFOs
    *PL011_CR = 0x301;     // enable Tx, Rx, UART
}

/**
 * Send a character
 */
void uart_send(unsigned int c) {
    /* wait until we can send */
    do{asm volatile("nop");}while(*PL011_FR&0x20);
    /* write the character to the buffer */
    *PL011_DR=c;
}

/**
 * Receive a character
 */
char uart_getc() {
    char r;
    /* wait until something is in the buffer */
    do{asm volatile("nop");}while(*PL011_FR&0x10);
    /* read it and return */
    r=(char)(*PL011_DR);
    /* convert carrige return to newline */
    return r=='\r'?'\n':r;
}

/**
 * Display a string
 */
void uart_puts(char *s) {
    while(*s) {
        /* convert newline to carrige return + newline */
        if(*s=='\n')
            uart_send('\r');
        uart_send(*s++);
    }
}

/**
 * Display a binary value in hexadecimal
 */
void uart_hex(unsigned int d, int c) {
    unsigned int n;
    for(;c>=0;c-=4) {
        // get highest tetrad
        n=(d>>c)&0xF;
        // 0-9 => '0'-'9', 10-15 => 'A'-'F'
        n+=n>9?0x37:0x30;
        uart_send(n);
    }
}

/**
 * Display a 32-bit binary value in hexadecimal
 */
void uart_hex_u32(unsigned int d) {
    uart_hex((unsigned)d, 28); // 32 - 4
}

/**
 * Display a 64-bit binary value in hexadecimal
 */
void uart_hex_u64(unsigned long d) {
    uart_hex(d, 60); // 64 - 4
}
