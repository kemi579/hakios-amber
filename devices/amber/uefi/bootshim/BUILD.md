# Building BootShim for amber

## Requirements
- aarch64-none-elf-gcc (or aarch64-linux-gnu-gcc)
- make, binutils

### Quick install (Ubuntu / WSL / Debian)
```bash
sudo apt update
sudo apt install -y gcc-aarch64-linux-gnu binutils-aarch64-linux-gnu make
```

Then in the bootshim directory:
```bash
make CROSS=aarch64-linux-gnu-
```

### Alternative (Arm GNU Toolchain)
Download from developer.arm.com, put bin/ in PATH, then:
```bash
make CROSS=aarch64-none-elf-
```

## Output
- bootshim.elf
- bootshim.bin

## Next
```bash
python3 mk_minimal_bootimg.py bootshim.bin boot-shim.img
fastboot boot boot-shim.img
```
