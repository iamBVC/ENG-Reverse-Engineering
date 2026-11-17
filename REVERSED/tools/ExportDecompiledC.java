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
import java.util.HashMap;
import java.util.Locale;
import java.util.Map;

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
    private final Map<Long, String> exportNames = new HashMap<>();

    @Override
    public void run() throws Exception {
        String[] args = getScriptArgs();
        File outDir = new File(args.length > 0 ? args[0] : ".");
        if (!outDir.exists() && !outDir.mkdirs()) {
            throw new RuntimeException("cannot create " + outDir);
        }

        // ---- 1. give every internal function a unique source name --------
        Map<String, Integer> internalNameCounts = new HashMap<>();
        for (Function f : currentProgram.getFunctionManager().getFunctions(true)) {
            if (!f.isExternal()) {
                String name = f.getName();
                internalNameCounts.put(name, internalNameCounts.getOrDefault(name, 0) + 1);
            }
        }
        int renamed = 0;
        for (Function f : currentProgram.getFunctionManager().getFunctions(true)) {
            String name = f.getName();
            boolean duplicateInternalName = !f.isExternal()
                    && internalNameCounts.getOrDefault(name, 0) > 1;
            String exportName = name;
            if (name.startsWith("FUN_") || duplicateInternalName) {
                String hex = String.format(Locale.ROOT, "%06X", f.getEntryPoint().getOffset());
                String uniqueName = "sub_" + hex;
                exportName = uniqueName;
                if (name.equals(uniqueName)) {
                    exportNames.put(f.getEntryPoint().getOffset(), exportName);
                    continue;
                }
                try {
                    f.setName(uniqueName, SourceType.USER_DEFINED);
                    renamed++;
                }
                catch (Exception e) {
                    throw new RuntimeException("could not assign unique name " + uniqueName
                                               + " to " + f.getEntryPoint(), e);
                }
            }
            exportNames.put(f.getEntryPoint().getOffset(), exportName);
        }
        println("renamed " + renamed + " default or colliding names to sub_<addr>");

        // ---- 1b. create the functions only a data table points at ----
        // An address that is only ever *referenced as a value* is not a function as far
        // as Ghidra's analysis is concerned, so it has no body to decompile - which is
        // why `tools/gen_crt_initialisers.py` reads the initialiser tables out of the
        // executable and this step turns each entry into a real function.  The tables
        // are `_initterm(0x570000,0x570260)` and `_initterm(0x570264,0x570278)`, called
        // from `_cinit` at 0x563B87; the same route will take any other list of
        // "address used as a value but never called directly" (the WndProc at 0x41DDA0
        // is the next one).
        File listFile = new File(args.length > 1 ? args[1] : "");
        int created = 0;
        if (listFile.exists()) {
            try (java.io.BufferedReader r = new java.io.BufferedReader(new java.io.FileReader(listFile))) {
                String line;
                while ((line = r.readLine()) != null) {
                    line = line.trim();
                    if (line.isEmpty() || line.startsWith("#")) {
                        continue;
                    }
                    long va = Long.parseLong(line.startsWith("0x") ? line.substring(2) : line, 16);
                    ghidra.program.model.address.Address a = toAddr(va);
                    if (getFunctionAt(a) != null) {
                        continue;
                    }
                    try {
                        Function f = createFunction(a, String.format("sub_%06X", va));
                        if (f != null) {
                            // Ghidra auto-names a 5-byte `jmp` a thunk (`thunk_FUN_00402760`),
                            // which would also change the exported file's name; the rebuild
                            // keys everything by `sub_<addr>`, so force it.
                            if (!f.getName().equals(String.format("sub_%06X", va))) {
                                try {
                                    f.setName(String.format("sub_%06X", va), SourceType.USER_DEFINED);
                                }
                                catch (Exception e) {
                                    println("could not rename " + f.getName() + ": " + e);
                                }
                            }
                            exportNames.put(f.getEntryPoint().getOffset(),
                                            String.format("sub_%06X", va));
                            created++;
                        }
                    }
                    catch (Exception e) {
                        println("could not create a function at " + line + ": " + e);
                    }
                }
            }
            println("created " + created + " functions from " + listFile);
        }

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
        index.println("name,address,size,status,file");

        for (Function f : currentProgram.getFunctionManager().getFunctions(true)) {
            String name = exportName(f);
            String address = f.getEntryPoint().toString();
            String fileName = String.format(Locale.ROOT, "sub_%08X.c",
                                             f.getEntryPoint().getOffset());
            String status = "fail";
            try {
                // These two 150 KB functions exceed Ghidra's normal timeout by
                // design. Give them a bounded, longer budget without slowing
                // down the remaining 1,347 functions.
                int timeoutSeconds = (address.equalsIgnoreCase("00447770")
                                      || address.equalsIgnoreCase("004CB870"))
                                     ? 900 : 120;
                String source = renderZeroArgumentThunk(f);
                if (source == null) {
                    DecompileResults res = dec.decompileFunction(f, timeoutSeconds, monitor);
                    if (res != null && res.decompileCompleted()) {
                        DecompiledFunction df = res.getDecompiledFunction();
                        if (df != null) {
                            source = df.getC();
                        }
                    }
                }
                if (source != null) {
                    try (PrintWriter w = new PrintWriter(new File(outDir, fileName))) {
                        w.println("/* " + name + " @ " + f.getEntryPoint()
                                  + "   " + f.getBody().getNumAddresses() + " bytes */");
                        w.print(source);
                    }
                    ok++;
                    status = "ok";
                }
            }
            catch (Exception e) {
                println("  !! " + name + ": " + e.getMessage());
            }
            if ("fail".equals(status)) {
                println("  !! decompilation failed for " + name + " @ " + address
                        + " (timeout "
                        + ((address.equalsIgnoreCase("00447770")
                            || address.equalsIgnoreCase("004CB870")) ? 900 : 120)
                        + " seconds)");
            }
            if ("fail".equals(status)) {
                failed++;
            }
            index.println(name + "," + address + ","
                          + f.getBody().getNumAddresses() + "," + status + ","
                          + fileName);
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

    private String exportName(Function function) {
        return exportNames.getOrDefault(function.getEntryPoint().getOffset(), function.getName());
    }

    private String renderZeroArgumentThunk(Function function) {
        if (!function.isThunk() || function.getParameterCount() != 0) {
            return null;
        }
        Function target = function.getThunkedFunction(false);
        if (target == null || target.getParameterCount() != 0) {
            return null;
        }

        String prototype = function.getPrototypeString(false, false);
        String functionName = exportName(function);
        String targetName = exportName(target);
        if (!functionName.equals(function.getName())) {
            prototype = prototype.replaceFirst("\\b" + java.util.regex.Pattern.quote(function.getName())
                                               + "\\b", java.util.regex.Matcher.quoteReplacement(functionName));
        }
        if (prototype.endsWith("()")) {
            prototype = prototype.substring(0, prototype.length() - 2) + "(void)";
        }
        boolean returnsVoid = "void".equals(function.getReturnType().getName());
        return prototype + "\n{\n  " + (returnsVoid ? "" : "return ")
                + targetName + "();\n}\n";
    }
}
