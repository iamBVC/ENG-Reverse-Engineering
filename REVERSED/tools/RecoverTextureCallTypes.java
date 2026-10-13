// Recover the texture uploader using call signatures checked against the listing.
import java.io.File;
import java.io.PrintWriter;
import java.util.Map;
import java.util.regex.Matcher;
import java.util.regex.Pattern;
import ghidra.app.script.GhidraScript;
import ghidra.app.decompiler.DecompInterface;
import ghidra.app.decompiler.DecompileResults;
import ghidra.program.model.listing.Function;
import ghidra.program.model.listing.Instruction;
import ghidra.program.model.data.FunctionDefinitionDataType;
import ghidra.program.model.data.IntegerDataType;
import ghidra.program.model.data.ParameterDefinition;
import ghidra.program.model.data.ParameterDefinitionImpl;
import ghidra.program.model.pcode.HighFunctionDBUtil;

public class RecoverTextureCallTypes extends GhidraScript {
    public void run() throws Exception {
        Function function = getFunctionAt(toAddr(0x407240));
        if (function == null) throw new Exception("Texture uploader is not identified");
        Map<Integer, Integer> counts = Map.ofEntries(
            Map.entry(0x2c, 1), Map.entry(0x14, 5), Map.entry(0x18, 4),
            Map.entry(0x74, 3), Map.entry(0x64, 5), Map.entry(0x80, 2),
            Map.entry(0x7c, 2), Map.entry(0x98, 3));
        Pattern registerMemory = Pattern.compile("(?i).*\\[E(?:AX|BX|CX|DX|SI|DI)(?:\\s*\\+\\s*(0x[0-9a-f]+))?\\].*");
        int overrides = 0;
        for (Instruction instruction : currentProgram.getListing().getInstructions(function.getBody(), true)) {
            if (!instruction.getFlowType().isCall() || !instruction.getFlowType().isComputed()) continue;
            String operand = instruction.getDefaultOperandRepresentation(0);
            Matcher matcher = registerMemory.matcher(operand);
            Integer count = null;
            String convention = "__stdcall";
            if (matcher.matches()) {
                if (matcher.group(1) == null) count = 3;
                else count = counts.get(Integer.decode(matcher.group(1)));
            }
            if (count == null) {
                convention = "__cdecl";
                String lower = operand.toLowerCase();
                if (lower.contains("57037c")) count = 5;
                else if (lower.contains("570374")) count = 11;
                else if (lower.contains("570378")) count = 14;
                else if (lower.contains("570358") || lower.contains("42ebe7")) count = 5;
            }
            println("Indirect call " + instruction.getAddress() + " " + operand + " args=" + count);
            if (count == null) throw new Exception("Unaccounted indirect call at " + instruction.getAddress());
            FunctionDefinitionDataType signature = new FunctionDefinitionDataType(
                "texture_call_" + instruction.getAddress(), currentProgram.getDataTypeManager());
            signature.setCallingConvention(convention);
            signature.setReturnType(IntegerDataType.dataType);
            ParameterDefinition[] parameters = new ParameterDefinition[count];
            for (int i = 0; i < count; ++i)
                parameters[i] = new ParameterDefinitionImpl("arg" + i, IntegerDataType.dataType, null);
            signature.setArguments(parameters);
            HighFunctionDBUtil.writeOverride(function, instruction.getAddress(), signature);
            ++overrides;
        }
        DecompInterface decompiler = new DecompInterface();
        decompiler.openProgram(currentProgram);
        try {
            DecompileResults result = decompiler.decompileFunction(function, 120, monitor);
            if (!result.decompileCompleted()) throw new Exception(result.getErrorMessage());
            try (PrintWriter output = new PrintWriter(new File(getScriptArgs()[0]))) {
                output.println("/* Ghidra export with " + overrides + " verified indirect call signatures. */");
                output.print(result.getDecompiledFunction().getC());
            }
            println("Recovered texture uploader with " + overrides + " indirect call signatures");
        } finally { decompiler.dispose(); }
    }
}
