#include "efi.h"
#include "memmap.h"
#include "uart.h"

static EFI_PHYSICAL_ADDRESS alloc_top = 0xBFF00000ULL;

static EFI_STATUS shim_AllocatePages(UINT32 Type, UINT32 MemoryType, UINTN Pages, EFI_PHYSICAL_ADDRESS *Memory)
{
    (void)Type; (void)MemoryType;
    if (Pages == 0 || Memory == NULL) return EFI_INVALID_PARAMETER;
    UINTN size = Pages * EFI_PAGE_SIZE;
    if (alloc_top < 0x40000000ULL + size) return EFI_OUT_OF_RESOURCES;
    alloc_top -= size;
    *Memory = alloc_top;
    uart_puts("[efi] AllocatePages "); uart_hex64(*Memory); uart_puts("\n");
    return EFI_SUCCESS;
}

static EFI_STATUS shim_FreePages(EFI_PHYSICAL_ADDRESS Memory, UINTN Pages)
{
    (void)Memory; (void)Pages;
    return EFI_SUCCESS;
}

static EFI_STATUS shim_GetMemoryMap(UINTN *MemoryMapSize, EFI_MEMORY_DESCRIPTOR *MemoryMap,
                                    UINTN *MapKey, UINTN *DescriptorSize, UINT32 *DescriptorVersion)
{
    const UINTN needed = amber_mem_region_count * sizeof(EFI_MEMORY_DESCRIPTOR);
    if (DescriptorSize) *DescriptorSize = sizeof(EFI_MEMORY_DESCRIPTOR);
    if (DescriptorVersion) *DescriptorVersion = 1;
    if (MapKey) *MapKey = 0xA11CE;
    if (MemoryMapSize == NULL) return EFI_INVALID_PARAMETER;
    if (*MemoryMapSize < needed) { *MemoryMapSize = needed; return EFI_BUFFER_TOO_SMALL; }
    if (MemoryMap == NULL) return EFI_INVALID_PARAMETER;
    for (unsigned i = 0; i < amber_mem_region_count; i++) {
        const mem_region_t *r = &amber_mem_regions[i];
        EFI_MEMORY_DESCRIPTOR *d = &MemoryMap[i];
        d->Type = (r->type == MEM_CONVENTIONAL) ? EFI_MEMORY_CONVENTIONAL_MEMORY :
                  (r->type == MEM_MMIO) ? EFI_MEMORY_MMIO : EFI_MEMORY_RESERVED;
        d->PhysicalStart = r->phys_start;
        d->VirtualStart  = 0;
        d->NumberOfPages = EFI_SIZE_TO_PAGES(r->phys_end - r->phys_start);
        d->Attribute     = 0;
    }
    *MemoryMapSize = needed;
    uart_puts("[efi] GetMemoryMap ok\n");
    return EFI_SUCCESS;
}

static EFI_STATUS shim_ExitBootServices(EFI_HANDLE ImageHandle, UINTN MapKey)
{
    (void)ImageHandle; (void)MapKey;
    uart_puts("[efi] ExitBootServices\n");
    return EFI_SUCCESS;
}

static EFI_STATUS shim_Stall(UINTN Microseconds)
{
    for (volatile UINTN i = 0; i < Microseconds * 10; i++) ;
    return EFI_SUCCESS;
}

static EFI_STATUS shim_SetWatchdogTimer(UINTN Timeout, uint64_t WatchdogCode, UINTN DataSize, CHAR16 *WatchdogData)
{
    (void)Timeout; (void)WatchdogCode; (void)DataSize; (void)WatchdogData;
    return EFI_SUCCESS;
}

static EFI_BOOT_SERVICES boot_services;
static EFI_SYSTEM_TABLE  system_table;

void efi_init(void)
{
    for (UINTN i = 0; i < sizeof(boot_services); i++) ((CHAR8 *)&boot_services)[i] = 0;
    for (UINTN i = 0; i < sizeof(system_table); i++) ((CHAR8 *)&system_table)[i] = 0;

    boot_services.AllocatePages     = shim_AllocatePages;
    boot_services.FreePages         = shim_FreePages;
    boot_services.GetMemoryMap      = shim_GetMemoryMap;
    boot_services.ExitBootServices  = shim_ExitBootServices;
    boot_services.Stall             = shim_Stall;
    boot_services.SetWatchdogTimer  = shim_SetWatchdogTimer;

    system_table.Hdr.Signature = 0x5453595320494249ULL;
    system_table.Hdr.Revision  = 0x0002001E;
    system_table.BootServices  = &boot_services;

    uart_puts("[efi] Boot Services table ready\n");
}

EFI_SYSTEM_TABLE *efi_get_system_table(void)
{
    return &system_table;
}
