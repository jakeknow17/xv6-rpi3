#ifndef DEFS_H
#define DEFS_H

#include "types.h"

// delay.c
void    delay_cycles(uint32);
void    delay_msec(uint32);
void    delay_msec_st(uint32 n);
uint64  get_system_timer(void);

// uart.c
void    uart_init(void);
void    uart_sendc(uint32);
char    uart_getc(void);
void    uart_puts(char *);
void    uart_hex_u32(uint32);
void    uart_hex_u64(uint64);

#endif /* DEFS_H */