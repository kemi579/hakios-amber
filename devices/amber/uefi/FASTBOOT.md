# Fastboot status of amber (2026-10-26)

| Variable | Value |
|----------|-------|
| product | amber |
| current-slot | a |
| version-bootloader | agate-f012dc01b-... |
| unlocked | **yes** |
| is-userspace | no |
| max-download-size | 0x10000000 (256 MiB) |

## Conclusion
- Bootloader unlocked → `fastboot boot` should be possible.
- 256 MiB is more than enough for BootShim + later payload.
- Same model as HakiOS: load only into RAM, reboot returns to Android.

## Next experiment
1. Cross-compile bootshim.bin
2. Wrap it into a minimal Android boot.img
3. `fastboot boot boot-shim.img`
4. Confirm it returns to Android on reboot
