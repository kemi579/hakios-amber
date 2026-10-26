# How to get the BootShim onto amber

## Current constraints
- Stock boot chain: Preloader → LK → Android
- Bootloader is unlocked
- `fastboot boot` may or may not accept arbitrary images
- We do not have a working MediaTek UEFI yet

## Possible load paths (ordered by realism)

### 1. fastboot boot of a custom Android boot.img
- Build a minimal boot.img whose kernel is our bootshim.bin
- `fastboot boot boot-shim.img`
- Requires knowing the exact expected header / load address for this LK

### 2. Custom recovery / TWRP chain-load
### 3. Temporary LK patch (higher risk)
### 4. Full U-Boot / EDK2 port (longer term)

## Immediate next experiment
1. Cross-compile bootshim.bin
2. Collect fastboot getvar all + try loading a test image
3. Inspect stock boot.img header of amber

## Known addresses
- BootShim linked at 0x40080000
- UART 0x11002000
- GICD 0x0c000000
