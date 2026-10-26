# UEFI / Bootloader candidates for MT6893 (amber)

## 1. edk2-mtk (linux-mediatek/edk2-mtk)
- Status: archived 2025-10-04
- Supported: MT6765, MT6789, MT8183
- No MT6893
- Value: BootShim design, MediaTek driver patterns

## 2. Upstream U-Boot + CONFIG_EFI_LOADER
- MediaTek support exists but focused on router/SBC chips
- No public ready-made port for Dimensity 1200

## 3. uniLoader
- Contains CONFIG_INFINIX_X6710 that depends on MT6893

## 4. Direct path via stock LK
- Preloader → LK → Android
- Possible to chain-load from unlocked fastboot

## Recommended next step
Implement platform_amber in xnuloader using the confirmed GIC/UART addresses.
Then explore minimal BootShim or U-Boot EFI_LOADER adaptation.
