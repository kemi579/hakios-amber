# HakiOS → Xiaomi 11T (amber / MT6893) — Progress Log

**Last update:** 2026-10-26 12:40

## Done
- Hardware addresses (GIC, UART, DRAM, PSCI) extracted via root
- devices/amber/ skeleton + platform_amber.h/.c
- Firmware files received and stored locally (GPU + Connsys)
- XnuLoader / MemoryMapLib / payload convention analysed
- BootShim design document written
- GitHub: https://github.com/kemi579/hakios-amber

## Current focus
Minimal BootShim requirements are clear. Next concrete coding step is a UART + memory-map skeleton.

## Still open
- Full mblock parser
- Framebuffer physical address
- Actual BootShim implementation (starts after this)
