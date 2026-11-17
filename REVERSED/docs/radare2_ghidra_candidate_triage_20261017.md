# Ghidra-only function candidate triage (2026-10-17)

## Scope and result

This is a static cross-check of function starts found by Ghidra 12.1.4 but not by Radare2 6.2.4 `-AA` in the original `groove.exe` and `aal.dll`. It tests whether selected starts can be independently decoded by Radare2 when forced with `af`; it does not establish source-code equivalence or complete function discovery.

The address-level comparison has 753 Ghidra-only starts in `groove.exe` and 8 in `aal.dll`. The Ghidra triage output CSV currently has 761 rows because it combines those 753 EXE candidates and 8 DLL candidates. Treat `ghidra_aal_candidate_triage_20261017.csv` as the clean DLL triage file; do not interpret all 761 rows as EXE entries. The combined CSV's EXE rows are all resolved to instructions and body sizes; the DLL candidates were analyzed in a separate Ghidra import as well.

## Forced Radare2 validation

For `aal.dll`, Radare2 forced analysis independently identified all eight candidate starts as functions, with sizes matching Ghidra exactly:

| Address | Bytes |
| --- | ---: |
| `0x21101c20` | 279 |
| `0x211046f0` | 30 |
| `0x2110d159` | 26 |
| `0x2110d173` | 16 |
| `0x2110d4ff` | 23 |
| `0x2110d705` | 27 |
| `0x2110da45` | 90 |
| `0x2110dead` | 17 |

For `groove.exe`, the focused set was the 18 Ghidra-only candidates with Ghidra call-type references and outside Radare2's reported linear extents. Forced Radare2 analysis found 15 as separate functions with the same start and body size. The other three are exact Radare2 decoded basic-block starts inside larger Radare2 function CFGs, so the tools disagree on function boundaries rather than on whether code exists:

| Candidate | Ghidra body | Radare2 CFG containing it | Finding |
| --- | ---: | --- | --- |
| `0x00406010` | 142 bytes | `fcn.004060a0`, 172 bytes, min `0x406010`, max `0x4060bc` | Exact basic-block start |
| `0x0041c1c0` | 21 bytes | `fcn.0041cd10`, 2,992 bytes, min `0x41c1c0`, max `0x41cd70` | Exact basic-block start |
| `0x0054ae20` | 455 bytes | `fcn.0054aff0`, 479 bytes, min `0x54ae20`, max `0x54afff` | Exact basic-block start |

The min/max values above are Radare2 function bounding addresses, not proof that every byte between them belongs to the CFG. The three candidates were also checked against Radare2's decoded basic-block instruction addresses.

The first boundary case, `0x00406010`, is an interior block in the `0x004060a0` routine, rather than an independently referenced function: the only incoming edge is the unconditional jump at `0x004060b6`, and the block returns at `0x0040609d`. Radare2's CFG follows that backward jump into the earlier block. Ghidra's candidate record labels that one reference as call-like, but the bytes decode to `JMP`, so the instruction is the stronger evidence.

The other two candidates have stronger evidence for distinct routines, although both are reached by tail jumps rather than direct calls. `0x0041c1c0` is a 21-byte block that stores two global constants and returns; two unconditional jumps from the separately located `0x0041cd10` routine target it. Ghidra models the 21-byte block and the 96-byte `0x0041cd10` body separately, while Radare2's CFG for `fcn.0041cd10` spans both through those jumps. `0x0054ae20` begins a 455-byte body with stack setup and ends in `RET`; `0x0054aff0` is a separate 15-byte entry that updates globals then jumps to `0x0054ae20`. Ghidra reports both entries separately, while Radare2's CFG rooted at `0x0054aff0` also includes the body at `0x0054ae20`. This is consistent with Radare2 folding tail-called routines into one CFG; the separate Ghidra entries and distinct return structure support retaining both starts in the candidate inventory.

Two very large EXE candidates, `0x00442bd0` and `0x004c6cd0`, each have a 12,166-byte Ghidra body and were independently found by forced Radare2 analysis at the same address and size. Their machine bytes are similar but not identical (about 98.18% byte positions match); normalized decompiler output similarity was 98.755%. Treat them as related variants, not duplicates.

