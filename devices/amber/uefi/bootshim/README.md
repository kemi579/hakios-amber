# Minimal BootShim for amber (MT6893)

Goal: provide the smallest possible UEFI Boot Services environment
so that an EFI application (xnuloader.efi or a test payload) can run.

## Current status
Skeleton only. No binary yet.

## Files
- `bootshim.c`   – entry + minimal Boot Services table
- `uart.c` / `uart.h` – early console on 0x11002000
- `gic.c` / `gic.h`   – very basic GICv3 init
- `memmap.c`          – static memory map
- `link.ld`           – linker script
- `Makefile`          – cross-compile with aarch64-none-elf-

## Build (once toolchain is present)
```
make CROSS=aarch64-none-elf-
```
Produces `bootshim.elf` / `bootshim.bin`.
