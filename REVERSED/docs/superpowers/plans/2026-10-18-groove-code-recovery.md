# Groove code recovery plan — 2026-10-18

**Objective:** Replace missing/stubbed original in-image code with reviewed C and
make the rebuilt EXE behaviorally match `Game/groove.exe` on the intro, Esc skip,
menu rendering, and audio paths. Do not equate a Ghidra C export or a successful
link with equivalent behavior.

**Immutable evidence:** Original SHA-256
`151102050d79c0cc703d121e7755f7bb75f436d5822d31e72a43c31cc1adb9bc`;
Ghidra/Radare2 1,686-entry comparison; `Game/groove.exe.asm`; both Ghidra C
export sets. `build/rebuild_parity_audit.csv` is the address-level queue.
Preserve all existing uncommitted sources. Do not use REA.

## Recovery gates

1. **Inventory:** Run `tools/audit_rebuild_parity.py`; reconcile all 1,686
   entries and the five extra recovered source addresses. Record status changes
   by address, not by filename. The current 1,597 in-image code entries include
   74 absent from the EXE compile input, with 28 fallback stub symbols.
2. **Assembly-backed recovery:** For each excluded entry, inspect original
   instructions and callers. Recover parameters, calling convention, register
   inputs, data width, control flow, return value, and side effects. Use a
   recovered source file or a narrow documented patch. A compiler error alone
   is not evidence for a semantic replacement. Remove its stub only after the
   original body compiles in the EXE input.
3. **Subsystem batches:** Work in dependency order. First fix the menu timer
   `sub_417FA0` and its 32-bit timestamp. Then close the intro media/input path
   (`sub_41F0C0`, `sub_41F590`, `sub_41D2C0`, `sub_40F060`); menu text and 3D
   renderer (`sub_4060C0`, pixel conversion/rasterizer entries near `0x409290`,
   `0x40AD30`, `0x40AF10`, `0x40B750`, `sub_424BE0`, `sub_435D10`); audio/MIDI
   entries near `0x5458D0` and `0x549270`; then the remaining `0x55`–`0x56`
   runtime, CRT, and exception entries. The CSV remains authoritative for every
   address, including entries not named in this summary.
4. **Compile and link:** Regenerate C, compile every selected function, link the
   bulk EXE, regenerate the audit, and verify the staged EXE came from the
   current generated chunks. The static gate is zero unexplained in-image
   exclusions and zero in-image fallback stub symbols. Document deliberate CRT
   substitutions and exception-handler handling separately.
5. **Behavioral comparison:** Exercise the original and rebuilt EXE under the
   same data files and input sequence. Compare intro and Esc state transitions,
   menu call order, rendered draw batches/frame hashes, and audio-init results.
   Visible tests use the existing eight-second watchdog. A mismatch returns to
   its first differing function/data edge; no speculative visual patching.
6. **Parity report:** Keep export coverage, C compile/link coverage, reviewed
   instruction/path coverage, and observed behavior separate. Name every
   unresolved indirect call, data-layout assumption, and platform dependency.
   Exact original-source recovery cannot be proven from a binary.

## First implementation batch

- [x] Test that `sub_417FA0` uses the actual 32-bit `0x005839D0` timer and stores a
  pointer to the eight-byte `0x00583988` text buffer at `0x00571DE8`.
- [x] Compare the original `sub_417FA0` instructions with selected C; replace the
  `uRam` and `func_0x00418050` artifacts with their verified globals/function.
- [x] Regenerate, compile and link; require `sub_417FA0` in the EXE chunks with no
  corresponding stub. Refresh the audit and record the exact count change.

The focused tests pass, all 1,575 clean-subset functions compile, and the bulk
DLL/EXE link succeeds. `sub_417FA0` is in the EXE chunks. The 24-byte menu
record at `0x00571E30` now retains its original mode value `1`, pointer to
`0x00571DE8`, and callback `sub_417FA0` as relocatable C addresses. The 32-bit
timer at `0x005839D0` and eight-byte text buffer at `0x00583988` are defined
with their original widths. The staged EXE SHA-256 is
`64546f4b1ac7d2fdd7a87d0af1311934d8c7c8ffa2898b382cce301732fb6183`.
The audit now reports 73 in-image code entries excluded, down from 74; the 28
in-image link-stub symbols remain. No visible run has tested this timer repair.

The next intro-media target is `sub_41F0C0` (1,231 original bytes). Its caller
at `0x0041F5DA` pushes **three** arguments; Ghidra's raw declarator has two,
and the current patch only changes that declarator. The exported body also
contains uninitialized `unaff_EBX`/`unaff_ESI`/`unaff_EDI` COM pointers and a
call through `puRam00000000`, so compiling that pseudocode by suppressing the
artifact warning would be unsafe. Recover the caller/callee contract and COM
objects from the original instructions before including it. The caller's
`sub_43CB20`/`sub_43CB30` calls resolve through five-byte thunks to the
`sub_545270`/`sub_545030` bodies seen in Ghidra; that label difference is not
a verified mismatch.

**Review focus:** x86 stack/register contracts; BSS globals mis-sized by
Ghidra; text patches that change semantics; SEH bodies mistaken for gameplay
code; indirect calls that the address-level inventory cannot resolve; staged
EXE freshness. No visual claim follows from this first batch.
