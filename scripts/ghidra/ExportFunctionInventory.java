// Export the analyzed target's internal functions for the repository tracker.
// @category TH105

import ghidra.app.script.GhidraScript;
import ghidra.program.model.address.Address;
import ghidra.program.model.listing.Function;
import ghidra.program.model.listing.FunctionIterator;

import java.io.File;
import java.io.PrintWriter;
import java.nio.charset.StandardCharsets;

public class ExportFunctionInventory extends GhidraScript {
    private static String csv(String value) {
        if (value == null) {
            return "";
        }
        return "\"" + value.replace("\"", "\"\"").replace("\r", " ").replace("\n", " ") + "\"";
    }

    @Override
    protected void run() throws Exception {
        String[] args = getScriptArgs();
        if (args.length != 1) {
            throw new IllegalArgumentException("usage: ExportFunctionInventory.java <output.csv>");
        }

        File output = new File(args[0]).getCanonicalFile();
        File parent = output.getParentFile();
        if (parent != null) {
            parent.mkdirs();
        }

        int count = 0;
        try (PrintWriter writer = new PrintWriter(output, StandardCharsets.UTF_8)) {
            writer.println("address,size,span_end,current_name,calling_convention,signature,is_thunk");
            FunctionIterator functions = currentProgram.getFunctionManager().getFunctions(true);
            for (Function function : functions) {
                Address entry = function.getEntryPoint();
                if (!entry.isMemoryAddress() || !".text".equals(currentProgram.getMemory().getBlock(entry).getName())) {
                    continue;
                }
                long size = function.getBody().getNumAddresses();
                Address max = function.getBody().getMaxAddress();
                writer.printf(
                    "0x%08X,%d,0x%08X,%s,%s,%s,%s%n",
                    entry.getOffset(),
                    size,
                    max.getOffset(),
                    csv(function.getName(true)),
                    csv(function.getCallingConventionName()),
                    csv(function.getSignature().getPrototypeString()),
                    function.isThunk()
                );
                count++;
            }
        }
        println("Exported " + count + " internal .text functions to " + output);
    }
}
