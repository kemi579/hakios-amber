# HakiOS → Xiaomi 11T (amber / MT6893) — Progress Log

**Last update:** 2026-10-26 12:37

## Done
- Live GIC / UART / memory / PSCI addresses extracted
- devices/amber/ skeleton created (matching current HakiOS layout)
- platform_amber.h/.c with all known constants
- pull-firmware.sh ready
- GitHub repo https://github.com/kemi579/hakios-amber populated
- XnuLoader.c and MemoryMapLib from redwood analysed
- Payload convention: 0xF0000000 + "XNUP" magic

## In progress
- Full mblock parser
- Understanding exact requirements for a minimal BootShim

## Next
1. Pull firmware from phone into fw-gpu / fw-wifi
2. Document amber memory map for future UEFI/BootShim
3. Start minimal BootShim design (after platform is solid)
