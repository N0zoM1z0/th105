# Original CRT debugger and initialization entries

Three whole runtime bodies are now canonical and inventory-unique:
-690987/8: __crt_debugger_hook from dbghook.obj.
-695025/14: ___CxxSetUnhandledExceptionFilter from unhandld.obj.
-69C9D8/13: ___sse2_available_init from cpu_disp.obj.

Only35 new runtime bytes are classified. No game implementation, assembly,
register facade, native-byte implementation or generic branch waiver is added.
All selected code comes from unchanged, hash-pinned original archive members.

## Debugger hook, not heap-handler initialization

The eight-byte function clears the actual __debugger_hook_dummy common word
at7039CC and returns. The original COFF definition is section0/value4/type0,
external storage class2 with no auxiliary record; the native word is PE virtual
zero-fill. No raw BSS bytes are read or invented.

Adjacency to __callnewh does not establish heap-handler identity. The actual
handler.obj __initp_heap_handler is a different10-byte function and references
a different encoded handler variable. That earlier naming hypothesis is
rejected, not treated as compiler/patch mismatch or forced into this body.
The vendor debugger-hook dummy is retained as original runtime provenance;
no inert storage is introduced into reconstructed game source.

## SSE query and exception callback

The SSE initializer calls the complete original96-byte __get_sse2_info and
stores its result in the actual four-byte ___sse2_available common allocation
at7039C8, then returns zero. Every byte of the96-byte query is also compared.
Its existing _has_osfxsr_set provider remains the separately classified80-byte
runtime function; no new remote SEH proof or credit is claimed for that helper.

The exception-filter registration passes the actual complete61-byte
__CxxUnhandledExceptionFilter to the verified KERNEL32 SetUnhandledExceptionFilter
import at6C0154, then returns zero. The callback is fully canonical with its
original terminate call at68FC12. Native import-descriptor identity, complete
IAT word and the typed source function-pointer relocation are all checked.
The existing terminate provider receives no new implementation/EH credit.

## Actual C initialization protocol

The original32-byte __initterm_e array walker matches in full. A separate
complete15-byte source/native __cinit call site at68E2A9 passes the real start
6C039C and end6C03B8. The whole32-byte native range including both sentinels
is checked. Its six callbacks include the two selected entries exactly once:
6C03B0 points to69C9D8 and6C03B4 points to695025.

The cpu_disp.obj _pinit record is the actual readonly .CRT$XIC contribution;
wincrt0.obj provides a readonly .CRT$XIY registration witness for the Cxx entry.
Both are complete zero-addend DIR32 records. Equivalent registration records
also occur in other original startup variants, so this pointer witness does
not uniquely identify the linked startup object or prove its entire code.
Only the named call site is newly checked in __cinit, not its whole body.

Non-selected C-table entries retain their existing runtime classifications.
In particular, the existing stdio-initializer evidence uses its KB provider;
this is not a claim that all callbacks or the whole executable share one patch
version. Other initializers, C++ tables, startup code and remote EH metadata
receive no new credit.

## Validation

All three public units freshly compare complete selected bodies. Thirteen
tests cover source-family/field identity, missing/short/masked entries, the
actual callback/query roles, readonly source records, zero addends and C versus
C++ registration sections. All275 actual initialized-byte corruption controls
fail:35 root bytes,189 support bytes,15 caller bytes,32 native table bytes and
four IAT bytes. Common/BSS words are proved structurally, not counted as raw
byte mutation cases.

Original member hashes and all source/native comparisons are retained in
build/origin-anchors/vc8-control-entries/proof.json. Private discovery and
mutation evidence is under build/frontier-crt-initializers-20261101/ and
.analysis/frontier-crt-control-entries-20261101/.
Authored exact/source counts remain unchanged.
