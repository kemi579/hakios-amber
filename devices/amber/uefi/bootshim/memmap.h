#pragma once
#include <stdint.h>

typedef struct {
    uint64_t phys_start;
    uint64_t phys_end;
    uint32_t type;
} mem_region_t;

#define MEM_CONVENTIONAL  0
#define MEM_RESERVED      1
#define MEM_MMIO          2

extern const mem_region_t amber_mem_regions[];
extern const unsigned amber_mem_region_count;

void memmap_dump(void);
