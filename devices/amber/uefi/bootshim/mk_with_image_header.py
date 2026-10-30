#!/usr/bin/env python3
"""Prepend a proper ARM64 Linux Image header to a raw binary.

Many MediaTek LKs expect this 64-byte header and jump to text_offset.
See Documentation/arm64/booting.txt
"""

import struct
import sys

def make(payload_path: str, out_path: str, text_offset: int = 0x40080000):
    with open(payload_path, "rb") as f:
        payload = f.read()

    header = bytearray(64)

    # code0 / code1 — simple branch to payload (offset 64)
    # b #64  → opcode 0x14000010
    struct.pack_into("<I", header, 0x00, 0x14000010)
    struct.pack_into("<I", header, 0x04, 0)

    struct.pack_into("<Q", header, 0x08, text_offset)   # text_offset
    struct.pack_into("<Q", header, 0x10, len(payload))  # image_size
    struct.pack_into("<Q", header, 0x18, 0)             # flags
    struct.pack_into("<Q", header, 0x20, 0)             # res2
    struct.pack_into("<Q", header, 0x28, 0)             # res3
    struct.pack_into("<Q", header, 0x30, 0)             # res4
    struct.pack_into("<I", header, 0x38, 0x644D5241)    # magic "ARM\x64"
    struct.pack_into("<I", header, 0x3c, 0)             # res5

    with open(out_path, "wb") as f:
        f.write(header + payload)

    print(f"[+] {out_path}  size={64 + len(payload)}  text_offset=0x{text_offset:x}")

if __name__ == "__main__":
    if len(sys.argv) < 3:
        print(f"Usage: {sys.argv[0]} bootshim.bin kernel_with_header.bin")
        sys.exit(1)
    make(sys.argv[1], sys.argv[2])