## Additional checks on high-priority candidates

The ten EXE candidates with zero incoming Ghidra references were each forced through Radare2 analysis. All ten were reported as new functions at the exact candidate address and with a body size exactly matching Ghidra: `0x0040fc90` (21), `0x0040fcb0` (21), `0x0040fcd0` (33), `0x00411470` (33), `0x00413da0` (362), `0x00417fa0` (117), `0x00418420` (123), `0x00550000` (19), `0x00563ec5` (27), and `0x00567fdb` (13). This corroborates their decoded bodies, but does not establish runtime reachability; callbacks, dynamically selected code, or dead code remain possible.

The 28 EXE candidates with a nonzero Ghidra `call_count` were also checked with Radare2 cross-reference analysis. The 114 statically resolved reference lines consist of 56 unconditional jumps, 4 conditional branches, and 54 data references; none is a direct `CALL` instruction. Thus, Ghidra's call-like reference count is a useful lead but cannot be treated as a count of direct call sites. In particular, the data references to the two large variants may represent addresses used by indirect dispatch, and should be checked in their surrounding control flow before assigning semantics.

That follow-up confirms the two large variants are used as indirect-call targets. Ghidra records 26 computed-call references to `0x00442bd0` and 15 to `0x004c6cd0`; the latter's call sites are a subset of the former's. Radare2 independently decoded all 26 unique call sites as register-indirect `CALL` instructions (2 `call eax`, 17 `call ecx`, 5 `call edx`, and 2 `call esi`). It also decoded all 52 unique address-reference sites as `MOV reg, 0x00442bd0` or `MOV reg, 0x004c6cd0`, with no mismatches. This resolves the earlier apparent `DATA` versus computed-call disagreement: the pointer is loaded at one instruction and called later through a register.

## Full EXE reference pass

The full Ghidra export in `../build/ghidra_candidate_refs_full_20261017.tsv` covers all 753 EXE candidates and contains 949 references. Radare2 decoded all 184 unique executable control-flow source sites represented by 199 reference rows: 39 are register-indirect `CALL`s, 141 are `JMP`s, and 4 are conditional jumps. By Ghidra's labels, its 56 `UNCONDITIONAL_CALL` references are actually tail `JMP`s; two references labelled `UNCONDITIONAL_JUMP` originate from `CALL` instructions. The 52 `COMPUTED_CALL` rows collapse to 37 unique call sites because several candidates share call sites.

The 750 `DATA` references split into 546 Ghidra `addr` records, 154 code instructions, and 50 records without a decoded instruction. Using Radare2's PE section map, the 546 address-record sources are 544 in `.data`, one in `.rdata`, and one in `.text`; all 50 instructionless references are in `.rdata`. Radare2 read the 546 address-record words and the 50 instructionless words directly from the binary: all 596 values exactly equal the candidate addresses Ghidra referenced. The 154 instruction-backed sources decoded in Radare2 as 141 `MOV` and 13 `PUSH` instructions. For the two large variants, the 52 code-backed address loads were additionally checked for their exact immediate values, all matching.

The 50 instructionless references come from `.rdata` addresses in `[0x0056e000, 0x00570000)` and point to 50 distinct Ghidra entries. Their exported function comments classify 41 as `Unwind` and nine as `Catch`, consistent with exception-handling metadata rather than ordinary direct-call sites. Forced Radare2 analysis produced a containing function record for all 50 targets: 49 are exact Radare2 function starts, while the `Catch` entry at `0x004113fb` lies inside Radare2's `0x00411000` function (1,117 bytes). This is a concrete function-boundary disagreement; Ghidra exports that entry as a 98-byte `Catch` handler. Radare2's reported `realsz` matches Ghidra's body size for 45 targets. Four `Unwind` entries (`0x0056d6ab`, `0x0056d6c0`, `0x0056d700`, and `0x0056d7b8`) differ because their short entry stubs tail-jump into shared code, which Radare2 includes in its analyzed body. These counts support the exception-entry interpretation, but do not independently prove how the runtime consumes every record.

