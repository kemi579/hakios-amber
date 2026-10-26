#!/bin/bash
# Pull MediaTek firmware needed for amber from a rooted phone
set -e
OUT=${1:-.}
mkdir -p "$OUT/fw-gpu" "$OUT/fw-wifi"

echo "[*] GPU (Mali Valhall)"
adb shell su -c "cat /vendor/firmware/valhall-1691526.wa" > "$OUT/fw-gpu/valhall-1691526.wa"

echo "[*] Connsys / Wi-Fi"
for f in \
  conninfra.cfg \
  wifi.cfg \
  soc3_0_ram_wifi_1a_1_hdr.bin \
  soc3_0_ram_bt_1a_1_hdr.bin \
  soc3_0_ram_mcu_1a_1_hdr.bin \
  soc3_0_ram_wmmcu_1a_1_hdr.bin \
  soc3_0_patch_wmmcu_1a_1_hdr.bin
do
  adb shell su -c "cat /vendor/firmware/$f" > "$OUT/fw-wifi/$f" 2>/dev/null || echo "  skip $f"
done

echo "[*] Done. Files in $OUT/fw-gpu and $OUT/fw-wifi"
ls -l "$OUT/fw-gpu" "$OUT/fw-wifi"
