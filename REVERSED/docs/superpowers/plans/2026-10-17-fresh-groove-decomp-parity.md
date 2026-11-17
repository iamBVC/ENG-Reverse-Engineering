# Fresh Groove Decompilation and Source-Parity Plan

> **For agentic workers:** Use the plan task by task. Every original in-image function must receive a recorded status; do not count an empty body, generated stub, or unresolved function as recovered C.

**Goal:** Produce a fresh Ghidra pseudocode export for every function in the original `Game/groove.exe`, compare that inventory one-to-one against all existing C sources, and recover each missing or mismatched in-image function until the coverage ledger has no unexplained gaps.

**Architecture:** Import the immutable original binary into a new Ghidra project, export one pseudocode artifact and one status row per discovered function, and preserve the input hash and Ghidra version. A deterministic audit script compares the fresh inventory with source definitions across `REVERSED/src`, `src_recovered`, `src_generated`, and the harness; discrepancies become an ordered repair queue with explicit statuses for true externals, thunks, artifacts, stubs, and translated bodies.

**Tech Stack:** REA CLI 6.4.0, Ghidra 12.1.4 headless, JDK 26.0.1, Python, MSVC build and existing C regression tests.

**Spec:** User request in the current conversation; original artifact `Game/groove.exe`; working reconstruction under `REVERSED/`.

## Global Constraints

- Never modify `Game/groove.exe`, `Game/groove.exe.asm`, or the existing Ghidra projects during fresh analysis.
- Store new analysis output and generated artifacts under `REVERSED/`.
- Preserve the exact binary SHA-256, function entry address, function name, body range, Ghidra decompilation status, and raw pseudocode for every exported function.
- Treat machine pseudocode as a decompiler observation, not recovered original source; record unresolved or unsupported functions explicitly.
- Keep existing uncommitted user and reconstruction changes intact.

## Review Focus

- **Coverage denominator drift:** compare fresh function entries to the prior inventory and explain additions/removals before judging source coverage.
- **Thunks and import boundaries:** classify by body and target; do not mislabel external library implementation as a missing game function.
- **Generated stubs and recovered overrides:** distinguish compiled fallback stubs from implemented C bodies and allow one address/name to map to multiple source locations.
- **Large or failed decompilations:** keep one manifest row even if pseudocode generation times out or fails, with diagnostics and retry status.
- **Non-function executable regions and embedded data:** report them separately; a complete function ledger does not prove every executable byte has been assigned a function.

### Task 1: Fresh original-binary analysis

**Files:**
- Create: `REVERSED/build/fresh_ghidra_project/` (private Ghidra project)
- Create: `REVERSED/decompiled_fresh/` (pseudocode and manifest)
- Target: `Game/groove.exe`

- [x] Record SHA-256, PE identity, and existing analysis/source counts.
- [x] Run REA against the original binary with the Ghidra provider and retain the complete overview Evidence.
- [x] Import the same immutable binary into a new headless Ghidra project and wait for analysis completion.
- [x] Export every function body, including failed-decompile rows, into address-keyed C pseudocode and a CSV manifest.
- [x] Verify the input hash remains unchanged and reconcile the fresh function count with REA and PE/assembly inventories.

### Task 2: Deterministic source-coverage audit

**Files:**
- Create: `REVERSED/tools/audit_function_coverage.py`
- Create: `REVERSED/tools/test_audit_function_coverage.py`
- Create: `REVERSED/decompiled_fresh/source_coverage.csv`
- Inputs: fresh Ghidra manifest; `REVERSED/functions.csv`; C files under `src`, `src_recovered`, `src_generated`, and `harness`.

- [x] Add synthetic tests for recovered definitions, generated definitions, duplicate definitions, stubs, missing bodies, thunks, and excluded imports.
- [x] Run the tests and verify the source auditor reports each expected category.
- [x] Implement the audit so each fresh in-image entry has exactly one coverage row and all source definitions are retained as candidate matches.
- [x] Run it across the project and summarize complete bodies, recovered overrides, generated stubs, duplicates, missing functions, and non-game boundaries.

### Task 3: Function-by-function mismatch recovery

**Files:** exact source and tests selected by each ledger finding; update `REVERSED/decompiled_fresh/source_coverage.csv` after each batch.

- [x] Select a small, dependency-coherent batch of missing functions from the ledger (three CRT timer initializers).
- [x] Compare fresh instruction listings, helper prototype, timer objects, and startup call table for each wrapper.
- [x] Add and pass a focused regression test for the three object-address/argument pairs.
- [x] Recover the wrapper bodies and seven-DWORD storage for the previously undeclared timer object; regenerate the bulk source and CRT call table.
- [x] Regenerate the source, compile all 1,507 clean-subset functions, link the full bulk executable, and pass the initializer, timer-object, and coverage-auditor tests; refresh the address coverage ledger.
- [x] Promote both timed-out renderer bodies from the existing REA fallback, correct six pointer-valued switch cases using their integer tag values, remove their link stubs, and link the bulk executable.
- [ ] Reconstruct the renderer helper call arguments from the original assembly; the fallback pseudocode omits nine pushed values at the two large functions' final internal calls, so current compilation/linking is not semantic validation.

### Task 4: Whole-project parity gate

**Files:** `REVERSED/decompiled_fresh/source_coverage.csv`, `REVERSED/README.md`, build/test outputs.

- [ ] Require every in-image function to be implemented, explicitly classified as a compiler artifact/thunk, or documented with a concrete unresolved blocker.
- [ ] Require no unexplained duplicate ownership, link stub, or missing function in the final ledger.
- [ ] Run the full compile/link and relevant regression suite; report code-level parity separately from byte-for-byte executable identity.
- [ ] Publish final denominator, completed count, exceptions, and remaining blockers without claiming equivalence that was not tested.