The 546 address-record references form 73 runs of adjacent 4-byte entries. The largest is `0x00570004`–`0x0057025c` (151 distinct candidate targets); other large runs include 43 entries at `0x005796c0`–`0x00579768` and 37 entries at `0x0057924c`–`0x005792dc`. Radare2's word view confirms these are code addresses stored consecutively. The tables' specific purpose—such as callback tables, class dispatch, or exception data—has not yet been proven.

## Table-use verification

The 151-entry pointer run at `0x00570004`–`0x0057025c` is confirmed as an executed callback table. Radare2 disassembly of `0x00563b87` shows it passes the range `[0x00570000, 0x00570260)` to `0x00563c6f`. That routine advances through the range in four-byte steps, loads each nonzero pointer, and executes `CALL EAX`. The first dword is zero and the remaining 151 values point to candidate code addresses. This proves those 151 targets are invoked indirectly by this startup/init path, even though Radare2's automatic function inventory omitted them.

The same helper is used by the termination path at `0x00563bd6`. It walks the dynamically registered callbacks in reverse order, then passes `[0x0057027c, 0x00570284)` and `[0x00570288, 0x00570290)` to the helper for two more short cleanup ranges. It does not pass any of the large `0x00579xxx` runs.

Other large `.data` pointer runs remain unresolved. Radare2 `axt` found no direct references to the tested starts `0x005796c0`, `0x0057924c`, `0x00579150`, `0x00579600`, and `0x00579798`; raw scans found no occurrences of those exact table-base addresses, their image-relative offsets, or four of five offsets relative to `.data` base `0x00570000`. The fifth relative offset (`0x9600`, for `0x00579600`) appeared as bytes nine times, but none aligned with a decoded instruction in the relevant Radare2 function, so these are not evidence of a table access. For the 62-word region at `0x00579108`-`0x005791fc`, the two preceding dwords at `0x00579100` and `0x00579104` are `0x31` and `0x18`. Radare2 `axtj` returned empty results for `0x00579100`, `0x00579108`, `0x00579150`, `0x005791c0`, and `0x005791fc`. A full-file byte scan found no exact pointer encodings for `0x00579100`, `0x00579108`, `0x00579150`, or `0x005791c0`, and no image-relative (`0x179100`, `0x179108`) encoding for the first two starts. The `.data`-relative encoding `0x9100` appeared three times, but each match crosses adjacent dwords or is part of instruction bytes, not an aligned address value; `0x9108` did not occur. These scans and xrefs do not rule out code that computes a base address or uses an indirect index. In the full Ghidra reference export, the 43 targets in `0x005796c0`-`0x00579768` have no other static references. The 37 entries in `0x0057924c`-`0x005792dc` contain 35 unique targets; those targets have eight additional references, all from other data locations, and no recorded code/control-flow references. This lack of static code references does not rule out indirect calls. The entries decode as code pointers, but their purpose and runtime use remain unproven. Radare2's C++ vtable scan reported nine vtable starts, all outside these `.data` runs. No callback/vtable classification is claimed for these runs yet; they may use computed offsets or belong to data that this scan cannot identify.

There is a semantic clue in the `0x005796c0` run: its entries at `0x00579744` and `0x00579748` point to `0x0054d200` and `0x0054d220`. Radare2 decodes these as short routines that read an object field at `+0x18` and pass it with the adjacent strings `stCollision_AlienVar` and `stCollision_AlienVarAddress` to a formatter. That suggests the pointer run is associated with collision-variable diagnostics, but it does not prove the run is consumed at runtime or establish its exact role.

Radare2 forced analysis recovered a body for each of the 43 distinct targets in `0x005796c0`-`0x00579768`; all 43 body sizes match Ghidra's candidate inventory. Thirty-six C files were in the 337-file candidate-audit folder, and the other seven were already in the baseline decompilation folder. A targeted Ghidra re-export wrote those seven to a separate audit folder; this was not a project-wide source gap. The bodies are mixed: examples include a state-flag setter at `0x0054fa50`, a bytecode-stream skipper at `0x00553850`, an operand decoder at `0x0054fc40`, wrappers that call shared helpers, and the two collision-variable diagnostic routines. This points to a mixed callback/serialization or interpreter-handler registry, but the missing table consumer prevents a firm classification.

