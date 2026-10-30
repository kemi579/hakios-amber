# HakiOS → Xiaomi 11T (amber / MT6893) — Progress Log

**Last update:** 2026-10-30

## Done
- Hardware addresses, platform_amber, firmware, BootShim skeleton + EFI services
- Bootloader confirmed unlocked, max-download 256 MiB
- Stock boot header analysed (header v2, kernel@0x40080000)
- Fixed mk_minimal_bootimg.py for real agate header values
- Minimal test payload (writes 0xDEADBEEFCAFEBABE + spin)

## Repo
https://github.com/kemi579/hakios-amber

## Next
1. Build minimal test: `make MINIMAL=1 CROSS=aarch64-linux-gnu-`
2. Wrap with `python3 mk_minimal_bootimg.py bootshim.bin boot-shim.img`
3. Flash to `boot_b` (keep stock on `boot_a`):
   ```
   fastboot flash boot_b boot-shim.img
   fastboot set_active b
   fastboot reboot
   ```
4. Without UART we still see black screen — expected.
5. Next real goal: find framebuffer / add simple fill so something appears on screen.
