# Groove Inventory Reconciliation and Build Validation Plan

> **For agentic workers:** Use the native inline execution workflow for this existing task. Track each verified step with the checkboxes below.

**Goal:** Resolve the Ghidra/Radare2 function-inventory discrepancies, close any source-export gaps, and then run a reproducible compile/link check of the reconstructed C project.

**Architecture:** Treat the fixed Ghidra inventory and reference export as the candidate baseline, and use Radare2 plus PE bytes to independently validate starts, extents, control-flow references, and pointer tables. Keep function-entry classification separate from exported-source presence and from runtime behavior; after inventory closure, use the existing build/check harness without launching the game.

**Tech Stack:** Ghidra 12.1.4; Radare2 PE32 analysis; PowerShell/Python audit scripts; existing MSVC x86 `REVERSED\build.bat` and `check.bat`.

**Spec:** User request in this conversation; current evidence in `REVERSED\docs\radare2_ghidra_candidate_triage_20261017.md` and project constraints/status in `REVERSED\README.md`.

## Global Constraints

- Preserve all existing tracked and untracked user changes; scope edits to evidence and verified gaps.
- Do not use REA or launch the game during this static reconciliation.
- Do not equate an exported C file with a valid standalone function or correct behavior.
- Label every discrepancy as verified function start, contained/boundary entry, metadata/data reference, tool-analysis gap, or unresolved; retain evidence for unresolved items.
- Run the project compile/link check only after the inventory/source reconciliation has no unexplained export gaps; report compiler/toolchain limits and exact results.

## Review Focus

- Ghidra and Radare2 disagree on a start but one entry lies inside another function: trace instructions and control-flow boundaries before classifying it.
- Pointer words resemble a table but have no direct xref: inspect values, source section, and code consumers; keep runtime use unresolved if indirect/computed access is possible.
- Ghidra's `body_bytes`, Radare2 `realsz`, and Radare2 linear `size` differ: compare decoded instruction sets and branch destinations rather than treating those sizes as interchangeable.
- Candidate source exists only in supplemental output or is duplicated under a different filename: normalize by address and check generated/source roles before reporting a gap.
- Build succeeds while sources remain incomplete or stubs remain linked: treat compile/link as a buildability result, not behavioral equivalence.

---

### Task 1: Freeze and reconcile the inventories

**Files:** Read `REVERSED\build\radare2_ghidra_function_comparison_20261017.csv`, `REVERSED\build\ghidra_candidate_triage_20261017.csv`, `REVERSED\build\ghidra_candidate_refs_full_20261017.tsv`, and baseline/supplemental export indexes. Update `REVERSED\docs\radare2_ghidra_candidate_triage_20261017.md` only with reproducible totals.

- [x] Verify the 1,349 baseline rows and 337 supplemental source files form 1,686 disjoint addresses.
- [x] Verify the 753 Ghidra-only EXE candidates map to 433 baseline and 320 supplemental C outputs; 17 extra supplemental files are R2-shared.
- [x] Reconcile the available denominators and exact address sets: the 1,212 addressed `functions.csv` entries are all in the 1,686-entry comparison, and the baseline plus supplemental Ghidra exports exactly equal that comparison set.
- [ ] Resolve why the 474 comparison entries outside `functions.csv` are absent from the worklist and classify which are standalone functions, compiler/runtime entries, metadata handlers, or boundary splits.

### Task 2: Classify pointer/reference regions

**Files:** Existing Radare2 scripts/logs, Ghidra reference TSVs, exported C bodies, and the candidate comparison report.

- [x] Document verified startup callbacks, the tested `0x005791xx`/`0x0057924c`/`0x005796xx`/`0x005797xx` regions, and the 50 `.rdata` Catch/Unwind entries.
- [ ] Enumerate remaining source-address runs and group them by contiguous word span, target class, and section.
- [ ] For each run, verify raw words with relocations, inspect static xrefs and decoded consumers, and classify each target or explicitly record why its use remains unresolved.
- [ ] Cross-check every pointer-target body against Ghidra and Radare2 using instruction-level/boundary-aware comparisons; do not rely on linear extent alone.

### Task 3: Close source and reconstruction coverage

**Files:** `REVERSED\tools\audit_function_coverage.py`, manifests, `src`, `src_recovered`, `src_generated`, and decompiled export directories.

- [ ] Run the address-normalized audit against the final candidate/function manifest and report missing, duplicated, declaration-only, generated, and stub definitions separately.
- [ ] For any true export gap, recover the C body from the verified Ghidra function and add it through the existing exporter/workflow; test filename collision handling and large-function output.
- [ ] Re-run the coverage audit; expected result is zero unexplained missing definitions, with boundary/metadata entries explicitly classified.

### Task 4: Compile and validate the reconstructed target

**Files:** Existing `REVERSED\build.bat`, `REVERSED\check.bat`, generated build outputs, and relevant tests.

- [ ] Confirm the available x86 compiler and the exact source/link set used by `build.bat` before invoking it.
- [ ] Run the supported compile/link check and capture compiler/linker diagnostics; fix only proven failures in source or build integration.
- [ ] Run the byte/reconstruction checks and classify results as exact, relocation-equivalent, mismatch, or not included; do not launch the executable in this pass.
- [ ] Report buildability separately from visual/audio/gameplay equivalence; proceed to controlled runtime comparison only after the user’s static-inventory acceptance criteria are met.
