#pragma once
#include <stdint.h>

#define UART0_BASE  0x11002000ULL

void uart_init(void);
void uart_putc(char c);
void uart_puts(const char *s);
void uart_hex64(uint64_t v);
