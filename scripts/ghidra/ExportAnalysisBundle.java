// Export a reviewable, tool-neutral snapshot of the TH105 Ghidra analysis.
// This script is intentionally read-only and is run with -readOnly -noanalysis.
// @category TH105

import ghidra.app.script.GhidraScript;
import ghidra.framework.Application;
import ghidra.program.model.address.Address;
import ghidra.program.model.address.AddressIterator;
import ghidra.program.model.data.DataType;
import ghidra.program.model.data.DataTypeManager;
import ghidra.program.model.data.DataTypeWriter;
import ghidra.program.model.listing.CommentType;
import ghidra.program.model.listing.Data;
import ghidra.program.model.listing.DataIterator;
import ghidra.program.model.listing.Function;
import ghidra.program.model.listing.FunctionIterator;
import ghidra.program.model.listing.Listing;
import ghidra.program.model.mem.MemoryBlock;
import ghidra.program.model.symbol.SourceType;
import ghidra.program.model.symbol.Symbol;
import ghidra.program.model.symbol.SymbolIterator;

import java.io.BufferedWriter;
import java.io.File;
import java.io.FileWriter;
import java.io.PrintWriter;
import java.nio.charset.StandardCharsets;
import java.nio.file.Files;
import java.util.ArrayList;
import java.util.Iterator;
import java.util.List;
import java.util.Properties;

public class ExportAnalysisBundle extends GhidraScript {
    private static String csv(String value) {
        if (value == null) {
            return "";
        }
        return "\"" + value.replace("\"", "\"\"") + "\"";
    }

    private static String address(Address value) {
        return String.format("0x%08X", value.getOffset());
    }

    private boolean isMappedMemory(Address value) {
        return value != null && value.isMemoryAddress() && currentProgram.getMemory().contains(value);
    }

    private void exportFunctions(File directory) throws Exception {
        int count = 0;
        File output = new File(directory, "functions.csv");
        try (PrintWriter writer = new PrintWriter(output, StandardCharsets.UTF_8)) {
            writer.println("address,size,span_end,body_ranges,name,name_source,namespace,calling_convention,signature,signature_source,return_type,is_thunk,no_return,comment,repeatable_comment");
            FunctionIterator functions = currentProgram.getFunctionManager().getFunctions(true);
            for (Function function : functions) {
                Address entry = function.getEntryPoint();
                if (!isMappedMemory(entry)) {
                    continue;
                }
                List<String> ranges = new ArrayList<>();
                AddressIterator starts = function.getBody().getAddresses(true);
                Address runStart = null;
                Address previous = null;
                while (starts.hasNext()) {
                    Address next = starts.next();
                    if (runStart == null) {
                        runStart = next;
                    } else if (!next.equals(previous.next())) {
                        ranges.add(address(runStart) + "-" + address(previous));
                        runStart = next;
                    }
                    previous = next;
                }
                if (runStart != null) {
                    ranges.add(address(runStart) + "-" + address(previous));
                }
                writer.printf(
                    "%s,%d,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s%n",
                    address(entry),
                    function.getBody().getNumAddresses(),
                    address(function.getBody().getMaxAddress()),
                    csv(String.join(";", ranges)),
                    csv(function.getName()),
                    csv(function.getSymbol().getSource().name()),
                    csv(function.getParentNamespace().getName(true)),
                    csv(function.getCallingConventionName()),
                    csv(function.getSignature().getPrototypeString()),
                    csv(function.getSignatureSource().name()),
                    csv(function.getReturnType().getPathName()),
                    function.isThunk(),
                    function.hasNoReturn(),
                    csv(function.getComment()),
                    csv(function.getRepeatableComment())
                );
                count++;
            }
        }
        println("Exported " + count + " functions");
    }

    private void exportSymbols(File directory) throws Exception {
        int count = 0;
        File output = new File(directory, "symbols.csv");
        try (PrintWriter writer = new PrintWriter(output, StandardCharsets.UTF_8)) {
            writer.println("address,name,qualified_name,namespace,symbol_type,source,is_primary,is_external,is_dynamic");
            SymbolIterator symbols = currentProgram.getSymbolTable().getAllSymbols(true);
            while (symbols.hasNext()) {
                Symbol symbol = symbols.next();
                Address at = symbol.getAddress();
                if (!isMappedMemory(at) || symbol.getSource() == SourceType.DEFAULT) {
                    continue;
                }
                writer.printf(
                    "%s,%s,%s,%s,%s,%s,%s,%s,%s%n",
                    address(at),
                    csv(symbol.getName()),
                    csv(symbol.getName(true)),
                    csv(symbol.getParentNamespace().getName(true)),
                    csv(symbol.getSymbolType().toString()),
                    csv(symbol.getSource().name()),
                    symbol.isPrimary(),
                    symbol.isExternal(),
                    symbol.isDynamic()
                );
                count++;
            }
        }
        println("Exported " + count + " non-default memory symbols");
    }

