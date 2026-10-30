/*
 * Minimal entry for Xiaomi 11T (amber / MT6893)
 *
 * Linked at 0x40080000.
 * Tries to kill the MediaTek watchdog (0x10007000) so we don't reboot after ~13s.
 */
.section .text.boot, "ax"
.global _start

.weak bootshim_main

_start:
    /* set stack */
    ldr  x0, =0x41000000
    mov  sp, x0

    /*--------------------------------------------------------------
     * Disable MediaTek WDT (common base 0x10007000)
     * WDT_MODE = base + 0x00
     * bit0 = EN, key = 0x22000000
     *--------------------------------------------------------------*/
    ldr  x1, =0x10007000          /* WDT_MODE */
    ldr  w2, [x1]                 /* read current mode */
    and  w2, w2, #0xFFFFFFFE      /* clear EN bit */
    movz w3, #0x2200, lsl #16     /* KEY = 0x22000000 */
    orr  w2, w2, w3
    str  w2, [x1]                 /* write back → disable */

    /* also restart once just in case */
    ldr  x1, =0x10007008          /* WDT_RST */
    movz w2, #0x1971
    str  w2, [x1]

    /* write magic so we know we ran */
    ldr  x1, =0x40001000
    ldr  x2, =0xDEADBEEFCAFEBABE
    str  x2, [x1]

    /* call C if present */
    adr  x0, bootshim_main
    cbz  x0, 3f
    bl   bootshim_main

3:  /* infinite loop */
    wfe
    b    3b

.section .text
.weak bootshim_main
bootshim_main:
    ret
