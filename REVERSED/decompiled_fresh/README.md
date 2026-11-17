# Fresh Groove Ghidra export and source coverage

Target: `Game/groove.exe` (PE32 x86), SHA-256 `151102050d79c0cc703d121e7755f7bb75f436d5822d31e72a43c31cc1adb9bc`.

The binary was analyzed with REA 6.4.0 and Ghidra 12.1.4, then imported into the separate headless project `build/fresh_ghidra_project/GrooveFresh`. The Ghidra export is in this directory. It contains one manifest row for every discovered function, one C pseudocode file for each successful Ghidra decompilation, and a data-symbol inventory. The binary hash was unchanged after both analyses.

## Inventory

| Evidence set | Entries |
| --- | ---: |
| REA overview procedure count | 1,251 |
| Fresh Ghidra function entries after promoting initializer-table targets | 1,349 |
| Fresh Ghidra decompilations completed | 1,347 |
| Fresh Ghidra decompilations that timed out | 2 |
| Older REA pseudocode fallbacks for those timeouts | 2 |

The two timed-out Ghidra functions are `sub_447770` and `sub_4CB870`. Each has a full REA pseudocode export under `../decompiled/rea/`, generated from the same executable with REA/Ghidra. A targeted fresh REA decompile of `sub_447770` stalled inside Ghidra's decompiler while processing its 150,625-byte function body and was stopped; the zero-byte attempt output is retained under `../build/`. The existing full REA pseudocode is therefore an older fallback, not a successful fresh retry. The REA overview count and Ghidra function count are different inventory views. Do not compare those totals as though they were interchangeable.

The fresh Ghidra entries reconcile against the previous Ghidra export and the assembly-derived `functions.csv` by address:

| Address membership | Functions |
| --- | ---: |
| Present in both prior inventories | 779 |
| Prior Ghidra export only | 332 |
| Assembly-derived inventory only | 111 |
| New to both inventories | 127 |
| **Fresh Ghidra total** | **1,349** |

## Files

- `_functions.csv`: function names, entry addresses, body sizes, and signatures.
- `_index.csv`: one `ok` or `fail` decompilation status per function.
- `_data.csv`: Ghidra data-symbol inventory.
- `source_coverage.csv`: one address-keyed row per function, with pseudocode source, prior-inventory membership, source candidates, and coverage classification.
- `sub_*.c`, `FUN_*.c`, and other per-function `.c` files: Ghidra pseudocode.

## Current C coverage

The coverage script found 1,171 entries with a C body, 50 with multiple source candidates, 28 represented by harness/runtime replacements, 13 represented only by a link stub, 8 with only the older decompiled export, and 79 with no current C body. “C body found” means that a candidate exists at the same address; it does not prove that the body is semantically equivalent to the fresh pseudocode.

The 79 no-body entries divide into 50 compiler exception/unwind artifacts, two compiler runtime helpers, and 27 newly identified address-based functions. The 27 fresh pseudocode bodies only return. Three startup wrappers were recovered from fresh instruction evidence: `sub_419450`, `sub_41A390`, and `sub_41CED0` each push zero, load a distinct timer-object address into ECX, call `sub_54B970`, and return. Their C translations and the missing seven-DWORD object storage at `DAT_00584860` are in the generated rebuild, and the CRT initializer table now includes all three. A regression test checks that each wrapper passes its exact object address and zero.

The 50 multiple-candidate rows are not automatically linker conflicts. They include alternative generated files, hand translations, and test harness implementations. In 30 rows, `bulk_all.c` has a body while `link_stubs.c` also has a stub; the curated `clean_subset.c`/`chunks` build excludes those bodies, so the stub remains the current build fallback. Review the candidate paths in the CSV before treating any row as a duplicate definition.

The two large renderer functions that fresh Ghidra timed out on were promoted from the existing REA fallback files into `src_recovered`; their former link stubs were removed after the bulk linker confirmed the real definitions. Six pointer-valued switch expressions were corrected to integer-tag switches, supported by the switch semantics and original call patterns. MSVC compiled all 1,507 clean-subset functions, and the bulk build linked `build/groove_rebuild.exe`.

The large fallback bodies still need a calling-convention pass before they can count as semantically matched: the REA pseudocode spells several internal renderer calls with no arguments, while the original assembly pushes nine values at those sites. The current empty C prototypes make those calls compile, but do not prove the generated caller passes the original values. Do not treat successful linking as behavioral parity.

The repaired CRT initializer list contains 124 callable bodies (up from 67 before source recovery); all three timer wrappers are included. The initializer regression test checked each wrapper's object address and zero argument, the existing timer-object test passed, and the source-coverage auditor tests passed. The rebuilt executable was linked but not launched during this source-parity pass.

## Reproduce the coverage ledger

From the repository root, run:

```powershell
& 'C:\Users\Brian\.cache\codex-runtimes\codex-primary-runtime\dependencies\python\python.exe' REVERSED\tools\audit_function_coverage.py --root REVERSED
& 'C:\Users\Brian\.cache\codex-runtimes\codex-primary-runtime\dependencies\python\python.exe' REVERSED\tools\test_audit_function_coverage.py
```

Source coverage is an inventory and comparison queue. It is not proof of behavioral parity or byte-identical output; those require reviewing the listed C bodies and validating the rebuilt executable against the original.