The `0x0057924c` run has a stronger common pattern. Its 37 entries resolve to 35 unique candidate routines. Radare2 forced analysis recovered all 35 bodies, with body sizes matching Ghidra's inventory. Twenty-six C files were in the candidate-audit folder; the other nine were already in the baseline decompilation folder and were re-exported separately for this audit. Nine routines are 22 bytes and share the object-field/logging shape, with labels including `stLink`, `stUnlink`, `stStreamPlay`, `stStreamQueue`, and several `stLight...` fields. This is consistent with a table of object-state diagnostic or serialization callbacks. The table's runtime consumer remains unlocated, so that role is still an inference rather than a confirmed call path.

Two additional `.data` runs were checked: `0x00579600`-`0x0057964c` has 20 pointer entries targeting 16 unique functions, and `0x00579798`-`0x005797cc` has 14 entries targeting 14 functions. Radare2's relocation-applied raw words match all 34 Ghidra data-reference values. Forced analysis recovered all 30 unique targets, with body sizes matching Ghidra's inventory; all 30 already have C files in the existing baseline plus candidate-audit outputs. Their consumer and exact role remain unresolved.

The larger contiguous region at `0x00579108`-`0x005791fc` contains 62 distinct 32-bit values in Radare2's relocation-applied raw word dump, and all 62 targets are function starts in Ghidra. Of these, 60 are Ghidra-only: 59 are recorded by Ghidra's candidate-reference export in four adjacent runs (`6 + 10 + 27 + 16`), while `0x00550000` is the extra pointer at `0x0057914c` that Ghidra did not record as an xref (`xref_count=0`). The other two targets are already shared functions: `0x00552dc0` (63 bytes) at `0x00579120` and the one-byte `RET` stub `0x00426500` at `0x005791bc`. Forced Radare2 analysis and targeted Ghidra export covered all 62 targets; every exported body length matches Radare2 (`62/62`), and the 60 Ghidra-only lengths also match Ghidra's candidate inventory. The exporter wrote 62 `.c` files with no per-function failures. These were not project-wide missing sources: 34 targets were already in the candidate-audit folder, and the other 28 were in the baseline decompilation folder. The isolated 62-file export provides a consistent artifact for this comparison. These bodies include field-name/value formatters labeled `stFlash`, `stTrans`, and `stWpdel`, wrappers around shared helpers such as `sub_54BC00`, `sub_404DB0`/`sub_404D60`, and other short state/operation routines. This mix is consistent with a data-driven method or handler registry, but the runtime consumer has not been found, so its role remains a hypothesis.

The Ghidra reference export also has 31 additional pointer-source records in `0x005791c0`-`0x00579244`; 16 overlap the already checked `0x00579108`-`0x005791fc` span, leaving 15 new targets in `0x00579200`-`0x00579244`. Forced Radare2 analysis recovered all 31 target records, and all 31 body sizes match Ghidra. Their C exports are present. Eight are 22-byte field-name logging wrappers that call `sub_414600` with labels including `stWpdel`, `stWpnew`, `stAnimsetspeed`, `stCollheight`, and `stMapreplace`; the remaining targets have mixed short-helper bodies. This extends the checked region's evidence but still does not identify the table consumer or prove runtime use.

## Comparison and project-manifest denominator

The project worklist `functions.csv` contains 1,213 rows: 1,153 `game` entries, 59 `ilt_thunk` entries, and one addressless `Callback` library row. Its 1,212 unique code addresses all occur in the Ghidra/Radare2 EXE comparison. That comparison contains 1,686 unique entry addresses, so 474 comparison entries are outside the current worklist.

Those 474 split by the comparison's existing tool-based class into 272 `both_exact`, 179 `ghidra_only_outside_radare2_ranges`, and 23 `ghidra_entry_inside_radare2_range`. The classes establish address relationships, not why every address is absent from the worklist or whether every entry should be compiled as a separate source function. The 50 `.rdata` Catch/Unwind entries described below are one identified subset of this difference.

