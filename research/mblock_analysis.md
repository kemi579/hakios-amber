# mblock_info analysis (amber)

Raw dump obtained via root.

Conservative usable DRAM window for early bring-up:
  0x40000000 – 0xC0000000 (first 2 GiB)

Full 8 GiB starts at 0x40000000.
TEE and other reserved regions exist in the higher part of the map;
a proper parser of mblock_info is required before claiming the full range.

XNU payload region used by current HakiOS on Qualcomm:
  0xF0000000 size 0x04000000 (64 MiB) with magic "XNUP"

For amber we will need an equivalent reserved region once a BootShim exists.
