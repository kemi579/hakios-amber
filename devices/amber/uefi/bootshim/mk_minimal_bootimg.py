#!/usr/bin/env python3
"""Create a minimal Android boot.img containing our BootShim as kernel."""

import struct, sys

BOOT_MAGIC = b"ANDROID!"
PAGE_SIZE  = 2048
KERNEL_ADDR = 0x40080000

def pad(data, pagesize):
    rem = len(data) % pagesize
    if rem:
        data += b"\x00" * (pagesize - rem)
    return data

def make_bootimg(kernel_path, out_path, pagesize=PAGE_SIZE, kernel_addr=KERNEL_ADDR):
    with open(kernel_path, "rb") as f:
        kernel = f.read()
    kernel_size = len(kernel)

    hdr = bytearray(1632)
    struct.pack_into("<8s", hdr, 0, BOOT_MAGIC)
    struct.pack_into("<I", hdr, 8,  kernel_size)
    struct.pack_into("<I", hdr, 12, kernel_addr)
    struct.pack_into("<I", hdr, 16, 0)
    struct.pack_into("<I", hdr, 20, 0)
    struct.pack_into("<I", hdr, 24, 0)
    struct.pack_into("<I", hdr, 28, 0)
    struct.pack_into("<I", hdr, 32, 0)
    struct.pack_into("<I", hdr, 36, pagesize)
    struct.pack_into("<I", hdr, 40, 0)
    name = b"hakios-shim\x00"
    hdr[48:48+len(name)] = name
    cmdline = b"console=ttyS0\x00"
    hdr[64:64+len(cmdline)] = cmdline

    img = pad(bytes(hdr), pagesize) + pad(kernel, pagesize)
    with open(out_path, "wb") as f:
        f.write(img)
    print(f"Wrote {out_path} ({len(img)} bytes)")
    print(f"  kernel size  = {kernel_size}")
    print(f"  kernel addr  = 0x{kernel_addr:08x}")

if __name__ == "__main__":
    if len(sys.argv) < 3:
        print(f"Usage: {sys.argv[0]} bootshim.bin boot-shim.img")
        sys.exit(1)
    make_bootimg(sys.argv[1], sys.argv[2])