    private void exportComments(File directory) throws Exception {
        int count = 0;
        File output = new File(directory, "comments.csv");
        Listing listing = currentProgram.getListing();
        try (PrintWriter writer = new PrintWriter(output, StandardCharsets.UTF_8)) {
            writer.println("address,comment_type,text");
            AddressIterator addresses = listing.getCommentAddressIterator(currentProgram.getMemory(), true);
            while (addresses.hasNext()) {
                Address at = addresses.next();
                for (CommentType type : CommentType.values()) {
                    String value = listing.getComment(type, at);
                    if (value == null || value.isBlank()) {
                        continue;
                    }
                    writer.printf("%s,%s,%s%n", address(at), csv(type.name()), csv(value));
                    count++;
                }
            }
        }
        println("Exported " + count + " comments");
    }

    private void exportDefinedData(File directory) throws Exception {
        int count = 0;
        File output = new File(directory, "defined-data.csv");
        DataIterator dataItems = currentProgram.getListing().getDefinedData(true);
        try (PrintWriter writer = new PrintWriter(output, StandardCharsets.UTF_8)) {
            writer.println("address,length,data_type_path,data_type_name,primary_symbol,value_repr");
            while (dataItems.hasNext()) {
                Data data = dataItems.next();
                Address at = data.getAddress();
                if (!isMappedMemory(at)) {
                    continue;
                }
                Symbol primary = currentProgram.getSymbolTable().getPrimarySymbol(at);
                Object value = data.getValue();
                writer.printf(
                    "%s,%d,%s,%s,%s,%s%n",
                    address(at),
                    data.getLength(),
                    csv(data.getDataType().getPathName()),
                    csv(data.getDataType().getName()),
                    csv(primary == null ? "" : primary.getName(true)),
                    csv(value == null ? "" : value.toString())
                );
                count++;
            }
        }
        println("Exported " + count + " defined data items");
    }

    private void exportDataTypes(File directory) throws Exception {
        DataTypeManager manager = currentProgram.getDataTypeManager();
        int count = 0;
        File inventory = new File(directory, "data-types.csv");
        List<DataType> types = new ArrayList<>();
        Iterator<DataType> iterator = manager.getAllDataTypes();
        try (PrintWriter writer = new PrintWriter(inventory, StandardCharsets.UTF_8)) {
            writer.println("path,name,category,class,length,description,source_archive");
            while (iterator.hasNext()) {
                DataType type = iterator.next();
                types.add(type);
                writer.printf(
                    "%s,%s,%s,%s,%d,%s,%s%n",
                    csv(type.getPathName()),
                    csv(type.getName()),
                    csv(type.getCategoryPath().getPath()),
                    csv(type.getClass().getSimpleName()),
                    type.getLength(),
                    csv(type.getDescription()),
                    csv(type.getSourceArchive() == null ? "" : type.getSourceArchive().getName())
                );
                count++;
            }
        }

        File header = new File(directory, "data-types.h");
        try (BufferedWriter writer = Files.newBufferedWriter(header.toPath(), StandardCharsets.UTF_8)) {
            DataTypeWriter typeWriter = new DataTypeWriter(manager, writer, true);
            typeWriter.write(types, monitor, true);
        }
        println("Exported " + count + " data types and C declarations");
    }

    private void exportMetadata(File directory) throws Exception {
        Properties properties = new Properties();
        properties.setProperty("schema", "th105-ghidra-analysis-bundle-v1");
        properties.setProperty("program_name", currentProgram.getName());
        properties.setProperty("executable_path", currentProgram.getExecutablePath());
        properties.setProperty("sha256", currentProgram.getExecutableSHA256());
        properties.setProperty("md5", currentProgram.getExecutableMD5());
        properties.setProperty("image_base", address(currentProgram.getImageBase()));
        properties.setProperty("language", currentProgram.getLanguageID().toString());
        properties.setProperty("compiler_spec", currentProgram.getCompilerSpec().getCompilerSpecID().toString());
        properties.setProperty("ghidra_version", Application.getApplicationVersion());
        StringBuilder blocks = new StringBuilder();
        for (MemoryBlock block : currentProgram.getMemory().getBlocks()) {
            if (blocks.length() != 0) {
                blocks.append(';');
            }
            blocks.append(block.getName()).append(':').append(address(block.getStart()))
                .append('-').append(address(block.getEnd()));
        }
        properties.setProperty("memory_blocks", blocks.toString());
        File output = new File(directory, "export-metadata.properties");
        try (FileWriter writer = new FileWriter(output, StandardCharsets.UTF_8)) {
            properties.store(writer, "generated by ExportAnalysisBundle.java");
        }
    }

    @Override
    protected void run() throws Exception {
        String[] args = getScriptArgs();
        if (args.length != 1) {
            throw new IllegalArgumentException("usage: ExportAnalysisBundle.java <output-directory>");
        }
        File directory = new File(args[0]).getCanonicalFile();
        Files.createDirectories(directory.toPath());
        exportMetadata(directory);
        exportFunctions(directory);
        exportSymbols(directory);
        exportComments(directory);
        exportDefinedData(directory);
        exportDataTypes(directory);
        println("Analysis bundle payload exported to " + directory);
    }
}
