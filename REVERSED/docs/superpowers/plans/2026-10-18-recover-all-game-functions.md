# Recover All Game Functions Implementation Plan

> **For agentic workers:** REQUIRED SUB-SKILL: Use superpowers:executing-plans to implement this plan task-by-task.

**Goal:** Include every recoverable in-image Groove function in the rebuilt executable and replace true game-code stubs with bodies justified by Ghidra exports and original x86 assembly.

**Architecture:** Treat Ghidra exports as the source for C bodies and `Game/groove.exe.asm` as the source for ABI, control flow, and data-layout checks. Keep compiler/runtime artifacts and imported OS/DirectX/Miles APIs classified separately from game functions. The bulk build must compile the complete generated function set before chunk filtering and linking, and the audit must distinguish compiled bodies, link stubs, imports, and non-game artifacts.

**Tech Stack:** Ghidra 12.1.4 exports, MSVC x86 compiler/linker, Python inventory/build tools, unittest, PE/parity audit.

**Spec:** User request in this chat: implement all missing functions and stubs.

## Global Constraints

- Preserve the user's existing uncommitted work.
- Do not use Reverse Engineer Everything; use Ghidra exports and the original assembly listing.
- Do not infer a function body from its name or a neighboring function; verify each candidate's address, ABI, and behavior.
- Keep imports and compiler-generated exception/runtime artifacts classified separately from in-image game logic.
- Do not claim binary or logical equivalence from compilation or symbol counts alone.

## Review Focus

- Functions omitted by `clean_subset.c` despite compiling in current generated C: verify the bulk build actually links those bodies.
- Recovery sources with overlapping aliases or shared global storage: verify exact address/width behavior and caller ABI.
- Functions still unresolved at link time: distinguish in-image body gaps from OS/DirectX/Miles imports and compiler helpers.
- Catch/unwind labels: preserve only real in-image code needed by the program; do not replace exception metadata with fake gameplay logic.
- Recovered functions with multiple Ghidra exports: prevent duplicate definitions and ensure the chosen source identity is audited.

### Task 1: Compile and include every generated function

**Files:**
- Modify: `REVERSED/harness/build_dlls.bat`
- Modify: `REVERSED/tools/test_bulk_build_regeneration.py`
- Generate: `REVERSED/src_generated/chunks/`, `REVERSED/build/dll_chunks/`, `REVERSED/build/exe_chunks/`

- [x] Add a failing regression test that requires the bulk build to run `compile_check.py --all`.
- [x] Confirm the test fails against the old clean-subset build command.
- [x] Change the bulk pipeline to compile all generated functions in bounded 20-function chunks.
- [x] Rebuild DLL and EXE, confirm no compile errors, and regenerate the current stub/audit inventory.

### Task 2: Remove remaining in-image function stubs

**Files:**
- Inspect/modify: `REVERSED/src_recovered/*.c`, `REVERSED/src_generated/bulk_patches.csv`, `REVERSED/tools/gen_link_stubs.py`, `REVERSED/tools/audit_rebuild_parity.py`
- Test: focused per-function ABI/body checks and current parity audit.

- [x] Rebuild after Task 1 and extract the authoritative current list of game-function link stubs.
- [x] For the 70 code-label symbols whose addresses exactly match generated function entries, verify the exact-address body and map them as aliases instead of no-op functions.
- [x] Add failing regression tests for exact-address alias selection and automatic placeholder pruning.
- [x] Classify the remaining label and CRT entries; the parity audit now places all 15 legacy CRT routines in explicit runtime replacements and reports no in-image code exclusions or stubs.
- [x] Compile recovered definitions and remove corresponding generated stubs only after the linker and symbol audit confirm a single real definition.
- [x] Repeat in small, subsystem-specific batches until no in-image game-function stub remains.

### Task 3: Resolve source bodies excluded for decompiler artifacts

**Files:**
- Modify: `REVERSED/src_recovered/*.c`, `REVERSED/src_generated/bulk_patches.csv`, `REVERSED/src_generated/type_overrides.csv`
- Test: focused compile and assembly-layout checks for each function/global repair.

- [x] Group current compile-review items by artifact (`in_EAX`, `unaff_*`, undeclared local, incorrect overlapping global, true compile failure); all 1,684 generated bodies compile, with no current compile failures.
- [ ] Recover register inputs and output conventions from call sites and assembly before editing bodies.
- [ ] Correct shared state layout in coordinated ranges rather than assigning incompatible scalar globals.
- [ ] Run each targeted test red, implement the minimal correction, then run it green and recompile all generated functions.