The 1,349-address fixed Ghidra export index and 337-address supplemental export set are disjoint, and their address union is exactly equal to the 1,686-address EXE comparison set: zero comparison entries lack a C export and zero exported addresses fall outside that comparison. This proves file-level coverage of the compared addresses. It does not resolve the 474-entry worklist difference or prove function-boundary correctness.

Evidence: `../functions.csv`, `../build/radare2_ghidra_function_comparison_20261017.csv`, `../decompiled_ghidra_12_1_4_fixed/_index.csv`, and the source files in `../decompiled_candidate_audit_ghidra_20261017/`.

## C source coverage reconciliation

The 753 Ghidra-only EXE candidates have no filename-level source gaps across the baseline and supplemental Ghidra exports. Of these, 433 are represented in the fixed baseline `_index.csv` and all 433 have status `ok`; the remaining 320 have matching C files in the supplemental candidate-audit folder. That folder contains 337 unique, nonempty `sub_<address>.c` files with a function-definition pattern: 320 correspond to Ghidra-only EXE candidates and 17 are candidates also identified by Radare2. The 17 shared entries explain why the supplemental file count is larger than the 320-candidate remainder.

The fixed baseline has 1,349 indexed addresses, all with status `ok`. Its address set and the 337 supplemental addresses are disjoint; together they cover exactly the 1,686 EXE entries in the comparison. This establishes source-file coverage for that comparison set, not semantic equivalence to the original executable, correct runtime behavior, or completeness beyond the analyzed inventories. The function-definition pattern check is a structural sanity check, not a C compiler check.

Evidence: `../decompiled_ghidra_12_1_4_fixed/_index.csv` and the C files under `../decompiled_candidate_audit_ghidra_20261017/`; the candidate address list is `../build/ghidra_candidate_triage_20261017.csv`.

## Limits and next step

This focused result materially narrows the discrepancy: Radare2's automatic analysis missed valid function starts, while some apparent disagreements are function-boundary choices. The startup table accounts for 151 Ghidra-only candidates. The `0x00579108`-`0x005791fc`, `0x0057924c`, `0x00579600`, `0x005796c0`, and `0x00579798` regions now have independently checked function targets and sizes, but their runtime consumers remain unresolved. The coverage reconciliation above shows that every Ghidra-only EXE candidate has a corresponding exported C file, while source presence alone does not demonstrate correct function boundaries or behavior. The next pass should trace how the verified regions are consumed and continue the remaining address-word-only candidates. The eight DLL candidates are all corroborated as functions by both tools under forced analysis.

The comparison CSV's `inside R2 range` column uses reported linear extents and is only a coarse overlap indicator; it is not exact CFG membership. No claim of full function completeness should rely on that column alone.

## Evidence files

