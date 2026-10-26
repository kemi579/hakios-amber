# Porting Plan: HakiOS → amber (MT6893)

## Honest realism assessment (2026-10-26)

**Overall difficulty: High.**  
This is the first public attempt at a non-Qualcomm port. No ready UEFI, no Panfrost G77, proprietary Wi-Fi stack.  
Feasible as a multi-week/month R&D effort if we accept softpipe first and a minimal BootShim/U-Boot path.

### What transfers almost as-is
- XNU core + most BSD layer (ARM64)
- iOS 16.5 userspace (launchd → SpringBoard)
- APFS image build & ramdisk loading logic
- QEMU virt path for development without phone

### What must be written / heavily adapted
1. **Boot path** — no Mu-Silicium equivalent. Need minimal UEFI or direct handoff from LK/fastboot.
2. **platform_amber** for xnuloader (GIC/UART/cores) — addresses already extracted.
3. **GPU** — Panfrost has no G77; start with softpipe, later reverse/port Valhall support.
4. **Wi-Fi** — completely different (Connsys SOC3.0 / MT6635 vs ath11k). New bridge required.
5. **Display / touch / UFS / audio / haptic** — all MediaTek-specific drivers instead of qcom_*.

## Concrete next steps (in order)

### Phase 0 — Done
- [x] Confirm codename amber, MT6893
- [x] Extract live GIC, UART, memory, PSCI via root
- [x] Create platform_amber.h
- [x] Create GitHub repo kemi579/hakios-amber

### Phase 1 — Platform skeleton (now)
1. Write full `struct platform platform_amber` matching current xnuloader ABI.
2. Locate current xnuloader source (or reverse from prebuilt/loader.efi + docs).
3. Document exact BootShim / mkxnuimg requirements for a non-Qualcomm path.
4. Pull more firmware (GPU wa, full Connsys set) into the repo structure.

### Phase 2 — Minimal boot
- Option A: Adapt U-Boot EFI_LOADER for MT6893 (hard but clean).
- Option B: Thin BootShim that provides only GetMemoryMap/ExitBootServices + GIC init, then jumps to xnuloader.efi.
- Option C: Direct load from custom LK payload if fastboot boot allows arbitrary images.

### Phase 3 — Bring-up order on hardware
1. UART console from xnuloader
2. Memory map + ExitBootServices
3. XNU early boot (no drivers)
4. Framebuffer / softpipe
5. Basic input
6. Later: storage, Wi-Fi, GPU acceleration

## Risks
- No public MT6893 UEFI → longest pole.
- Mali-G77 unsupported in Panfrost → softpipe only for months.
- MediaTek Wi-Fi is closed; may stay non-functional for a long time.
- SELinux / verified boot quirks on the specific HyperOS build.
