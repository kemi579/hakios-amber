# HakiOS → Xiaomi 11T (amber / MT6893) — Progress Log

**Last update:** 2026-10-26 12:39

## Done
- Live GIC / UART / memory / PSCI addresses extracted
- devices/amber/ skeleton created
- platform_amber.h/.c with known constants
- pull-firmware.sh ready
- Firmware files successfully pulled by user (GPU + main Connsys set)
- XnuLoader + MemoryMapLib (redwood) analysed
- Payload convention documented (0xF0000000 + XNUP)

## In progress
- Full mblock understanding
- Minimal BootShim design notes

## Next concrete actions
1. Place pulled firmware into local clone under devices/amber/fw-*
2. Continue memory map + BootShim requirements
3. Later: actual UEFI/BootShim implementation
