.section ".text.boot"

.global _entry

_entry:
    // set up a stack for C.
    // stack0 is declared in start.c,
    // with a 4096-byte stack per CPU.
    // sp = stack0 + (coreid * 4096)
    ldr x0, =stack0
    mov sp, x0
    mov x0, #4096
    mrs x1, mpidr_el1   // read core id
    and x1, x1, #3
    add	x1, x1, 1
    mul x0, x0, x1
    add sp, sp, x0      // calculate offset
    bl start            // jump to start() in start.c
spin:
    wfe
    b spin