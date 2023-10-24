// .section ".text.boot"

// .global _entry

// _entry:
//     // set up a stack for C.
//     // stack0 is declared in start.c,
//     // with a 4096-byte stack per CPU.
//     // sp = stack0 + (coreid * 4096)
//     ldr x0, =stack0
//     mov sp, x0
//     mov x0, #4096
//     mrs x1, mpidr_el1   // read core id
//     add	x1, x1, 1
//     mul x0, x0, x1
//     add sp, sp, x0      // calculate offset
//     bl start            // jump to start() in start.c
// spin:
//     b spin

/*
 * Copyright (C) 2018 bzt (bztsrc@github)
 *
 * Permission is hereby granted, free of charge, to any person
 * obtaining a copy of this software and associated documentation
 * files (the "Software"), to deal in the Software without
 * restriction, including without limitation the rights to use, copy,
 * modify, merge, publish, distribute, sublicense, and/or sell copies
 * of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be
 * included in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 * NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT
 * HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
 * WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
 * DEALINGS IN THE SOFTWARE.
 *
 */

.section ".text.boot"

.global _start

_start:
    // read cpu id, stop slave cores
    mrs     x1, mpidr_el1
    and     x1, x1, #3
    cbz     x1, 2f
    // cpu id > 0, stop
1:  wfe
    b       1b
2:  // cpu id == 0

    // set top of stack just before our code (stack grows to a lower address per AAPCS64)
    ldr     x1, =_start
    mov     sp, x1

    // clear bss
//    ldr     x1, =__bss_start
//    ldr     w2, =__bss_size
//3:  cbz     w2, 4f
//    str     xzr, [x1], #8
//    sub     w2, w2, #1
//    cbnz    w2, 3b

    // jump to C code, should not return
4:  bl      start
    // for failsafe, halt this core too
    b       1b