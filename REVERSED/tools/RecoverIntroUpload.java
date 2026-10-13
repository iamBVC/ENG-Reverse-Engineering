// Recover the intro pixel uploader after correcting native surface call ABIs.
import java.io.File;
import java.io.PrintWriter;
import ghidra.app.script.GhidraScript;
import ghidra.app.decompiler.DecompInterface;
import ghidra.app.decompiler.DecompileResults;
import ghidra.program.model.listing.Function;
import ghidra.program.model.listing.Instruction;
import ghidra.program.model.data.*;
import ghidra.program.model.pcode.HighFunctionDBUtil;

public class RecoverIntroUpload extends GhidraScript {
    public void run() throws Exception {
        Function function = getFunctionAt(toAddr(0x43b080));
        int overrides = 0;
        for (Instruction instruction : currentProgram.getListing().getInstructions(function.getBody(), true)) {
            if (!instruction.getFlowType().isCall() || !instruction.getFlowType().isComputed()) continue;
            String operand = instruction.getDefaultOperandRepresentation(0).toLowerCase();
            int count;
            if (operand.contains("0x64")) count = 5;
            else if (operand.contains("0x80")) count = 2;
            else throw new Exception("Unknown surface call " + operand);
            FunctionDefinitionDataType signature = new FunctionDefinitionDataType(
                "intro_call_" + instruction.getAddress(), currentProgram.getDataTypeManager());
            signature.setCallingConvention("__stdcall");
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
                output.println("/* Original intro uploader with verified native Lock/Unlock ABIs. */");
                output.print(result.getDecompiledFunction().getC());
            }
            println("Recovered intro uploader: " + overrides + " surface calls");
        } finally { decompiler.dispose(); }
    }
}
