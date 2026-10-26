/*
 * Minimal BootShim for Xiaomi 11T (amber / MT6893)
 * Entry is in start.S
 */

#include "uart.h"
#include "gic.h"
#include "memmap.h"
#include "efi.h"

void bootshim_main(void)
{
    uart_init();
    uart_puts("\n\n*** HakiOS amber BootShim ***\n");
    uart_puts("SoC: MT6893 (Dimensity 1200)\n");

    gic_init();
    memmap_dump();
    efi_init();

    EFI_SYSTEM_TABLE *st = efi_get_system_table();
    UINTN map_size = 0, map_key, desc_size;
    UINT32 desc_ver;
    EFI_STATUS s = st->BootServices->GetMemoryMap(
        &map_size, NULL, &map_key, &desc_size, &desc_ver);
    uart_puts("[test] GetMemoryMap -> ");
    uart_hex64(s);
    uart_puts(" size=");
    uart_hex64(map_size);
    uart_puts("\n");

    uart_puts("[bootshim] ready – halting\n");
    for (;;)
        __asm__ volatile("wfe");
}
