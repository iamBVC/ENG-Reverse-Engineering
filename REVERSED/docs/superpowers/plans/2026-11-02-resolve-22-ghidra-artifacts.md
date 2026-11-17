# Resolve 22 Ghidra Function Artifacts Implementation Plan

> **For agentic workers:** REQUIRED SUB-SKILL: Use superpowers:executing-plans to implement this plan task-by-task. Steps use checkbox (`- [ ]`) syntax for tracking.

**Goal:** Replace unresolved Ghidra pseudo-register artifacts in the 22 flagged function entries with verified C or x86 recovery that preserves the original binary contracts.

**Architecture:** Re-decompile the targets from the original `Game/groove.exe`, then use callers, function ranges, and Radare2/Ghidra instruction listings to establish each ABI. Prefer corrected Ghidra signatures and boundaries when they express the behavior; use small MSVC x86 naked-assembly recoveries only for register, x87, split-frame, or EH contracts that ordinary C cannot express. Make the recovered source the generator’s authoritative body and keep a focused regression test per contract or tightly coupled group.

**Tech Stack:** Ghidra 12.1.4 headless, Radare2, MSVC x86 inline assembly, Python `unittest`, `make_bulk.py`, `build_dlls.bat`, `audit_rebuild_parity.py`.

**Spec:** User request in this chat (2026-11-02): fix all 22 flagged functions so the reconstructed C project behaves like original Groove.

## Global Constraints

- Target binary is the original 32-bit `Game/groove.exe`.
- Treat generated Ghidra C as evidence, not source truth; verify register and stack contracts against original instructions and call sites.
- Preserve original observable behavior and calling convention; do not replace unresolved behavior with zero/no-op stubs.
- Do not claim full game equivalence from compile or function-coverage counts alone.
- Do not launch the rebuilt GUI during this recovery pass; it can black-screen the desktop and needs the user's visible test loop.

## Review Focus

- x87 stack depth and return value: preserve ST(0)/ST(1) effects and control/status words for math helpers.
- Integer return register fragments: preserve AH/AL/ECX/CL/DL side effects at caller boundaries.
- Split or overlapping function entries: distinguish true entry prologues from shared epilogues and EH funclets.
- SEH/EH stack chain: preserve FS:[0], EBP frame layout, and continuation behavior.
- Regeneration stability: ensure each recovery survives `make_bulk.py` and reaches the EXE's compile/link inputs.

### Task 1: Establish current target inventory and Ghidra baseline

**Files:**
- Inspect: `build/ghidra_register_artifact_targets.txt`, `build/ghidra_artifact_export_20261102/*.c`, `tools/make_bulk.py`, `tools/audit_rebuild_parity.py`.
- Test: existing coverage/parity tests.

- [x] Confirm all 22 target entries still exist and fresh Ghidra exports each one. The exported target list has 23 addresses because `sub_413CC0` is an interior fragment merged into `sub_413C40`.
- [x] Record the unresolved pseudo-registers, caller references, and relevant original instruction ranges for each remaining target.
- [x] Group entries by ABI: AH/AL/ECX/DL results (`sub_409290`, `sub_40AD30`, `sub_563E08`); x87/FPU (`sub_40AF10`, `sub_40B750`, `sub_563382`, `sub_56814E`, `sub_5683D0`, `sub_568519`, `sub_56B376`, `sub_56B57C`, `sub_56B62E`, `sub_56B834`); split frame/EH (`sub_413CC0`, `sub_567B34`, `sub_56D0A0`, `sub_56D0FA`, `sub_56D188`, `sub_56D1E1`, `sub_56D23E`, `sub_56D2CC`, `sub_56D326`).

### Task 2: Recover register-result and x87 helper groups

**Files:**
- Create or modify: `src_recovered/sub_<address>.c` and only required generator/type patches.
- Test: focused `tools/test_*recovery.py` files per ABI group.

- [x] For each register-result target, derive output and preserved registers from call sites and original instructions; compare the emitted register behavior statically.
- [x] For `sub_40AF10` and `sub_40B750`, recover the x87 return predicate and verify stack effects against the original instruction sequence. Dynamic numeric edge-case tests were not run.
- [x] For `sub_563382`, recover each input/output register and x87 stack effect from callers and original instructions before implementing; do not infer from the decompiler's fake locals.
- [x] For `sub_56814E`, `sub_5683D0`, and `sub_568519`, preserve the original x87/control/status-word contracts and inspect emitted x87 sequences. Dynamic exceptional-value tests were not run.
- [x] For `sub_56B376`, `sub_56B57C`, `sub_56B62E`, and `sub_56B834`, recover the bridge/helper ABI and verify the emitted instruction sequence, including the FPREM/FPREM1 differences.

### Task 3: Recover split-frame and exception-handler entries

**Files:**
- Create or modify: `src_recovered/sub_<address>.c`, Ghidra export/boundary scripts only where evidence supports a corrected boundary.
- Test: focused frame/EH regression tests.

- [x] Resolve whether `sub_413CC0` is a valid function entry or an interior continuation by comparing Ghidra function ranges with original control-flow and call sites; merge it into the recovered parent.
- [x] Recover `sub_567B34`'s caller-established EBP/EBX/ESI/EDI state and its termination/handler paths.
- [x] Recover each targeted `sub_56D*` funclet's stack frame and FS:[0] effects from its parent EH function; preserve only boundaries supported by original control flow.

### Task 4: Integrate, regenerate, and verify all 22

**Files:**
- Modify: `src_recovered/*`, focused regression tests, and generator metadata required for durable overrides.
- Generated by tools: `src_generated/bulk_all.c`, `clean_subset.c`, build chunk sources, parity audit reports.

- [x] Regenerate through `tools/make_bulk.py` and verify no target's executable body is still classified unresolved.
- [ ] Run the complete unittest suite. Not run: the active instruction for this task prohibits running tests unless the user asks.
- [x] Run the full 32-bit bulk build, `audit_rebuild_parity.py`, and `git diff --check`.
- [x] Verify every recovery is present in the EXE compile inputs and no new placeholder stub was generated.
- [x] Report behavior that cannot be proven statically as unverified; no GUI runtime validation was performed and full game equivalence is not claimed.
