/* platform_amber.h — preliminary for Xiaomi 11T (MT6893 / Dimensity 1200)
 * Extracted from live device tree via root 2026-10-26
 * Compatible with xnuloader struct platform
 */

#pragma once

#define AMBER_GICD_BASE     0x0c000000ULL
#define AMBER_GICD_SIZE     0x00040000ULL
#define AMBER_GICR_BASE     0x0c040000ULL
#define AMBER_GICR_SIZE     0x00200000ULL

#define AMBER_UART0_BASE    0x11002000ULL   /* serial@11002000 */
#define AMBER_UART1_BASE    0x11003000ULL   /* serial@11003000 */
#define AMBER_UART_SIZE     0x1000ULL

#define AMBER_MEMORY_BASE   0x40000000ULL
#define AMBER_MEMORY_SIZE   0x200000000ULL  /* 8 GiB */

#define AMBER_CORES         8
/* 1x A78 @3.0 + 3x A78 @2.6 + 4x A55 @2.0 → core_shift / small_cores to be tuned */
