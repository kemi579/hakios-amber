# Device: Xiaomi 11T (amber)

MediaTek Dimensity 1200 (MT6893), Mali-G77 MC9.

This is the first non-Qualcomm target for HakiOS. Everything that is phone-specific lives here.

## Status (2026-10-26)

- Live hardware addresses extracted (GIC, UART, memory, PSCI)
- Root available (Kitsune Magisk)
- No UEFI yet — Mu-Silicium path is Qualcomm-only
- GPU firmware known: valhall-1691526.wa
- Wi-Fi: Connsys SOC3.0 / MT6635-family

## Layout

| Path | Purpose |
|------|---------|
| `platform_amber.h` / `.c` | Addresses for future loader |
| `pull-firmware.sh` | Pull GPU + Connsys firmware from phone |
| `uefi/` | Future minimal BootShim / U-Boot EFI work |
| `prebuilt/` | Built images (empty for now) |
| `fw-gpu/`, `fw-wifi/` | Vendor firmware (gitignored) |

## Key addresses

- GICD  0x0c000000
- GICR  0x0c040000
- UART0 0x11002000
- UART1 0x11003000
- RAM   0x40000000 (8 GiB)
- PSCI  arm,psci-1.0 (SMC)

## Next

1. Complete platform description matching current loader ABI
2. Design minimal BootShim that can load xnuloader.efi
3. Softpipe framebuffer path once early boot works