- `../build/radare2_ghidra_function_comparison_20261017.csv` — address-by-address `-AA` comparison.
- `../build/ghidra_candidate_triage_20261017.csv` — Ghidra triage rows; 753 EXE plus 8 DLL rows.
- `../functions.csv` — original assembly-derived project worklist used to reconcile the 1,212 addressed entries with the 1,686-address Ghidra/Radare2 comparison set.
- `../decompiled_ghidra_12_1_4_fixed/_index.csv` and `../decompiled_candidate_audit_ghidra_20261017/` — baseline and supplemental C source sets used for the coverage reconciliation above.
- `../build/ghidra_aal_candidate_triage_20261017.csv` — separate DLL candidate triage.
- `../build/radare2_exe_called_candidates_20261017.r2` and `.log` — forced EXE analysis of the focused 18 candidates.
- `../build/radare2_aal_candidate_forced_20261017.r2` and `.log` — forced DLL analysis of all eight candidates.
- `../build/ghidra_candidate_refs_20261017.tsv` — Ghidra reference kinds and callers for candidate starts.
- `../build/ghidra_candidate_refs_full_20261017.tsv` — full 949-row reference set used to verify the candidate reference categories and identify the 151-entry startup callback table.
- `../build/radare2_table_579108_words_reloc_20261017.log` — relocation-applied raw words for all 62 entries at `0x00579108`-`0x005791fc`; `../build/radare2_table_579100_words_reloc_20261017.log` includes the preceding `0x31` and `0x18` dwords; `../build/radare2_table_579150_words_20261017.log` and `../build/radare2_table_579150_words_reloc_20261017.log` preserve the earlier 44-word subrange check.
- `../build/radare2_table_579108_xrefs_20261017.r2` / `.log`, `../build/radare2_table_579108_rawscan_20261017.log`, and `../build/radare2_table_579100_rawscan_20261017.log` — direct xref and exact-address encoding checks for the region and the unaligned `0x9100` byte matches.
- `../build/radare2_table_579108_forced_20261017.r2` / `.log`, `../build/radare2_table_579150_forced_20261017.r2` / `.log`, `../build/radare2_table_5791c0_forced_20261017.r2` / `.log`, and `../build/radare2_table_5791xx_known_forced_20261017.r2` / `.log` — forced Radare2 analysis for the 62 targets.
- `../build/ghidra_table_579108_export_20261017.log`, `../build/ghidra_table_579150_export_retry_20261017.log`, `../build/ghidra_table_5791c0_export_20261017.log`, and `../build/ghidra_table_5791xx_known_export_20261017.log`, with C files in the matching `../decompiled_table_579108_ghidra_20261017/`, `../decompiled_table_579150_ghidra_20261017_retry/`, `../decompiled_table_5791c0_ghidra_20261017/`, and `../decompiled_table_5791xx_known_ghidra_20261017/` folders — targeted Ghidra exports for all 62 targets.
- `../build/radare2_tables_57924c_5796c0_forced_20261017.r2` / `.log` — forced Radare2 analysis for the 78 distinct targets in the `0x0057924c` and `0x005796c0` runs; all sizes match Ghidra's candidate inventory.
- `../build/ghidra_tables_57924c_5796c0_missing_addresses_20261017.txt` and `../build/ghidra_tables_57924c_5796c0_export_20261017.log`, with 16 selected re-exports in `../decompiled_tables_57924c_5796c0_ghidra_20261017/` — these targets were absent from the candidate-audit subset but already present in baseline decompilation output.
- `../build/radare2_tables_579600_579798_forced_20261017.r2` / `.log` and `../build/radare2_tables_579600_579798_words_reloc_20261017.log` — forced body-size checks for 30 unique targets and raw-word comparison for 34 reference entries.

## Additional pointer run at `0x005792e4`-`0x005792f4`

Radare2's relocation-applied `pxw` output reads the five words in this span as `0x0054fbd0`, `0x00553b80`, `0x00553b50`, `0x0054f960`, and `0x0054f5c0`, matching the five Ghidra `DATA` references. Direct Radare2 `axtj` queries for the five individual slots returned empty arrays; this does not exclude a computed/indexed consumer.

Forced Radare2 analysis created exact-start functions for all five targets with `realsz` values of 40, 40, 40, 61, and 65 bytes respectively. The comparison CSV records matching Ghidra/Radare2 sizes for four targets (`0x0054f960`, `0x0054fbd0`, `0x00553b50`, `0x00553b80`). It has no Ghidra size value for `0x0054f5c0`, so that target is not counted as a verified size match. A C export exists for all five: four in the fixed baseline folder and `sub_54F5C0.c` in the supplemental candidate folder. This run adds no source-export gap; its table consumer and the Ghidra boundary metadata for `0x0054f5c0` remain unresolved.

The wider `0x005792e4`-`0x005795e8` source interval contains 127 Ghidra `DATA` reference records to 124 distinct targets. Reading the original PE by section-relative file offsets confirms all 127 source dwords exactly equal their referenced target addresses. Forced Radare2 analysis produced an exact-start body for all 124 targets. The fixed Ghidra index has body sizes for 40 of these targets; all 40 match Radare2's `realsz`. The other 84 target C files are present, but the fixed index does not provide sizes for them, so their body-size agreement is unverified. Every target has a comparison-CSV row classified as Ghidra-only outside Radare2's automatic linear ranges. No direct slot xrefs or table consumer were established by this check.

