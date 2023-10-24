.section ".text.boot"

.global _entry

_entry:
    ldr x0, =stack0
    mov sp, x0
    mov x0, #4096
    mrs x1, mpidr_el1
    add	x1, x1, 1
    mul x0, x0, x1
    add sp, sp, x0
    // jump to start() in start.c
    bl start
spin:
    b spin