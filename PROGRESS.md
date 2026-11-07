# HakiOS → Xiaomi 11T (amber / MT6893) — Progress Log

**Last update:** 2026-11-07

## Done
- Hardware addresses, platform_amber, firmware, BootShim skeleton + EFI services
- Bootloader confirmed unlocked, max-download 256 MiB
- Stock boot header analysed (header v2, kernel@0x40080000)
- Fixed mk_minimal_bootimg.py for real agate header values
- Minimal test payload (writes 0xDEADBEEFCAFEBABE + spin)
- **2026-11-07**: Added MediaTek-style chainloader (`devices/amber/chain/`)
  - `start.S` — WDT disable + magic + jump to stock Image
  - `chainboot.py` — packs program in front of stock kernel (from hakios-mt6768)
  - Pure BootShim approach abandoned for now (bootloop, no life signs)

## Repo
https://github.com/kemi579/hakios-amber

## Open questions / risks
- Does LK on MT6893 accept a chained gzip Image the same way as MT6768?
- Exact WDT base (0x10007000 is common, may need confirmation from Linux sources)
- AVB: flashing boot_b may still require `fastboot --disable-verity --disable-verification` or matching vbmeta
- No UART confirmed yet → magic in RAM is the only proof of execution

## Next
1. Build chain: `cd devices/amber/chain && make`
2. Pack: `python3 chainboot.py <stock_boot.img> chain.bin boot-chain.img`
3. Flash only to `boot_b` (stock stays on `boot_a`):
   ```
   fastboot flash boot_b boot-chain.img
   fastboot set_active b
   fastboot reboot
   ```
4. After Android boots — check magic at 0x40001000
5. If magic present → proceed to UART / framebuffer fill inside the chain payload
6. Only after reliable chain — expand toward full mtkloader + XNU
