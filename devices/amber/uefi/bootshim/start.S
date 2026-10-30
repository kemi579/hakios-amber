/*
 * Minimal entry for Xiaomi 11T (amber / MT6893)
 *
 * Linked at 0x40080000 (same as stock kernel).
 * Stack at 0x41000000.
 *
 * When built with MINIMAL=1 this file is the only object:
 * it just writes a magic value and spins so we can later
 * check RAM if we ever get a way to read it back.
 */
.section .text.boot, "ax"
.global _start
.extern bootshim_main
.extern __bss_start
.extern __bss_end

_start:
    /* set stack */
    ldr  x0, =0x41000000
    mov  sp, x0

    /* write magic so we know we ran (0x40001000 is early DRAM) */
    ldr  x1, =0x40001000
    ldr  x2, =0xDEADBEEFCAFEBABE
    str  x2, [x1]

    /* clear .bss if symbols exist (full build) */
    ldr  x1, =__bss_start
    ldr  x2, =__bss_end
1:
    cmp  x1, x2
    b.hs 2f
    str  xzr, [x1], #8
    b    1b
2:
    /* jump to C if linked, otherwise just spin */
    bl   bootshim_main

3:  /* infinite loop */
    wfe
    b    3b
