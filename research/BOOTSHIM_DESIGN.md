# Minimal BootShim design for amber (MT6893)

## Goal
Provide just enough UEFI Boot Services so that the existing xnuloader.efi
(or a future MediaTek-aware loader) can run and hand off to XNU.

## What xnuloader actually needs (from redwood analysis)
From XnuLoader.c / payload convention:
- GetMemoryMap / AllocatePages / ExitBootServices
- Optional Graphics Output Protocol (framebuffer)
- A reserved region at 0xF0000000 (64 MiB) containing the XNUP payload
- GIC already usable or initialised by the shim
- UART for early console (optional but highly useful)

## Minimal set of Boot Services to implement
1. GetMemoryMap
2. AllocatePages / FreePages (simple bump or bitmap)
3. ExitBootServices
4. LocateProtocol (at least GOP if we have framebuffer, otherwise stub)
5. SetWatchdogTimer (can be no-op)
6. Stall / RaiseTPL / RestoreTPL (minimal)

## Platform init the shim must do
- Program GICD / GICR bases (0x0c000000 / 0x0c040000)
- Enable the redistributor for the boot CPU
- Set up a simple identity map or rely on the loader
- Initialise one UART (0x11002000 or 0x11003000) for debug output
- Build a memory map from the conservative usable window + known reserved regions

## Possible implementations
A. Pure assembly + tiny C BootShim that never calls into EDK2
B. Extremely stripped EDK2 / U-Boot EFI_LOADER port that only brings up GIC + UART + memory map
C. Chain from a custom LK payload that jumps directly into a non-UEFI loader (longer term)

For the first working path we prefer A or a very thin B.

## Next implementation steps
1. Freeze the memory map table for amber (usable + reserved)
2. Write a skeleton BootShim that prints to UART and builds a fake GetMemoryMap
3. Test load of a trivial EFI application via fastboot (if the bootloader allows)
