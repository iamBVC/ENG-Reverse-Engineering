// Read-only address-level disassembly dump for a saved Ghidra program.
import ghidra.app.script.GhidraScript;
import ghidra.program.model.listing.Function;
import ghidra.program.model.listing.Instruction;
import java.security.MessageDigest;

public class DumpFunctionInstructions extends GhidraScript {
    @Override
    public void run() throws Exception {
        for (String raw : getScriptArgs()) {
            long offset = Long.decode(raw);
            Function function = getFunctionAt(toAddr(offset));
            println("=== " + raw + " " + (function == null ? "NO_FUNCTION" : function.getName())
                    + " ===");
            if (function == null) {
                continue;
            }
            println("body_bytes=" + function.getBody().getNumAddresses());
            byte[] bodyBytes = new byte[(int) function.getBody().getNumAddresses()];
            currentProgram.getMemory().getBytes(function.getBody().getMinAddress(), bodyBytes);
            byte[] digest = MessageDigest.getInstance("SHA-256").digest(bodyBytes);
            StringBuilder hash = new StringBuilder();
            for (byte value : digest) {
                hash.append(String.format("%02x", value & 0xff));
            }
            println("body_sha256=" + hash);
            for (Instruction instruction : currentProgram.getListing()
                    .getInstructions(function.getBody(), true)) {
                byte[] bytes = instruction.getBytes();
                StringBuilder encoded = new StringBuilder();
                for (byte value : bytes) {
                    encoded.append(String.format("%02x", value & 0xff));
                }
                println(instruction.getAddress() + "  " + encoded + "  " + instruction);
            }
        }
    }
}
