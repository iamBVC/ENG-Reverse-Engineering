# Groove Export Build Recovery Plan

> **For agentic workers:** REQUIRED SUB-SKILL: Use superpowers:executing-plans to implement this plan task-by-task. Steps use checkbox (`- [ ]`) syntax for tracking.

**Goal:** Recover the seven failed routines in `Game/groove.exe.c` and determine whether that single source file can compile as a separate EXE.

**Architecture:** Use the original `Game/groove.exe` and available Ghidra/assembly exports as evidence for each failed routine. Keep recovered code in the requested single translation unit, preserve the original binary, and avoid placeholder implementations that hide missing behavior.

**Tech Stack:** MSVC x86, Hex-Rays C export, Ghidra exports, original PE binary.

**Spec:** User request in this chat: fix the seven functions marked as decompilation failures and try compiling `Game/groove.exe.c`.

## Global Constraints

- Do not overwrite `Game/groove.exe`.
- Compile only `Game/groove.exe.c` as the project translation unit; `defs.h` is its included compatibility header.
- Preserve function behavior using binary/export evidence; do not replace missing bodies with no-op stubs.
- Report compilation failures and unverified behavior precisely.

## Review Focus

- Address-to-function mapping: verify each failed address against the binary and function boundaries before editing.
- Function ABI: preserve x86 calling convention and register argument behavior when translating Ghidra output.
- Renderer routines: ensure the large routines at `0x447770` and `0x4CB870` are recovered from authoritative exports, not guessed.
- Missing data: avoid arbitrary global sizes or zero values when data can be recovered from the PE.
- Build scope: verify MSVC compiles the original `.c` translation unit and writes only a separate output.

---

### Task 1: Map the seven failures

**Files:** Read `Game/groove.exe.c`, `Game/groove.exe.asm`, and available `REVERSED` Ghidra exports.

- [ ] Identify the exact start/end address and symbol for each of the seven failed function bodies.
- [ ] Record whether an authoritative recovered body already exists and whether its ABI/types match the export.
- [ ] Reproduce the direct single-file compiler failure and preserve its diagnostics.

### Task 2: Recover functions and data

**Files:** Modify `Game/groove.exe.c`; use `Game/defs.h` only for verified compiler compatibility definitions.

- [ ] Replace each failed body only from verified original-binary or Ghidra evidence.
- [ ] Restore omitted data constants from the original PE where the symbol address and extent are known.
- [ ] Correct type/calling-convention declarations only when confirmed by call sites or binary metadata.

### Task 3: Compile the single translation unit

**Files:** `Game/build/groove_direct.exe` and `Game/build/cl_direct_exe.log`.

- [ ] Compile `Game/groove.exe.c` directly with MSVC x86 and output to the build directory.
- [ ] If compilation reaches linking, resolve only evidenced system/runtime dependencies; do not substitute another C source file.
- [ ] Confirm the output EXE exists and report remaining behavior checks separately.
