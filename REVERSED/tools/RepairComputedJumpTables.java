// Restore known indirect-jump destinations in the two renderer functions.
// Input rows are: function-entry,branch-address,target-address,target-address,...
import java.io.File;
import java.nio.file.Files;
import java.util.ArrayList;
import java.util.Arrays;

import ghidra.app.script.GhidraScript;
import ghidra.program.model.address.AddressSet;
import ghidra.program.model.address.Address;
import ghidra.program.model.listing.Function;
import ghidra.program.model.listing.Instruction;
import ghidra.program.model.pcode.JumpTable;
import ghidra.program.model.symbol.RefType;
import ghidra.program.model.symbol.Reference;
import ghidra.program.model.symbol.SourceType;

public class RepairComputedJumpTables extends GhidraScript {
    @Override
    public void run() throws Exception {
        if (getScriptArgs().length != 1) {
            throw new IllegalArgumentException("expected path to branch,target CSV rows");
        }

        int repaired = 0;
        for (String raw : Files.readAllLines(new File(getScriptArgs()[0]).toPath())) {
            String line = raw.trim();
            if (line.isEmpty() || line.startsWith("#")) continue;

            String[] fields = line.split(",");
            if (fields.length < 3) throw new IllegalArgumentException("bad row: " + line);
            Address entry = toAddr(Long.parseLong(fields[0].trim(), 16));
            Address branch = toAddr(Long.parseLong(fields[1].trim(), 16));
            Instruction instruction = currentProgram.getListing().getInstructionAt(branch);
            if (instruction == null || !instruction.getFlowType().isJump()
                    || !instruction.getFlowType().isComputed()) {
                throw new IllegalStateException("not a computed jump: " + branch);
            }

            Function function = currentProgram.getFunctionManager().getFunctionAt(entry);
            if (function == null) throw new IllegalStateException("no function at entry: " + entry);

            ArrayList<Address> targets = new ArrayList<Address>();
            AddressSet repairedBody = new AddressSet(function.getBody());
            repairedBody.add(instruction.getMinAddress(), instruction.getMaxAddress());
            for (int i = 2; i < fields.length; i++) {
                Address target = toAddr(Long.parseLong(fields[i].trim(), 16));
                Instruction targetInstruction = currentProgram.getListing().getInstructionAt(target);
                if (targetInstruction == null) {
                    throw new IllegalStateException("target is not an instruction: " + target);
                }
                Function targetOwner = getFunctionContaining(target);
                if (targetOwner != null && !targetOwner.equals(function)) {
                    throw new IllegalStateException("target belongs to another function: " + target);
                }
                targets.add(target);
                repairedBody.add(targetInstruction.getMinAddress(), targetInstruction.getMaxAddress());
                boolean exists = false;
                for (Reference reference : instruction.getReferencesFrom()) {
                    if (reference.getToAddress().equals(target)
                            && reference.getReferenceType().isJump()) {
                        exists = true;
                        break;
                    }
                }
                if (!exists) {
                    instruction.addOperandReference(0, target, RefType.COMPUTED_JUMP,
                            SourceType.USER_DEFINED);
                }
            }

            function.setBody(repairedBody);
            new JumpTable(branch, targets, true, 0).writeOverride(function);
            if (!function.getBody().contains(branch)) {
                throw new IllegalStateException("branch missing from repaired body: " + branch);
            }
            for (Address target : targets) {
                if (!function.getBody().contains(target)) {
                    throw new IllegalStateException("function body was not repaired at target: " + target);
                }
            }
            repaired++;
            println("Restored " + function.getName() + " " + branch + " -> "
                    + Arrays.toString(targets.toArray()));
        }
        println("Computed jump tables restored: " + repaired);
    }
}
