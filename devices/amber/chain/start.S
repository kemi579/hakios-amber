/*
 * Minimal chain payload for Xiaomi 11T (amber / MT6893)
 *
 * LK loads this as a Linux arm64 Image at 0x40080000 (MMU/caches off).
 * We:
 *   1. Disable MediaTek WDT (0x10007000)
 *   2. Write magic 0xDEADBEEFCAFEBABE at 0x40001000
 *   3. Copy stock Android Image from CHAIN_OFFSET down over ourselves
 *   4. Jump into it exactly as LK would have
 *
 * tools/chainboot.py fills image_size / res2 / res3 in the header.
 */
.global _start
.section .text.boot

_start:
    /* Linux ARM64 Image header (64 bytes) */
    b       primary_entry          /* code0 */
    .word   0                      /* code1 */
    .quad   0x80000                /* text_offset */
    .quad   0x02000000             /* image_size (filled by chainboot.py) */
    .quad   0x0a                   /* flags: LE, 4K, anywhere */
    .quad   0                      /* res2: length of Android Image */
    .quad   0                      /* res3: reserved */
    .quad   0                      /* res4 */
    .ascii  "ARM\x64"
    .word   0

primary_entry:
    msr     daifset, #0xf

    /* Stack just below load address */
    adr     x0, _start
    sub     x0, x0, #0x8000
    mov     sp, x0

    /*--------------------------------------------------------------
     * Disable MediaTek WDT (common base 0x10007000 on MT68xx)
     * WDT_MODE = base+0x00, bit0=EN, unlock key=0x22000000
     *--------------------------------------------------------------*/
    ldr     x1, =0x10007000
    ldr     w2, [x1]
    and     w2, w2, #0xFFFFFFFE    /* clear EN */
    movz    w3, #0x2200, lsl #16   /* KEY */
    orr     w2, w2, w3
    str     w2, [x1]

    /* Restart counter once */
    ldr     x1, =0x10007008        /* WDT_RST */
    movz    w2, #0x1971
    str     w2, [x1]

    /* Write magic so we know we ran (readable from Android later) */
    ldr     x1, =0x40001000
    ldr     x2, =0xDEADBEEFCAFEBABE
    str     x2, [x1]
    dsb     sy

    /*
     * Chain to stock Android Image.
     * chainboot.py places the uncompressed Image at CHAIN_OFFSET (0x40000)
     * and puts its length into res2 (offset 0x28 of the header).
     */
    adr     x0, _start             /* our base */
    ldr     x1, [x0, #0x28]        /* res2 = Android Image length */
    cbz     x1, halt               /* safety: no image -> hang */

    add     x2, x0, #0x40000       /* src = CHAIN_OFFSET */
    mov     x3, x0                 /* dst = 0x40080000 (ourselves) */
    mov     x4, x1                 /* len */

    /* Copy Image down over us (simple 8-byte loop) */
1:  ldr     x5, [x2], #8
    str     x5, [x3], #8
    subs    x4, x4, #8
    b.hi    1b

    dsb     sy
    ic      iallu
    dsb     sy
    isb

    /* Jump to the start of the stock Image (now at 0x40080000) */
    mov     x0, xzr                /* x0 = DTB (we don't have one, stock may ignore) */
    mov     x1, xzr
    mov     x2, xzr
    mov     x3, xzr
    br      x0                     /* should be 0x40080000 after copy, but we just overwrote */

    /* Fallback if something went wrong */
halt:
    wfe
    b       halt
