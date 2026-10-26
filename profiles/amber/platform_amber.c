/*
 * platform_amber.c — preliminary platform description for Xiaomi 11T (MT6893)
 *
 * This is a draft matching the known xnuloader struct platform layout
 * (name, io_base/io_size, gic_dist, gic_redist, uart, psci_hvc, cores, ...).
 * Exact field order must be verified against current loader source.
 */

#include "platform_amber.h"

/*
 * Example shape (to be adjusted once loader source is confirmed):
 *
 * static const struct platform platform_amber = {
 *     .name         = "amber",
 *     .io_base      = 0x00000000,          // or actual peripheral window
 *     .io_size      = 0x20000000,
 *     .gic_dist     = AMBER_GICD_BASE,
 *     .gic_redist   = AMBER_GICR_BASE,
 *     .uart         = AMBER_UART0_BASE,    // or 0 if early console elsewhere
 *     .psci_hvc     = 0,                   // method=smc → 0
 *     .cores        = AMBER_CORES,
 *     .core_shift   = 0,                   // TBD from topology
 *     .timeout_scale= 1,
 *     .small_cores  = 0xF0,                // lower 4 bits A55?
 * };
 */

const char *amber_platform_name = "amber";
uint64_t amber_gic_dist   = AMBER_GICD_BASE;
uint64_t amber_gic_redist = AMBER_GICR_BASE;
uint64_t amber_uart       = AMBER_UART0_BASE;
int     amber_cores       = AMBER_CORES;
