# Firmware inventory for amber

## GPU (Mali-G77 / Valhall r32p1)
- `valhall-1691526.wa` (440 bytes) — already pulled

## Connsys / Wi-Fi + BT (SOC3.0 / MT6635 family)
- `soc3_0_ram_wifi_1a_1_hdr.bin` (296928 B)
- `soc3_0_ram_bt_1a_1_hdr.bin` (672600 B)
- `soc3_0_ram_mcu_1a_1_hdr.bin` (166384 B)
- `conninfra.cfg` (17 B)
- `wifi.cfg` (275 B)

Optional / variants still on device:
- soc3_0_ram_bt_1_1_hdr.bin
- soc3_0_ram_mcu_1_1_hdr.bin
- soc3_0_ram_mcu_e1_hdr.bin
- soc3_0_ram_wmmcu_1a_1_hdr.bin
- soc3_0_patch_wmmcu_1a_1_hdr.bin

These stay out of git (vendor binary). Place them under `devices/amber/fw-gpu/` and `devices/amber/fw-wifi/` after cloning the repo.
