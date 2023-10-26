

// delay.S
void    delay_cycles(unsigned long);

// uart.c
void    uart_init(void);
void    uart_sendc(unsigned int);
char    uart_getc(void);
void    uart_puts(char *);
void    uart_hex_u32(unsigned int);
void    uart_hex_u64(unsigned long);