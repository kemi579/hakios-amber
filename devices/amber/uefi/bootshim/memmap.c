#include "memmap.h"
#include "uart.h"

const mem_region_t amber_mem_regions[] = {
    { 0x00000000ULL, 0x0c000000ULL, MEM_MMIO },
    { 0x0c000000ULL, 0x0c240000ULL, MEM_MMIO },
    { 0x11000000ULL, 0x12000000ULL, MEM_MMIO },
    { 0x40000000ULL, 0xC0000000ULL, MEM_CONVENTIONAL },
    { 0xC0000000ULL, 0x100000000ULL, MEM_RESERVED },
    { 0xF0000000ULL, 0xF4000000ULL, MEM_RESERVED },
};

const unsigned amber_mem_region_count =
    sizeof(amber_mem_regions) / sizeof(amber_mem_regions[0]);

void memmap_dump(void)
{
    uart_puts("[memmap]\n");
    for (unsigned i = 0; i < amber_mem_region_count; i++) {
        const mem_region_t *r = &amber_mem_regions[i];
        uart_hex64(r->phys_start);
        uart_puts(" - ");
        uart_hex64(r->phys_end);
        uart_puts(" type=");
        uart_putc('0' + r->type);
        uart_puts("\n");
    }
}
