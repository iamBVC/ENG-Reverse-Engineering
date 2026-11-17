# Radare2/Ghidra function-start comparison (2026-10-17)

Radare2 6.2.4 Win64 analyzed both original PE32 binaries with `-AA` (aggressive analysis). A second pass with `bin.relocs.apply=true` produced identical function-start sets: 933 starts for `groove.exe` and 269 for `aal.dll`.

The unsuffixed `radare2_6.2.4_groove_aflj.json` is a separate 914-start inventory and is not the `-AA` baseline used in this comparison. A fresh `-AA` run produced 933 starts, exactly matching the saved `radare2_6.2.4_groove_aaaa_reloc_aflj.json` address set (zero set differences).

Ghidra 12.1.4 has 1,349 baseline `groove.exe` exports plus 337 supplemental entries (1,686 unique addresses), and 276 baseline `aal.dll` exports plus 1 supplemental entry (277 unique addresses).

For `groove.exe`, all 933 Radare2 starts match a Ghidra export exactly. Ghidra has 753 starts absent from Radare2; 40 lie within a Radare2 function's reported extent, while 713 lie outside those extents. For `aal.dll`, all 269 Radare2 starts match exactly; Ghidra has 8 additional starts, all outside Radare2 function extents.

The `0x00568191` body-size discrepancy is resolved. Ghidra originally had no instruction at that entry, so `ExportSelectedFunctions.java` created a one-byte stub. The exporter now disassembles an undefined entry before creating the function. Reproducing the original one-byte state and rerunning the exporter produced a 52-byte Ghidra body, matching Radare2's 52-byte, 22-instruction function extent. The decompiled output expresses the same 0/1/2 rounding-result logic.

Other newly identified candidates at `0x00563E08`, `0x0056D15E`, and `0x0056D665` in `groove.exe`, and `0x2110D648` in `aal.dll`, were also exported by Ghidra. The two `0x56D...` entries are short C++ virtual methods identified during Radare2 vtable analysis.

This comparison does not prove that every machine-code function has been identified. The 753 exe and 8 DLL Ghidra-only starts still need triage; indirect callbacks and executable data sections also need separate auditing.

Raw Radare2 inventories are in `REVERSED/build/radare2_6.2.4_*_aaaa_reloc_aflj.json`; the row-by-row comparison is `REVERSED/build/radare2_ghidra_function_comparison_20261017.csv`.
