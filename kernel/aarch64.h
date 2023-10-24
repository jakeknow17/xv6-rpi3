#include "types.h"


static inline uint64
r_mpidr_el1()
{
    uint64 x;
    asm volatile ("mrs %0, mpidr_el1" : "=r" (x));
    return x;
}