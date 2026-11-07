#!/usr/bin/env python3
"""
Put a bare-metal program in front of Android's kernel in a boot image (header v2).

  chainboot.py <android-boot.img> <program.bin> <out.img>

LK decompresses the kernel to 0x40080000 and enters it there.
The new kernel is gzip of: program.bin padded to CHAIN_OFFSET, then
Android's own (uncompressed) Image.

The program runs first, writes a magic, disables WDT, then moves the
Image down to 0x40080000 and starts it. Everything else (header fields,
cmdline, ramdisk, dtb) is copied from the Android image.

Adapted from oosexgang/hakios-mt6768 for Xiaomi 11T (amber / MT6893).
"""
import gzip
import hashlib
import struct
import sys

CHAIN_OFFSET = 0x40000
BOOT_PARTITION = 128 << 20   # 128 MiB typical on Xiaomi

def pad(b, n):
    return b + b'\0' * (-len(b) % n)

def main():
    if len(sys.argv) < 4:
        print(f"Usage: {sys.argv[0]} <stock-boot.img> <chain.bin> <out.img>")
        sys.exit(1)

    src, prog_path, out = sys.argv[1:4]
    d = open(src, 'rb').read()
    assert d[:8] == b'ANDROID!', 'not an Android boot image'

    ksize, _, rsize, _, ssize, _, _, page, hver = struct.unpack_from('<9I', d, 8)
    assert hver == 2, f'header v{hver}, expected 2'

    rdo_size = struct.unpack_from('<I', d, 1632)[0]
    dtb_size = struct.unpack_from('<I', d, 1648)[0]

    def pages(n):
        return (n + page - 1) // page * page

    off = page
    kernel = d[off:off + ksize]; off += pages(ksize)
    ramdisk = d[off:off + rsize]; off += pages(rsize)
    second = d[off:off + ssize]; off += pages(ssize)
    rdo = d[off:off + rdo_size]; off += pages(rdo_size)
    dtb = d[off:off + dtb_size]

    # Decompress if gzipped
    if kernel[:2] == b'\x1f\x8b':
        image = gzip.decompress(kernel)
    else:
        image = kernel

    assert image[0x38:0x3c] == b'ARM\x64', 'Android kernel is not an arm64 Image'

    prog = bytearray(open(prog_path, 'rb').read())
    assert prog[0x38:0x3c] == b'ARM\x64', 'program has no arm64 header'
    assert len(prog) <= CHAIN_OFFSET, f'program too large ({len(prog)} > {CHAIN_OFFSET})'

    # Fill header fields that the chain payload reads
    linux_image_size = struct.unpack_from('<Q', image, 0x10)[0]
    struct.pack_into('<Q', prog, 0x10, (CHAIN_OFFSET + linux_image_size + 0xfffff) & ~0xfffff)
    struct.pack_into('<Q', prog, 0x28, len(image))   # res2 = Android Image length

    blob = bytes(prog) + b'\0' * (CHAIN_OFFSET - len(prog)) + image
    new_kernel = gzip.compress(blob, 9, mtime=0)

    # Rebuild header
    hdr = bytearray(d[:page])
    struct.pack_into('<I', hdr, 8, len(new_kernel))

    # Update SHA1 of the pieces (Android bootimg v2 style)
    sha = hashlib.sha1()
    for part in (new_kernel, ramdisk, second, rdo, dtb):
        sha.update(part)
        sha.update(struct.pack('<I', len(part)))
    hdr[576:608] = pad(sha.digest(), 32)

    img = (bytes(hdr) +
           pad(new_kernel, page) +
           pad(ramdisk, page) +
           pad(second, page) +
           pad(rdo, page) +
           pad(dtb, page))

    if len(img) > BOOT_PARTITION:
        raise SystemExit(f'{out}: {len(img)} bytes > {BOOT_PARTITION} (boot partition)')

    open(out, 'wb').write(img)
    print(f'{out}: {len(img)} bytes')
    print(f'  program   {len(prog)} bytes')
    print(f'  Image     {len(image)} bytes')
    print(f'  kernel.gz {len(new_kernel)} bytes')

if __name__ == '__main__':
    main()
