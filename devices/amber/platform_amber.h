/* platform_amber.h — Xiaomi 11T (MT6893 / Dimensity 1200)
 * Live DT extraction 2026-10-26 (root)
 */

#pragma once

#include <stdint.h>

/* GICv3 */
#define AMBER_GICD_BASE          0x0c000000ULL
#define AMBER_GICD_SIZE          0x00040000ULL
#define AMBER_GICR_BASE          0x0c040000ULL
#define AMBER_GICR_SIZE          0x00200000ULL
#define AMBER_GIC_REDIST_REGIONS 1
#define AMBER_GIC_INTERRUPT_CELLS 3

/* UART (mediatek,mt6577-uart) */
#define AMBER_UART0_BASE         0x11002000ULL
#define AMBER_UART1_BASE         0x11003000ULL
#define AMBER_UART_SIZE          0x00001000ULL

/* DRAM */
#define AMBER_DRAM_BASE          0x40000000ULL
#define AMBER_DRAM_SIZE          0x200000000ULL   /* 8 GiB */
/* Conservative early usable window (avoid TEE / high reserved) */
#define AMBER_USABLE_BASE        0x40000000ULL
#define AMBER_USABLE_SIZE        0x80000000ULL    /* first 2 GiB until full mblock */

/* PSCI */
#define AMBER_PSCI_METHOD_SMC    1

/* CPU */
#define AMBER_CORES              8

/* Known firmware paths on device */
#define AMBER_FW_GPU             "/vendor/firmware/valhall-1691526.wa"
#define AMBER_FW_WIFI_PREFIX     "/vendor/firmware/soc3_0_"