Across the full `.data` reference inventory, the original PE contains 544 Ghidra-addressed dword records in 71 contiguous source runs. Mapping each source VA through the PE section table and reading the file-backed dword confirms all 544 values exactly equal the Ghidra-referenced target addresses. This validates the raw words and the candidate destinations, but it does not by itself prove that each run is consumed as a function-pointer table.

## Supplemental starts and compile verification (2026-10-17)

Five additional recovered sources were not represented in the 1,686-address Ghidra/Radare2 comparison. A fresh targeted Ghidra 12.1.4 headless import of the original `Game/groove.exe` used the `x86:LE:32:default:windows` profile and exported all five as functions. Radare2 forced analysis also created exact-start functions for all five. Their checked-in C bodies match the fresh Ghidra output after removing comments and normalizing whitespace.

| Address | Ghidra body bytes | Radare2 `realsz` | Finding |
| --- | ---: | ---: | --- |
| `0x0054b800` | 10 | 809 | Ghidra and the instruction bytes show a 5-byte call followed by a 5-byte tail jump to `0x0041c230`. Radare2 includes the tail-jump destination in its analyzed function extent; the size disagreement is a boundary choice. |
| `0x0054da90` | 11 | 11 | Exact size match. |
| `0x0054dac0` | 11 | 11 | Exact size match. |
| `0x0054e880` | 16 | 16 | Exact size match. |
| `0x0054f710` | 7 | 7 | Exact size match. |

The comparison inventory therefore has 1,686 starts; these five additional targeted starts bring the source set to 1,691. The actual `make_bulk.collect_source_files` selection contains 1,653 unique address-mapped definitions: 1,648 from the comparison inventory plus these five. Its 38 excluded source names consist of 37 CRT/DirectDraw/DirectInput runtime routines handled through the build's runtime/import substitutions, and `caseD_2d` at `0x00551a4b`. Radare2 places `caseD_2d` at a basic-block boundary inside `fcn.00550e60`; it has no call reference and is not emitted as an independent function. The parent `0x00550e60` C body is in the generated bulk.

Validation performed after regeneration:

- `python tools/compile_check.py --all --chunk 20`: 1,653 functions compiled in 83 chunks, zero compiler errors, zero pending failures.
- `harness/build_dlls.bat bulk`: exit code 0; linked `build/groove_rebuild.exe`, `build/groove_ghidra.dll`, and `build/groove_hand.dll`.
- `python -m unittest discover -s tools -p 'test_*.py' -v`: all 20 tests passed.

The Ghidra/Radare2 address comparison is an analyzed inventory, not proof that no additional undiscovered functions exist. Successful compilation and linking establish buildability of this reconstructed harness target; they do not establish binary or gameplay equivalence. The separate AAL DLL has 277 matching source exports, but those are not part of the 1,653-function Groove EXE bulk build.

## Full EXE candidate forced-start reconciliation (2026-10-17)

The 753 EXE rows in `../build/ghidra_candidate_triage_20261017.csv` were forced through Radare2 6.2.4 against the original `../Game/groove.exe`. The unmodified forced pass reported exact-start functions for 652 candidates; the remaining reports were affected by existing overlapping CFG ownership. A second pass removed the current owner at each address before forcing that candidate. It produced an exact-start Radare2 record for 750 candidates. Every one of the 753 candidate addresses has a corresponding Ghidra C export; no address-level C file is missing.

The three candidates without a standalone Radare2 function record have direct explanations in the instruction stream:

| Address | Ghidra candidate | Independent evidence |
| --- | --- | --- |
| `0x004113fb` | `Catch@004113fb`, 98 bytes | This is an exception landing pad inside Radare2's `0x00411000` function, not an independent function entry. Ghidra labels it as a catch handler. |
| `0x00567e9d` | 5-byte alias for `sub_56AB58` | The bytes are `JMP 0x0056ab58`; the exported C wrapper calls `sub_56AB58` and returns. |
| `0x00567ef3` | 5-byte alias for `sub_567E4C` | The bytes are `JMP 0x00567e4c`; this is a tail-jump alias of the exported target function. |

