# HakiOS → Xiaomi 11T (amber / MT6893) — Progress Log

**Date started:** 2026-10-26  
**Device:** Xiaomi 11T (amber), MediaTek Dimensity 1200 (MT6893), Mali-G77 MC9  
**Android:** 14 (UP1A.231005.007 / V816.0.14.0.UKWIDXM), kernel 4.19.191-gfbbcacfb8b1f, slot _a  
**Root:** Kitsune Magisk SuperUser (confirmed working)

## Confirmed facts (from real device + config.gz)

- codename: **amber**
- platform: **mt6893**
- `/proc/config.gz` readable
- **CONFIG_KEXEC is not set**
- **CONFIG_MTK_GPU_VERSION="mali valhall r32p1"**
- **CONFIG_MTK_COMBO_WIFI=y**
- **CONFIG_DM_VERITY=y** (AVB variants disabled)
- **CONFIG_MICROTRUST_TEE_SUPPORT=y**

## Hardware addresses (extracted via root 2026-10-26)

### GIC (arm,gic-v3)
- GICD: 0x0c000000 size 0x40000
- GICR: 0x0c040000 size 0x200000
- #redistributor-regions = 1
- #interrupt-cells = 3
- #address-cells = 2
- #size-cells = 2

### UART
- serial@11002000 : mediatek,mt6577-uart , reg 0x11002000 / 0x1000
- serial@11003000 : mediatek,mt6577-uart , reg 0x11003000 / 0x1000

### Memory
- base 0x40000000 , size 0x200000000 (8 GiB)
- mblock_info present (full dump saved)

### PSCI
- arm,psci-1.0 via SMC

### Firmware
- GPU: /vendor/firmware/valhall-1691526.wa (440 bytes)
- Wi-Fi/Connsys SOC3.0: soc3_0_ram_wifi_1a_1_hdr.bin + others, conninfra.cfg

## Status
- platform_amber.h skeleton created
- Live DT fully readable with root
- HakiOS upstream structure changed (devices/ layout, no old common/new-device.sh)
- xnuloader remains platform-agnostic

## Open questions
- Exact framebuffer / display pipeline addresses
- Full usable memory map after TEE / reserved regions
- Minimal UEFI / BootShim path for MT6893
- Panfrost G77 support (still missing)
