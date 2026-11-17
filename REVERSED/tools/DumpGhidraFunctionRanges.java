import java.util.Iterator;

import ghidra.app.script.GhidraScript;
import ghidra.program.model.address.Address;
import ghidra.program.model.address.AddressRange;
import ghidra.program.model.address.AddressSetView;
import ghidra.program.model.listing.Function;

public class DumpGhidraFunctionRanges extends GhidraScript {
    @Override
    public void run() throws Exception {
        String[] args = getScriptArgs();
        if (args.length == 0) {
            throw new IllegalArgumentException("Pass one or more function entry addresses");
        }

        println("entry,name,body_bytes,range_min,range_max");
        for (String argument : args) {
          for (String value : argument.split(",")) {
            long offset = Long.parseLong(value.trim().replaceFirst("^0[xX]", ""), 16);
            Address entry = toAddr(offset);
            Function function = currentProgram.getFunctionManager().getFunctionAt(entry);
            if (function == null) {
                println(String.format("0x%08x,<no_function>,0,,,", offset));
                continue;
            }

            AddressSetView body = function.getBody();
            Iterator<AddressRange> ranges = body.getAddressRanges();
            while (ranges.hasNext()) {
                AddressRange range = ranges.next();
                println(String.format("%s,%s,%d,%s,%s",
                    entry, function.getName(), body.getNumAddresses(),
                    range.getMinAddress(), range.getMaxAddress()));
            }
          }
        }
    }
}
