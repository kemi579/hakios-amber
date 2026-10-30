#pragma once
#include <stdint.h>

#ifndef NULL
#define NULL ((void *)0)
#endif

typedef uint64_t  EFI_STATUS;
typedef uint64_t  EFI_PHYSICAL_ADDRESS;
typedef uint64_t  EFI_VIRTUAL_ADDRESS;
typedef void     *EFI_HANDLE;
typedef uint64_t  UINTN;
typedef uint32_t  UINT32;
typedef uint16_t  UINT16;
typedef uint8_t   UINT8;
typedef uint64_t  UINT64;
typedef char      CHAR8;
typedef uint16_t  CHAR16;

#define EFI_SUCCESS               0
#define EFI_INVALID_PARAMETER     2
#define EFI_BUFFER_TOO_SMALL      5
#define EFI_OUT_OF_RESOURCES      9

#define EFI_MEMORY_CONVENTIONAL_MEMORY   7
#define EFI_MEMORY_RESERVED              0
#define EFI_MEMORY_MMIO                  11

typedef struct {
    uint32_t Type;
    uint32_t Pad;
    EFI_PHYSICAL_ADDRESS PhysicalStart;
    EFI_VIRTUAL_ADDRESS  VirtualStart;
    uint64_t NumberOfPages;
    uint64_t Attribute;
} EFI_MEMORY_DESCRIPTOR;

#define EFI_PAGE_SIZE  4096ULL
#define EFI_SIZE_TO_PAGES(s)  (((s) + EFI_PAGE_SIZE - 1) / EFI_PAGE_SIZE)

typedef struct {
    uint64_t Signature;
    uint32_t Revision;
    uint32_t HeaderSize;
    uint32_t CRC32;
    uint32_t Reserved;
} EFI_TABLE_HEADER;

typedef EFI_STATUS (*EFI_GET_MEMORY_MAP)(UINTN *, EFI_MEMORY_DESCRIPTOR *, UINTN *, UINTN *, UINT32 *);
typedef EFI_STATUS (*EFI_ALLOCATE_PAGES)(UINT32, UINT32, UINTN, EFI_PHYSICAL_ADDRESS *);
typedef EFI_STATUS (*EFI_FREE_PAGES)(EFI_PHYSICAL_ADDRESS, UINTN);
typedef EFI_STATUS (*EFI_EXIT_BOOT_SERVICES)(EFI_HANDLE, UINTN);
typedef EFI_STATUS (*EFI_STALL)(UINTN);
typedef EFI_STATUS (*EFI_SET_WATCHDOG_TIMER)(UINTN, uint64_t, UINTN, CHAR16 *);

typedef struct EFI_BOOT_SERVICES {
    EFI_TABLE_HEADER Hdr;
    void *RaiseTPL;
    void *RestoreTPL;
    EFI_ALLOCATE_PAGES AllocatePages;
    EFI_FREE_PAGES FreePages;
    EFI_GET_MEMORY_MAP GetMemoryMap;
    void *AllocatePool;
    void *FreePool;
    EFI_STALL Stall;
    EFI_SET_WATCHDOG_TIMER SetWatchdogTimer;
    EFI_EXIT_BOOT_SERVICES ExitBootServices;
} EFI_BOOT_SERVICES;

typedef struct EFI_SYSTEM_TABLE {
    EFI_TABLE_HEADER Hdr;
    CHAR16 *FirmwareVendor;
    UINT32 FirmwareRevision;
    EFI_HANDLE ConsoleInHandle;
    void *ConIn;
    EFI_HANDLE ConsoleOutHandle;
    void *ConOut;
    EFI_HANDLE StandardErrorHandle;
    void *StdErr;
    void *RuntimeServices;
    EFI_BOOT_SERVICES *BootServices;
    UINTN NumberOfTableEntries;
    void *ConfigurationTable;
} EFI_SYSTEM_TABLE;

void efi_init(void);
EFI_SYSTEM_TABLE *efi_get_system_table(void);
