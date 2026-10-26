/* Minimal start for amber BootShim */
.section .text.boot, "ax"
.global _start
.extern bootshim_main
.extern __bss_start
.extern __bss_end

_start:
    ldr  x0, =0x41000000
    mov  sp, x0

    ldr  x1, =__bss_start
    ldr  x2, =__bss_end
1:
    cmp  x1, x2
    b.hs 2f
    str  xzr, [x1], #8
    b    1b
2:
    bl   bootshim_main
3:
    wfe
    b    3b
