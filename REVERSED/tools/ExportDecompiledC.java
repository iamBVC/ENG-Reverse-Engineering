// ExportDecompiledC.java - Ghidra headless script for the groove.exe rebuild.
//
// Run through tools/ghidra_decompile.bat.  It does two things:
//   1. renames every default-named function (FUN_00401000) to sub_<addr>, so the
//      decompiled C lines up with the IDA listing and REVERSED/functions.csv;
//   2. decompiles every function and writes one .c file per function into the
//      output directory, plus an _index.csv with the status of each one.
//
// Kept in Java on purpose: Ghidra 12 ships PyGhidra (needs a matching CPython)
// and dropping Jython, so a plain GhidraScript is the version-proof choice.

import java.io.File;
import java.io.PrintWriter;

import ghidra.app.decompiler.DecompInterface;
import ghidra.app.decompiler.DecompileResults;
import ghidra.app.decompiler.DecompiledFunction;
import ghidra.app.script.GhidraScript;
import ghidra.program.model.data.DataType;
import ghidra.program.model.listing.Data;
import ghidra.program.model.listing.Function;
import ghidra.program.model.symbol.SourceType;
import ghidra.program.model.symbol.Symbol;
import ghidra.program.model.symbol.SymbolIterator;

public class ExportDecompiledC extends GhidraScript {

    @Override
    public void run() throws Exception {
        String[] args = getScriptArgs();
        File outDir = new File(args.length > 0 ? args[0] : ".");
        if (!outDir.exists() && !outDir.mkdirs()) {
            throw new RuntimeException("cannot create " + outDir);
        }

        // ---- 1. rename FUN_xxxxxx -> sub_xxxxxx -------------------------
        int renamed = 0;
        for (Function f : currentProgram.getFunctionManager().getFunctions(true)) {
            String name = f.getName();
            if (name.startsWith("FUN_")) {
                String hex = Long.toHexString(f.getEntryPoint().getOffset()).toUpperCase();
                try {
                    f.setName("sub_" + hex, SourceType.USER_DEFINED);
                    renamed++;
                }
                catch (Exception e) {
                    // duplicate or invalid name: leave it alone
                }
            }
        }
        println("renamed " + renamed + " functions to sub_<addr>");

        // ---- 2. decompile everything ------------------------------------
        DecompInterface dec = new DecompInterface();
        dec.toggleCCode(true);
        dec.toggleSyntaxTree(false);
        if (!dec.openProgram(currentProgram)) {
            throw new RuntimeException("decompiler would not open the program");
        }

        int ok = 0;
        int failed = 0;
        PrintWriter index = new PrintWriter(new File(outDir, "_index.csv"));
        index.println("name,address,size,status");

        for (Function f : currentProgram.getFunctionManager().getFunctions(true)) {
            String name = f.getName();
            String status = "fail";
            try {
                DecompileResults res = dec.decompileFunction(f, 120, monitor);
                if (res != null && res.decompileCompleted()) {
                    DecompiledFunction df = res.getDecompiledFunction();
                    if (df != null && df.getC() != null) {
                        PrintWriter w = new PrintWriter(new File(outDir, name + ".c"));
                        w.println("/* " + name + " @ " + f.getEntryPoint()
                                  + "   " + f.getBody().getNumAddresses() + " bytes */");
                        w.print(df.getC());
                        w.close();
                        ok++;
                        status = "ok";
                    }
                }
            }
            catch (Exception e) {
                println("  !! " + name + ": " + e.getMessage());
            }
            if ("fail".equals(status)) {
                failed++;
            }
            index.println(name + "," + f.getEntryPoint() + ","
                          + f.getBody().getNumAddresses() + "," + status);
        }
        index.close();
        dec.dispose();

        // ---- 3. function signatures + data symbol inventory ---------------
        // These drive tools/make_bulk.py, which generates the prototypes and the
        // DAT_/UNK_ global definitions the decompiled C references.
        PrintWriter fns = new PrintWriter(new File(outDir, "_functions.csv"));
        fns.println("name,address,size,signature");
        for (Function f : currentProgram.getFunctionManager().getFunctions(true)) {
            String proto = f.getPrototypeString(false, false);
            proto = proto.replace(',', ';');
            fns.println(f.getName() + "," + f.getEntryPoint() + ","
                        + f.getBody().getNumAddresses() + "," + proto);
        }
        fns.close();

        PrintWriter dat = new PrintWriter(new File(outDir, "_data.csv"));
        dat.println("name,address,size,datatype");
        SymbolIterator it = currentProgram.getSymbolTable().getAllSymbols(true);
        int dataCount = 0;
        while (it.hasNext()) {
            Symbol s = it.next();
            if (!s.isExternal() && s.getSymbolType().toString().equals("Label")
                && !s.isPrimary()) {
                continue;
            }
            String n = s.getName();
            boolean interesting = n.startsWith("DAT_") || n.startsWith("UNK_")
                                  || n.startsWith("PTR_") || n.startsWith("s_")
                                  || n.startsWith("uRam") || n.startsWith("off_")
                                  || n.startsWith("a") || n.startsWith("flt_")
                                  || n.startsWith("dbl_") || n.startsWith("byte_")
                                  || n.startsWith("word_") || n.startsWith("dword_");
            if (!interesting) {
                continue;
            }
            long size = 1;
            Data d = getDataAt(s.getAddress());
            if (d != null) {
                size = d.getLength();
            }
            DataType dt = d == null ? null : d.getDataType();
            dat.println(n + "," + s.getAddress() + "," + size + ","
                        + (dt == null ? "undefined" : dt.getName()));
            dataCount++;
        }
        dat.close();
        println("wrote " + dataCount + " data symbols to _data.csv");
        println("decompiled ok=" + ok + " failed=" + failed + " into " + outDir);
    }
}
