# Script/file-buffer array ownership and parser registration

## Correct source allocation families

The reconstruction previously paired new[] with free in the script-prefix
temporary and FileBufferContext's destructor/replacement paths. Those four
source sites now use delete[] with the actual array element type. This corrects
the reconstruction source; it is not a claim that the original game had this
ownership defect.

The native allocation/deallocation chain is already independently identified:
array new at 665B8A forwards to scalar operator new 689DCB; array delete 68AA26
forwards to scalar delete 6898EA, then CRT free 68C686. The original source
already allocates char[] or unsigned char[] and retains the target's explicit
null guard where present. No allocator replacement, synthetic wrapper, defensive
cleanup branch, changed exception policy or forced ABI is introduced.

Only four function-scoped bindings in exact-first-csv-file-loading change from
the old free spelling to the actual emitted array-delete symbol. Unchanged
separate bitmap/SFL buffer implementations keep their existing bindings; no
blanket remap is applied across unrelated functions.

Actual dependency discovery finds two affected units:
exact-first-csv-file-loading and exact-first-bgm-stream-runtime.
Fresh canonical replay preserves all 12 accepted CSV/script/reader/texture
functions and both accepted BGM functions (14 total), including their complete
selected cleanup-EH witnesses. This is focused regression evidence, not an
all-unit corpus or runtime game test.

## Existing complete parser source is now tracked

The existing real parser in ScriptFileLoading.cpp already participates in
the accepted CScript loader's source graph, but lacked a source/ownership
ledger row. It is now registered as authored, nonexact source.

Native [405930,405ABF) is 399 bytes / 137 instructions, ending in RET8 at405ABC.
Whole native SHA-256:
dd534e8474d97ae97348bdcc0189d47ed643b55c98635446df715eec4ad4ecc9.
The exact CScript loader405810 calls it at4058C7.

A colon triggers factory-key lookup. The key ends at the first earlier space
if present, otherwise at the colon. A temporary char array receives that
prefix, a real std::string supplies the checked-map key, then the array is
deleted after the string temporary's lifetime. A found factory creates a
command and parses only the text after the colon. Otherwise the optional
default factory creates a command and parses the entire original line.
The returned command is appended to the owned command-pointer deque.
No new token trimming, missing-factory error or exception cleanup is invented.

The full linked source remains 405 bytes versus399 native. Explicit real
callee bindings now describe its array allocation/deletion and actual map/
string/deque operations. Public exact replay still lacks a supported cleanup
contract for this ordinary free stdcall function. The member-cleanup contract
was not widened, and no fabricated member ABI or global-lifetime witness was
introduced merely to obtain a comparison. Native handler6BDF48, FuncInfo6E45EC
and one string cleanup at6BDF40 were inspected only as bounded evidence.
The parser is neither exact nor promoted by its exact caller.

## Verification and accounting

Fresh accepted receipts:
build/frontier-script-parser-lifetime-20261031/final-csv-accepted.json
and final-bgm-accepted.json. The affected-unit list, native parser facts and
intermediate diagnostics are retained in the same private build scope.

Only the new parser authored-origin row is materialized; its whole hash and
exact-caller edge pass the normal validator. No existing accepted function
or byte count changes. Source 1,752; authored ownership 1,772; mapped1,779;
review615; exclusions1,640; match units745. Exact remains1,553 /441,679 bytes.

## Shared enqueue control, 2026-11-10

Native 405A78 joins the default-factory path at one enqueue block, 405A9C.
Two bounded source controls tested that ordinary command-pointer lifetime:
moving the declaration outside both branches emits 413 bytes, and joining both
successful parse paths at one enqueue block emits 410 bytes. Neither reproduces
the complete 399-byte native function; both retain a stack-aligned frame absent
from native. The original 405-byte source was restored rather than selecting
an unproven spelling improvement. The existing free-stdcall EH comparison
boundary remains unchanged.

Fresh restoration builds retain all 14 currently registered exact roots in the
linked unit. Receipts and both rejected source controls are under
`build/frontier-script-line-control-20261110/` and its matching private analysis
scope. No shared input, comparison contract, source pin or exact ledger changed.
