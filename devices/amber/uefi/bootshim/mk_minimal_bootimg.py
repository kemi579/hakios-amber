#!/usr/bin/env python3
"""Create a minimal Android boot.img (header version 2) for Xiaomi 11T (agate/amber).

Uses the real values extracted from stock boot_a:
  kernel_addr  = 0x40080000
  page_size    = 2048
  header_ver   = 2
  tags_addr    = 0x47c80000
  ramdisk_addr = 0x51100000
  cmdline      = bootopt=64S3,32N2,64N2 buildvariant=user
"""

import struct
import sys

PAGE_SIZE       = 2048
KERNEL_ADDR     = 0x40080000
RAMDISK_ADDR    = 0x51100000
TAGS_ADDR       = 0x47c80000
HEADER_VERSION  = 2
OS_VERSION      = 0x18000197          # from stock
CMDLINE         = b"bootopt=64S3,32N2,64N2 buildvariant=user"

def pad(data: bytes, pagesize: int) -> bytes:
    rem = len(data) % pagesize
    if rem:
        data += b"\x00" * (pagesize - rem)
    return data

def make_bootimg(kernel_path: str, out_path: str):
    with open(kernel_path, "rb") as f:
        kernel = f.read()
    kernel_size = len(kernel)

    # Header layout for version 2 (see system/tools/mkbootimg/include/bootimg/bootimg.h)
    # size of the fixed part up to and including header_size is 0x650 (1648),
    # then dtb_size (4) + dtb_addr (8) = 1660 bytes total before padding.
    hdr = bytearray(1660)

    struct.pack_into("<8s", hdr, 0x00, b"ANDROID!")
    struct.pack_into("<I",  hdr, 0x08, kernel_size)       # kernel_size
    struct.pack_into("<I",  hdr, 0x0c, KERNEL_ADDR)       # kernel_addr
    struct.pack_into("<I",  hdr, 0x10, 0)                 # ramdisk_size
    struct.pack_into("<I",  hdr, 0x14, RAMDISK_ADDR)      # ramdisk_addr
    struct.pack_into("<I",  hdr, 0x18, 0)                 # second_size
    struct.pack_into("<I",  hdr, 0x1c, 0)                 # second_addr
    struct.pack_into("<I",  hdr, 0x20, TAGS_ADDR)         # tags_addr
    struct.pack_into("<I",  hdr, 0x24, PAGE_SIZE)         # page_size
    struct.pack_into("<I",  hdr, 0x28, HEADER_VERSION)    # header_version
    struct.pack_into("<I",  hdr, 0x2c, OS_VERSION)        # os_version

    # name[16] stays zero
    # cmdline[512]
    cmdline = CMDLINE[:511] + b"\x00"
    hdr[0x40:0x40 + len(cmdline)] = cmdline

    # extra_cmdline[1024] stays zero (offset 0x240)

    # recovery_dtbo_size / recovery_dtbo_offset / header_size (v1 fields)
    struct.pack_into("<I",  hdr, 0x640, 0)                # recovery_dtbo_size
    struct.pack_into("<Q",  hdr, 0x644, 0)                # recovery_dtbo_offset
    struct.pack_into("<I",  hdr, 0x64c, 1660)             # header_size

    # v2 fields
    struct.pack_into("<I",  hdr, 0x650, 0)                # dtb_size
    struct.pack_into("<Q",  hdr, 0x654, 0)                # dtb_addr

    img = pad(bytes(hdr), PAGE_SIZE) + pad(kernel, PAGE_SIZE)

    with open(out_path, "wb") as f:
        f.write(img)

    print(f"[+] Wrote {out_path}")
    print(f"    kernel size  = {kernel_size} (0x{kernel_size:x})")
    print(f"    kernel addr  = 0x{KERNEL_ADDR:08x}")
    print(f"    header ver   = {HEADER_VERSION}")
    print(f"    total size   = {len(img)}")

if __name__ == "__main__":
    if len(sys.argv) < 3:
        print(f"Usage: {sys.argv[0]} <kernel.bin> <boot-shim.img>")
        sys.exit(1)
    make_bootimg(sys.argv[1], sys.argv[2])
