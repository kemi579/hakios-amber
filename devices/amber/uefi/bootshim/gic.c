#include "gic.h"
#include "uart.h"

static inline void mmio_write32(uint64_t a, uint32_t v) { *(volatile uint32_t *)a = v; }
static inline uint32_t mmio_read32(uint64_t a) { return *(volatile uint32_t *)a; }

void gic_init(void)
{
    mmio_write32(GICD_BASE + 0x0000, 0);
    mmio_write32(GICR_BASE + 0x0014, 0);
    mmio_write32(GICD_BASE + 0x0000, 0x2);
    uart_puts("[gic] minimal init done\n");
}
