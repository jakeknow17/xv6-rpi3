.global delay_cycles

// void delay_cycles(unsigned long cycles);
delay_cycles:
    // Check if number of cycles is zero or negative
    cbz x0, end_delay_cycles

delay_cycles_loop:
    // Decrement the cycles count
    sub x0, x0, #1

    // If not zero, repeat
    cbnz x0, delay_cycles_loop

end_delay_cycles:
    ret
