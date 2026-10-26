# amber (Xiaomi 11T / MT6893)

## Confirmed hardware
- SoC: MediaTek MT6893 (Dimensity 1200)
- GIC: GICv3 at 0x0c000000 (GICD) / 0x0c040000 (GICR)
- UART: 0x11002000 and 0x11003000 (mediatek,mt6577-uart)
- RAM: 8 GiB starting at 0x40000000
- PSCI: arm,psci-1.0 via SMC
- GPU firmware: valhall-1691526.wa
- Wi-Fi: Connsys SOC3.0 / MT6635-family (proprietary)

## Status
- platform_amber.h skeleton created
- devices/amber layout matching HakiOS style
- Still missing: exact framebuffer address, full mblock layout details, bootloader chain
