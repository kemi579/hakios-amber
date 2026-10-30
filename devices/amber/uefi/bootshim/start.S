/*
 * Minimal entry for Xiaomi 11T (amber / MT6893)
 *
 * Linked at 0x40080000 (same as stock kernel).
 * Stack at 0x41000000.
 *
 * When built with MINIMAL=1 this file is the only object:
 * it just writes a magic value and spins.
 */
.section .text.boot, "ax"
.global _start

/* weak so that when bootshim.o is not linked we still build */
.weak bootshim_main

_start:
    /* set stack */
    ldr  x0, =0x41000000
    mov  sp, x0

    /* write magic so we know we ran (0x40001000 is early DRAM) */
    ldr  x1, =0x40001000
    ldr  x2, =0xDEADBEEFCAFEBABE
    str  x2, [x1]

    /* try to call C entry if it exists */
    adr  x0, bootshim_main
    cbz  x0, 3f
    bl   bootshim_main

3:  /* infinite loop */
    wfe
    b    3b

/* provide a weak empty stub so the linker is happy in MINIMAL mode */
.section .text
.weak bootshim_main
bootshim_main:
    ret
