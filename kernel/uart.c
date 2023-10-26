#include "memlayout.h"
#include "types.h"
#include "mailbox.h"

void uart_init()
{
    register unsigned int r;

    /* initialize UART */
    *PL011_CR = 0;         // turn off UART0

    /* set up clock for consistent divisor values */
    __attribute__ ((aligned (16))) uint32 mbox[9];
    mbox[0] = 9*4;
    mbox[1] = MBOX_REQUEST;
    mbox[2] = MBOX_CLK_SET_CLK_RATE; // set clock rate
    mbox[3] = 12;
    mbox[4] = 8;
    mbox[5] = 2;           // UART clock
    mbox[6] = 4000000;     // 4Mhz
    mbox[7] = 0;           // clear turbo
    mbox[8] = MBOX_TAG_LAST;
    write_mailbox(MBOX_CH_PROP, mbox);

    /* map UART0 to GPIO pins */
    r=*GPFSEL1;
    r&=~((7<<12)|(7<<15)); // gpio14, gpio15
    r|=(4<<12)|(4<<15);    // alt0
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
