#include "memlayout.h"
#include "types.h"
#include "mailbox.h"
#include "defs.h"

// Initialize UART0s
void uart_init()
{
    register unsigned int r;

    *PL011_CR = 0;              // turn off UART0

    // Set up clock for consistent divisor values
    set_device_clock_rate(MBOX_CLK_ID_UART, 4000000, 1);

    // Map UART0 to GPIO pins
    r = *GPFSEL1;                   // GPFSEL1 controls function select for GPIO 10-19
    r &= ~((7<<12)|(7<<15));        // Clear GPIO14 (bits 14-12) and GPIO15 (bits 17-15)
    r |= (4<<12)|(4<<15);           // Set GPIO14 and GPIO15 to ALT0 (bit pattern 100)
    *GPFSEL1 = r;

    *GPPUD = 0;                     // No pull-up, no pull-down
    delay_cycles(150);              // Wait for around 150 cycles before applying
    *GPPUDCLK0 = (1<<14)|(1<<15);   // Apply pull-up/pull-down to GPIO14 and GPIO15
    delay_cycles(150);
    *GPPUDCLK0 = 0;                 // Clear the clock

    *PL011_ICR = 0x7FF;             // Clear all interrupts (bits 10-0)

    // The formula for baud rate is UART_CLOCK_RATE / (16 * (IBRD + FBRD/64))
    // For 115200 baud, we have a divisor of 2.1701389.
    // From this, IBRD = 2 and FBRD = .1701389 * 64 = 10.889 ≈ 11;
    *PL011_IBRD = 2;
    *PL011_FBRD = 11;
    *PL011_LCRH = 0;                // Clear the register
    *PL011_LCRH |= (0x3 << 5);      // WLEN = 11 (for 8 bits)
    *PL011_LCRH |= (1 << 4);        // FEN = 1 (enable FIFOs)
                                    // No need to set PEN since we want no parity
                                    // No need to set STP2 since we want 1 stop bit
    *PL011_CR = (0x3<<8)|(0x1);     // Enable TX and RX, and UART
}

// Send a character
void uart_sendc(unsigned int c) {
    // Wait until we can send
    do { asm volatile("nop"); } while (*PL011_FR & 0x20);
    // Write the character to the buffer
    *PL011_DR = c;
}

// Receive a character
char uart_getc() {
    char r;
    // Wait until something is in the buffer
    do { asm volatile("nop"); } while (*PL011_FR & 0x10);
    // Read the character
    r=(char)(*PL011_DR);
    // Convert carrige return to newline
    return r=='\r' ? '\n' : r;
}

// Write a string
void uart_puts(char *s) {
    while(*s) {
        // Convert newline to carrige return + newline
        if(*s=='\n')
            uart_sendc('\r');
        uart_sendc(*s++);
    }
}

// Display a (c+4)-bit binary value in hexadecimal
void uart_hex(unsigned long d, int c) {
    unsigned int n;
    for(; c >= 0; c -= 4) {
        // Get highest tetrad
        n = (d>>c) & 0xF;
        // 0-9 => '0'-'9', 10-15 => 'A'-'F'
        n += n > 9 ? ('A' - 10) : '0';
        uart_sendc(n);
    }
}

// Display a 32-bit binary value in hexadecimal
void uart_hex_u32(unsigned int d) {
    uart_hex((unsigned)d, 28); // 32 - 4
}

// Display a 64-bit binary value in hexadecimal
void uart_hex_u64(unsigned long d) {
    uart_hex(d, 60); // 64 - 4
}

/**
 * Dump memory
 */
void uart_dump(void *ptr)
{
    unsigned long a,b,d;
    unsigned char c;
    for(a=(unsigned long)ptr;a<(unsigned long)ptr+512;a+=16) {
        uart_hex_u32(a); uart_puts(": ");
        for(b=0;b<16;b++) {
            c=*((unsigned char*)(a+b));
            d=(unsigned int)c;d>>=4;d&=0xF;d+=d>9?0x37:0x30;uart_sendc(d);
            d=(unsigned int)c;d&=0xF;d+=d>9?0x37:0x30;uart_sendc(d);
            uart_sendc(' ');
            if(b%4==3)
                uart_sendc(' ');
        }
        for(b=0;b<16;b++) {
            c=*((unsigned char*)(a+b));
            uart_sendc(c<32||c>=127?'.':c);
        }
        uart_sendc('\r');
        uart_sendc('\n');
    }
}