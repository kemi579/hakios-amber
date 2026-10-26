#pragma once
#include <stdint.h>

#define GICD_BASE   0x0c000000ULL
#define GICR_BASE   0x0c040000ULL

void gic_init(void);