Of the 97 body-size differences in the owner-reset pass, 84 are exactly 5-byte Ghidra `JMP` entries. Radare2 follows each tail jump into its destination CFG, so its `realsz` includes target instructions. The remaining size differences were checked against Ghidra function ranges and raw Radare2 disassembly; they are function partition or alignment differences, not missing C exports. Examples with exact byte accounting are:

Radare2's owner-reset pass is order-sensitive when candidate CFGs overlap, so its aggregate size-difference count is a diagnostic, not 97 independent failed matches. Fresh single-target Radare2 sessions resolved order-dependent results; for example, `0x00427f60` matches at 60 bytes in both tools, although the shared-session pass reported only 12 bytes.

| Ghidra/Radare2 relationship | Ghidra body bytes | Radare2 `realsz` | Reconciliation |
| --- | ---: | ---: | --- |
| `0x00406010` + `0x004060a0` | 142 + 28 | 170 | Radare2 owns both Ghidra ranges in one CFG. |
| `0x0040f220` + `0x0040f3b0` | 102 + 118 | 220 | Radare2 owns the parent and nested Ghidra range together. |
| `0x00413c40` + `0x00413cc0` | 89 + 136 | 225 | Radare2's CFG combines the two Ghidra functions. |
| `0x00427f60` | 60 | 60 | Fresh single-target Radare2 analysis matches Ghidra exactly. |
| `0x00434ad0` | 4,301 | 4,451 | Ghidra has five ranges; the four gaps total 41 + 34 + 41 + 34 = 150 bytes, which Radare2 includes in its linear extent. |
| `0x0054ae20` + `0x0054aff0` | 455 + 15 | 470 | Radare2 initially assigns both Ghidra functions to one owner; after removing that owner and forcing `0x0054ae20`, its body is exactly 455 bytes. |
| `0x00550e60` + `caseD_2d` at `0x00551a4b` | 6,118 + 62 | 6,180 | The latter is a switch/basic-block range inside the parent, not an independent call target; it remains excluded from the bulk function selection. |
| `0x00563382` + `0x005684ce` + `0x00568519` | 467 + 13 + 163 | 643 | Radare2's single CFG includes all three Ghidra function ranges. |
| `0x0056d3e9` + `0x0056d41f` | 42 + 12 | 54 | The first Ghidra body tail-jumps to the second; Radare2 follows that target. |

At `0x0056ab58`, Ghidra's body is 23 bytes and ends after a call; the next byte is `INT3` alignment (`0xcc`), which accounts for Radare2's 24-byte extent. At `0x0040e040` and `0x0040f4b0`, each 10-byte call-plus-tail-jump wrapper reaches a 12-byte Ghidra target; Radare2 reports the combined 22 bytes. These targeted checks explain the size differences without treating automatic-analysis extents as source omissions.

The `.data` reference audit covers 544 address-records to 514 distinct targets. All 514 targets have C exports. Radare2 created exact-start functions for 513 in the broad run; the remaining `0x0054ae20` was verified with the owner removed as described above. This validates those target starts and exports, but does not prove every pointer run is consumed at runtime.

Evidence artifacts: `../build/ghidra_r2_candidate_reconciliation_20261017.csv`, `../build/radare2_all_ghidra_only_exe_candidates_forced_20261017.log`, `../build/radare2_all_ghidra_only_exe_candidates_reforced_20261017.log`, `../build/radare2_all_data_ref_targets_forced_20261017.log`, and the targeted range/instruction dumps under `../build/ghidra_function_ranges_*_20261017.log` and `../build/ghidra_boundary_instructions_20261017.log`.

Final validation rerun: `harness/build_dlls.bat bulk` exited successfully and produced valid x86 PE files (`groove_rebuild.exe`, 1,153,024 bytes; `groove_ghidra.dll`, 983,040 bytes; `groove_hand.dll`, 11,264 bytes). `python tools/compile_check.py --all --chunk 20` compiled all 1,653 generated function bodies in 83 chunks with zero compiler errors and zero pending failures. The full Python test suite passed all 20 tests. These checks establish compilability and linkability of the reconstructed target, not gameplay equivalence.

This reconciles the candidate and pointer-target discrepancies checked here; it does not prove that the tools discovered every possible code entry in the original PE, nor that reconstructed C reproduces the original game's runtime behavior.