### Task 4: Close the implementation inventory and verify the build

**Files:**
- Modify: `REVERSED/tools/audit_rebuild_parity.py` and its tests if classifications are incomplete.
- Verify: generated source inventory, both bulk images, current link-stub CSV, parity audit, and watchdog trace.

- [x] Reconcile every original in-image code range against a compiled C body or an explicitly justified compiler/runtime artifact; the current audit reports zero in-image exclusions.
- [x] Confirm zero true in-image game-function stubs and no duplicate/undefined game symbols; the full link succeeds and the stub CSV is empty.
- [x] Run all relevant unit tests, a fresh all-function MSVC compile, full bulk link, parity audit, and `git diff --check`.
- [x] Perform an eight-second launch only after static and link checks pass; report graphics/runtime failures separately from code-coverage results.

## Current Evidence

- Before this plan, the audit listed 24 in-image game-function link stubs and 68 excluded in-image functions; some excluded items were already represented by recovered source files.
- A fresh `compile_check.py --all --chunk 20` compiled all 1,653 currently generated bodies with zero compiler errors and cleared `failed.txt`.
- The old build script ran `compile_check.py` without `--all`, so its chunk set omitted functions flagged for review even when the current bodies compiled.
- The bulk-build regression test now requires `--all`; its initial run failed against the old script and passes after the build command change.
- A prior runtime trace still shows DirectDraw `SetDisplayMode` returning `E_NOTIMPL`; this is a separate runtime blocker and not proof that recovered game bodies are incorrect.
- Historical linker inventory contained 101 code-label candidates. 70 exact-entry aliases were resolved; the remaining label and legacy CRT classifications are still open.
- Follow-up on 2026-10-18: recovered the x86 FS:[0] exception-chain mapping, the register-sensitive NLG notification thunk (`sub_5632D2`), and exact-layout `__local_unwind2`; `__global_unwind2` now uses a relocated continuation instead of the original image address. Removed stale `_LOCK`, `_UNLOCK`, and `ExceptionList` link placeholders. Restored `sub_567FCA` to the EXE startup after the diagnostic filter, so the original game exception handler remains active and chains other faults to diagnostics.
- Latest follow-up: restored the two large rasterizer call blocks from the original x86 stack contract. Both now pass the original five scalar arguments, three y-sorted vertex pointers, and the remapped flags word. The corrected source removed the final two C2198 errors.
- Latest full build compiled all 1,684 generated bodies with zero compiler errors and linked the rebuilt EXE and both DLLs. The link-stub CSV is empty; the parity audit reports zero in-image exclusions and zero in-image stubs, with 15 explicit legacy CRT runtime replacements. The staged EXE SHA-256 is `cf1716a84769cc5a45189b583075391caed39ff0e5a91950bc2dc578f9f09f0d` and source/generated/object/EXE timestamps are ordered.
- The full Python regression suite passes 69 tests. `git diff --check` reports no whitespace errors (only existing line-ending warnings).
- A watchdog launch was attempted after the successful build. The process exited before creating a visible window with code `0xE06D7363`, and no fresh `groove_trace.log` was produced, so runtime startup remains unresolved and the build is not claimed to work like the original.
- Follow-up on 2026-10-18: a scan of 69 return-only generated C bodies was checked against Radare2's original-byte decode. Twenty-seven one-byte `FUN_*` entries are literal `RET` bytes, and the five-byte adjacent wrappers checked are tail jumps to those `RET` entries; their C `return;` bodies preserve the observed behavior. The meaningful x87 cases were recovered from their actual instructions: `sub_5682F8` (swap/pop), `sub_568306` (pop and return x87 zero), `sub_568445`/`sub_5684CE` (paired per-thread control-word prepare/restore for the C-rebuilt caller), and `sub_56CFCA` (x87 exception/status probe with original 80-bit constants). `tools/test_x87_recovered_helpers.py` checks the x87 stack, control-word restoration, EAX preservation, and divide-by-zero status effect. The latest bulk build and all 63 Python tests pass. The parity audit still shows 0 link stubs, 14 intentionally excluded legacy CRT bodies, and staged EXE SHA-256 `c81c0b9d6dc46def59c5ac5caa2cf4b8e3860c71e9060c9ed11596b35fe734b1`. This does not close Tasks 2-4: remaining non-CRT function-boundary/source-body mismatches and runtime behavior still require review.
