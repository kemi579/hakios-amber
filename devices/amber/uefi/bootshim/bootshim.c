/*
 * Minimal BootShim for Xiaomi 11T (amber / MT6893)
 *
 * Current goal: bring up UART + GIC, print banner + memory map, then halt.
 * Later: real EFI_SYSTEM_TABLE + Boot Services and jump to an .efi.
 */

#include "uart.h"
#include "gic.h"
#include "memmap.h"

void bootshim_main(void)
{
    uart_init();
    uart_puts("\n\n*** HakiOS amber BootShim ***\n");
    uart_puts("SoC: MT6893 (Dimensity 1200)\n");

    gic_init();
    memmap_dump();

    uart_puts("[bootshim] halting\n");
    for (;;)
        __asm__ volatile("wfe");
}

void _start(void) __attribute__((section(".text.boot"), naked));
void _start(void)
{
    __asm__ volatile(
        "mov x0, sp\n"
        "bl  bootshim_main\n"
        "1: wfe\n"
        "b 1b\n"
    );
}
