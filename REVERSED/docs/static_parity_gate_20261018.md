# Groove rebuild: static parity gate (2026-10-18)

The current rebuild is **not** code-equivalent to the original. The observed Esc
crash and flickering black menu are behavioral failures, and source-file coverage
alone cannot certify that a C rebuild has the same behavior as the original x86
program. Ghidra pseudocode loses or guesses calling conventions, register inputs,
types, exception handling, and some indirect control flow. DirectX, audio, CRT,
globals, and binary data also affect behavior.

## Evidence and current denominator

Run `tools/audit_rebuild_parity.py` to regenerate
`build/rebuild_parity_audit.csv` and `build/rebuild_parity_audit.json`. It uses
the original `Game/groove.exe` (SHA-256
`151102050d79c0cc703d121e7755f7bb75f436d5822d31e72a43c31cc1adb9bc`),
the address-by-address Ghidra/Radare2 comparison, both Ghidra C export sets,
the selected sources, generated C markers, and actual `build/exe_chunks` input.
This is a read-only provenance audit; it does not infer semantic equivalence.

The current comparison has **1,686** EXE entry addresses. Each has a C export
file, but 337 supplemental files have no `_index.csv` decompile status, and
the independent tools do not prove that no other function boundary was missed.
The 1,686 entries divide into 1,597 in-image code entries, 50 compiler
catch/unwind entries, 38 runtime/import entries, and one CRT entry point.
At the initial audit, **1,523** of the 1,597 in-image code entries occurred in
the EXE compile input and **74** did not. **28** of those 74 had generated
link-stub symbols. After the first recovery batch (`sub_417FA0`), the latest
audit reports 1,524 in the EXE compile input and 73 excluded; 28 stub symbols
remain. The JSON output is the current count authority.
The source selection uses 436 hand-recovered overrides and applies at least one
text patch to 328 in-image code functions. The audit records each address,
selected file, patch count, generated C presence, compile-input presence, and
stub presence. It does not prove those 1,523 bodies compiled into the staged
EXE, or that any compiled body matches the original machine code.

The current `build/exe_chunks` set contains 1,557 bodies total, including some
compiler artifacts. Five selected recovered sources have addresses outside the
1,686-entry comparison; they are listed in the audit summary and need separate
boundary review. The build pipeline rewrites `__fastcall` and `__stdcall`
definitions to C calling conventions and loosens most prototypes. Those are
explicit ABI-parity risks even where a function is included.
The audit also found zero body-text differences between the 1,557 EXE chunk
blocks and their `clean_subset.c` blocks. File timestamps are in generation
order and the staged EXE hash is recorded in the JSON. Timestamp order and
source-text matching do not prove binary linkage or runtime parity.

The first Esc-path spot check compared the original assembly of `sub_41D2C0`
with Ghidra C: both call `sub_40F060` with pointers at offsets `0x18` and
`0x118` from the input-state base and test bit `0x80` at offset `0x19`.
`sub_40F060` obtains the input-list head from the value at `0x00582260` in
the original assembly; the current generated body uses `DAT_00582260[0]`.
This verifies those specific expressions, not the whole functions or the
reason for the Esc crash.

## Bounded workflow and pass criteria

1. **Freeze the evidence.** Keep the original EXE hash and Ghidra/Radare2
   comparison as the denominator. Re-run the comparison only if the binary or
   analysis settings change, then explain every changed function boundary.
2. **Close compile-input gaps.** Resolve each of the 74 excluded in-image
   entries against original instructions, and remove their 28 fallback stubs.
   The gate passes when the audit reports zero unexplained in-image exclusions
   and zero in-image stub symbols. Exception handlers, CRT startup, and imports
   receive separate, explicit dispositions.
3. **Review semantic fidelity of paths, not just files.** For each function on
   the intro/Esc and menu render paths, compare original disassembly with the
   selected C, every patch, parameter/register contract, globals, and indirect
   call target. Record evidence and an unresolved status where Ghidra's output
   is ambiguous. The intro wait/input path starts at `sub_41D2C0`, which polls
   through `sub_40F060`; the main startup path is `sub_41D350`. The current
   window procedure `sub_41DDA0` is a hand reconstruction. None is considered
   verified merely because it appears in the EXE input.
4. **Compare controlled behavior.** Add a reproducible original-versus-rebuild
   trace for startup, Esc at the logo, and menu frames: call order, key state,
   state transitions, render queue counts, DirectDraw operations, and audio
   initialization. A visual difference identifies a failing trace boundary;
   source repair then follows that boundary. Run the visible EXE only behind
   the existing eight-second watchdog and with the user's observation.
5. **Report evidence separately.** Track export coverage, compile/link coverage,
   path-level instruction review, and differential behavior as separate gates.
   Do not report 100% logical equivalence unless all required paths have
   matching observable behavior and remaining uncertainty is stated. Exact
   original-source recovery is not possible from machine code alone.

Next priority: resolve the 74-row exclusion queue before further visual
patching, while manually reviewing `sub_41D2C0`/`sub_40F060` and their input
data layout for the Esc crash. The CSV is the per-function worklist.
