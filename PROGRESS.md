# HakiOS → Xiaomi 11T (amber / MT6893) — Progress Log

**Last update:** 2026-10-26 12:44

## Done
- Hardware addresses extracted
- devices/amber/ + platform_amber
- Firmware stored locally
- BootShim skeleton with:
  - UART (0x11002000)
  - minimal GICv3
  - static memory map
  - EFI Boot Services stubs: GetMemoryMap, AllocatePages, FreePages, ExitBootServices, Stall, SetWatchdogTimer
  - self-test of GetMemoryMap

## Repo
https://github.com/kemi579/hakios-amber

## Next
- Cross-compile test
- Real payload loading path
- How to get bootshim.bin into the phone via fastboot
