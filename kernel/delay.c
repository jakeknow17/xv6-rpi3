#include "memlayout.h"
#include "types.h"

// Wait N CPU cycles (ARM CPU only)
void delay_cycles(uint32 n)
{
    if(n)
        while(n--) { asm volatile("nop"); }
}

// Wait N microseconds (ARM CPU only)
void delay_msec(uint32 n)
{
    register unsigned long f, t, r;
    // Get the current counter frequency in Hz
    asm volatile ("mrs %0, cntfrq_el0" : "=r" (f));
    // Read the current counter
    asm volatile ("mrs %0, cntpct_el0" : "=r" (t));
    // Calculate required count increase
    // Divide by 1000 to convert from seconds to milliseconds
    unsigned long i = ((f/1000) * n) / 1000;

    // loop while counter increase is less than i
    do { asm volatile ("mrs %0, cntpct_el0" : "=r" (r)); } while(r - t < i);
}

/**
 * Get System Timer's counter
 */
uint64 get_system_timer()
{
    uint32 h=-1, l;

    h = *SYS_TIMER_CHI; // Upper 32 bits
    l = *SYS_TIMER_CLO; // Lower 32 bits

    // Repeat the read if upper 32 bits changed
    if(h != *SYS_TIMER_CHI) {
        h = *SYS_TIMER_CHI;
        l = *SYS_TIMER_CLO;
    }
    
    return ((uint64) h << 32) | l;
}

// Wait N microsec (with BCM System Timer)
void delay_msec_st(uint32 n)
{
    uint64 t=get_system_timer();
    // Qemu does not emulate the system timer,
    // so we need to check if the timer returned zero
    if (t)
        while(get_system_timer() - t < n);
}