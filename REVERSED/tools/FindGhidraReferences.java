import ghidra.app.script.GhidraScript;
import ghidra.program.model.address.Address;
import ghidra.program.model.listing.Function;
import ghidra.program.model.symbol.Reference;
import ghidra.program.model.symbol.ReferenceIterator;

/** Print code/data xrefs for addresses supplied as hexadecimal script arguments. */
public class FindGhidraReferences extends GhidraScript {
    @Override
    protected void run() throws Exception {
        for (String argument : getScriptArgs()) {
            String value = argument.startsWith("0x") || argument.startsWith("0X")
                ? argument.substring(2) : argument;
            Address target = toAddr(Long.parseUnsignedLong(value, 16));
            println("=== references to " + target + " ===");
            ReferenceIterator references = currentProgram.getReferenceManager().getReferencesTo(target);
            int count = 0;
            while (references.hasNext()) {
                Reference reference = references.next();
                Function owner = currentProgram.getFunctionManager().getFunctionContaining(
                    reference.getFromAddress());
                println(reference.getFromAddress() + " " + reference.getReferenceType()
                    + " in " + (owner == null ? "<no function>" : owner.getName()));
                count++;
            }
            println("count=" + count);
        }
    }
}
