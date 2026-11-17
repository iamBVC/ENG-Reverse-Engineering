// Use Ghidra's disassembler to inspect candidate function starts that the
// saved project has not yet identified. Intended for a disposable project copy.
import ghidra.app.script.GhidraScript;
import ghidra.program.model.address.Address;
import ghidra.program.model.listing.Function;
import ghidra.program.model.listing.Instruction;

public class CreateAndDumpFunction extends GhidraScript {
    @Override
    public void run() throws Exception {
        for (String raw : getScriptArgs()) {
            Address start = toAddr(Long.decode(raw));
            Instruction first = currentProgram.getListing().getInstructionAt(start);
            if (first == null) {
                disassemble(start);
                first = currentProgram.getListing().getInstructionAt(start);
            }
            Function function = getFunctionAt(start);
            if (function == null && first != null) {
                function = createFunction(start, null);
            }
            println("=== " + raw + " " + (function == null ? "NO_FUNCTION" : function.getName()) + " ===");
            if (function == null) {
                continue;
            }
            println("body_bytes=" + function.getBody().getNumAddresses());
            for (Instruction instruction : currentProgram.getListing()
                    .getInstructions(function.getBody(), true)) {
                println(instruction.getAddress() + "  " + instruction);
            }
        }
    }
}
