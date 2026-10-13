// Targeted recovery of functions referenced by original executable data tables.
import java.io.File;
import java.io.PrintWriter;
import java.nio.file.Files;
import ghidra.app.decompiler.DecompInterface;
import ghidra.app.decompiler.DecompileResults;
import ghidra.app.script.GhidraScript;
import ghidra.program.model.address.Address;
import ghidra.program.model.listing.Function;
import ghidra.program.model.symbol.SourceType;

public class ExportSelectedFunctions extends GhidraScript {
    @Override
    public void run() throws Exception {
        String[] args = getScriptArgs();
        File output = new File(args[0]);
        output.mkdirs();
        // Rename existing functions so call sites retain the rebuild's naming.
        for (Function f : currentProgram.getFunctionManager().getFunctions(true)) {
            if (f.getName().startsWith("FUN_"))
                f.setName(String.format("sub_%06X", f.getEntryPoint().getOffset()), SourceType.USER_DEFINED);
        }
        DecompInterface decompiler = new DecompInterface();
        decompiler.openProgram(currentProgram);
        try {
            for (String line : Files.readAllLines(new File(args[1]).toPath())) {
                line = line.trim();
                if (line.isEmpty() || line.startsWith("#")) continue;
                long value = Long.parseLong(line.replaceFirst("^0x", ""), 16);
                Address address = toAddr(value);
                String name = String.format("sub_%06X", value);
                Function function = getFunctionAt(address);
                if (function == null) function = createFunction(address, name);
                if (function == null) {
                    println("FAILED " + name + ": cannot create function");
                    continue;
                }
                function.setName(name, SourceType.USER_DEFINED);
                decompiler.flushCache();
                DecompileResults result = decompiler.decompileFunction(function, 60, monitor);
                if (!result.decompileCompleted() || result.getDecompiledFunction() == null) {
                    println("FAILED " + name + ": " + result.getErrorMessage());
                    continue;
                }
                try (PrintWriter writer = new PrintWriter(new File(output, name + ".c"))) {
                    writer.println("/* Selected Ghidra export at " + address + ". */");
                    writer.print(result.getDecompiledFunction().getC());
                }
                println("Exported " + name);
            }
        } finally {
            decompiler.dispose();
        }
    }
}
