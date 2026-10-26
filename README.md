# hakios-amber

Work-in-progress port of **HakiOS** (XNU + iOS 16.5 userspace) to **Xiaomi 11T** (codename `amber`, MediaTek Dimensity 1200 / MT6893).

## Current status (2026-10-26)

- Live hardware addresses extracted (GIC, UART, memory, PSCI)
- `platform_amber.h` skeleton ready
- Root (Kitsune Magisk) available on the device
- Research on UEFI / U-Boot path ongoing

## Key hardware

| Component | Value |
|-----------|-------|
| GICD | 0x0c000000 |
| GICR | 0x0c040000 |
| UART0 | 0x11002000 |
| UART1 | 0x11003000 |
| RAM | 0x40000000 (8 GiB) |
| GPU | Mali-G77 MC9 (valhall r32p1) |
| Wi-Fi | MediaTek Connsys SOC3.0 / MT6635 |

## Upstream

Based on https://github.com/oosexgang/hackios-xnu-kernel and https://github.com/oosexgang/hackios-xnu-userland

## License

Same as upstream HakiOS (APSL 2.0 / MIT where applicable).
