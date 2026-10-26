#include "uart.h"

#define UART_RBR    0x00
#define UART_THR    0x00
#define UART_LSR    0x14
#define UART_LSR_THRE  0x20

static inline void mmio_write32(uint64_t addr, uint32_t val)
{
    *(volatile uint32_t *)addr = val;
}

static inline uint32_t mmio_read32(uint64_t addr)
{
    return *(volatile uint32_t *)addr;
}

void uart_init(void)
{
    /* Assume already configured by LK / previous stage. */
}

void uart_putc(char c)
{
    while ((mmio_read32(UART0_BASE + UART_LSR) & UART_LSR_THRE) == 0)
        ;
    mmio_write32(UART0_BASE + UART_THR, (uint32_t)(uint8_t)c);
}

void uart_puts(const char *s)
{
    while (*s) {
        if (*s == '\n')
            uart_putc('\r');
        uart_putc(*s++);
    }
}

void uart_hex64(uint64_t v)
{
    static const char hex[] = "0123456789abcdef";
    uart_puts("0x");
    for (int i = 60; i >= 0; i -= 4)
        uart_putc(hex[(v >> i) & 0xf]);
}
