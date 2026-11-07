# Minimal chainloader for amber (MT6893)

Proven MediaTek path from [hakios-mt6768](https://github.com/oosexgang/hakios-mt6768):

1. Small bare-metal program is placed **in front of** the stock Android kernel inside `boot.img`.
2. LK loads it as a normal arm64 Image at `0x40080000`.
3. The program disables WDT, writes a magic value, then jumps into the real Android kernel.
4. After Android boots you can verify the magic from userspace.

## Build

```bash
cd devices/amber/chain
make CROSS=aarch64-linux-gnu-     # or aarch64-none-elf-
```

Produces `chain.bin`.

## Pack against stock boot

```bash
python3 chainboot.py /path/to/stock_boot_a.img chain.bin boot-chain.img
```

## Flash (only after you confirm backups)

```bash
fastboot flash boot_b boot-chain.img
fastboot set_active b
fastboot reboot
```

Keep stock on `boot_a`. One slot stays native.

## Verify magic after Android boots

```bash
adb shell su -c "xxd -l 16 -s 0x1000 /dev/mem"   # or use busybox devmem
# expect: DE AD BE EF CA FE BA BE  (or the little-endian form)
```

If the magic is present → our code ran and control returned to Android successfully.
