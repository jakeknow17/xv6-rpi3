#ifndef AARCH64_H
#define AARCH64_H

#include "types.h"

static inline uint64
r_mpidr_el1()
{
    uint64 x;
    asm volatile ("mrs %0, mpidr_el1" : "=r" (x));
    return x;
}

static inline uint64
r_CurrentEL()
{
    uint64 x;
    asm volatile ("mrs %0, CurrentEL" : "=r" (x));
    return x;
}

static inline uint64
r_sctlr_el1()
{
    uint64 x;
    asm volatile ("mrs %0, sctlr_el1" : "=r" (x));
    return x;
}

static inline void
nop()
{
    asm volatile ("nop");
}

#endif /* AARCH64_H */