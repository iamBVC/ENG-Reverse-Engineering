# Execution ledger: resolve 22 Ghidra artifacts

## Scope and decisions

- User authorized fixing the 22 flagged function entries in the Groove reconstruction.
- Reference executable: `Game/groove.exe`; all register and frame claims are checked against its 32-bit instructions and fresh Ghidra exports.
- Do not launch either game GUI during this work; prior black-screen runs make offline validation the safer path.
- Preserve x86 register, stack, SEH, and x87 contracts. Use naked assembly only where C cannot express the verified contract.
- Work in the existing shared workspace on `main`; do not create a worktree because the current sandbox permits writes only in the project root and `.git` is read-only. This leaves changes unisolated, so review the diff before delivery.

## Completed recovery work

- Recovered `sub_562840`, `sub_567B34`, and `sub_56D674` with x86 naked assembly; verified their instruction/frame contracts against the original.
- Merged `sub_413CC0` into its proven parent and documented that fragment in the generated-function inventory.
- Recovered string-error paths `sub_56D0A0`, `sub_56D0FA`, and `sub_56D2CC`, including handler thunks and legacy EH metadata.
- Fixed the color packers `sub_409290` and `sub_40AD30` to retain AH from the first `__ftol` result, matching the original byte-pack sequence.
- Replaced uninitialized `extraout_ST0` checks in `sub_40AF10` and `sub_40B750` with the explicit nonzero-alpha predicate corresponding to `sub_409510`'s x87 scale result.
- Recovered `sub_56D188`, `sub_56D1E1`, `sub_56D23E`, and `sub_56D326` from original instructions. Added their relocated EH3 handler thunks and mapped original FuncInfo tokens `0x56F658`, `0x56F680`, `0x56F6A8`, and `0x56F738` to matching one-state unwind records.
- Recovered `sub_56814E`, `sub_5683D0`, and `sub_568519` with x87 sequences; retained the original helper already present in `recovered_crt_helpers.c` rather than adding a duplicate.
- Recovered `sub_56B376`, `sub_56B57C`, `sub_56B62E`, and `sub_56B834` from the original instruction streams. Their emitted opcode counts match the original function ranges, including the distinct `FPREM`/`FPREM1` instructions. Added the overlapping constants/table bytes read from the original image to `x87_math_helpers.c`.
- Recovered `sub_563382` from its caller and original x86 flow, including the custom stack/control-word return, `pow` error path, NaN/infinity branches, and negative-argument re-entry. A first object-code comparison exposed omitted branches and an `FPREM` distinction; those were corrected before the final build.
- Static scan of the 23 exported target rows found zero unresolved pseudo-registers. The `sub_413CC0` row is included in the recovered parent, leaving 22 actual target entries.

## Build evidence

- `REVERSED/build/resolve_22_20261102_final6.log`: final full bulk build passed; 1,690 generated bodies, all 1,690 clean, compiler exit code 0, zero compile errors, and zero link stubs. It produced `groove_rebuild.exe`, `groove_ghidra.dll`, and `groove_hand.dll`.
- `REVERSED/build/rebuild_parity_audit.json`: 1,728 selected entries; 1,690 generated bodies; no EXE-input body mismatches, no uncovered merged fragments, no excluded in-image bodies, and no in-image code stubs. This is a provenance/input audit, not proof of behavioral equivalence.
- `REVERSED/build/resolve_22_final_obj_disasm.txt`: emitted object disassembly checked against Radare2's original instruction ranges. All opcode classes are represented for `sub_563382`; its missing `call sub_568445` is replaced by the helper's exact inline stack operations. The four `sub_56B*` functions match original opcode counts.
- `git diff --check` exited 0; Git reported only existing LF-to-CRLF conversion warnings. No files were staged or committed.
- No GUI/game run was performed. The full unittest suite was not run, per the active instruction not to run tests unless the user asks.

## Remaining behavior limits

All 22 targeted Ghidra entries are recovered and compile. The rebuilt EXE has not been launched in this pass, and these results do not prove full logical or visual equivalence to `groove.exe`.
