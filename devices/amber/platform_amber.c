/*
 * platform_amber.c
 * Preliminary constants for the amber (MT6893) platform.
 */

#include "platform_amber.h"

const char amber_name[] = "amber";

const uint64_t amber_gic_dist   = AMBER_GICD_BASE;
const uint64_t amber_gic_redist = AMBER_GICR_BASE;
const uint64_t amber_uart       = AMBER_UART0_BASE;
const int      amber_cores      = AMBER_CORES;
const int      amber_psci_smc   = AMBER_PSCI_METHOD_SMC;
