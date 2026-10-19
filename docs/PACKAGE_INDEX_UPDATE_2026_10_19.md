# Package-index registration, 2026-10-19

## Observed target and ownership

Original Japanese1.06a SHA256 is
`56350024879199861579c11b0e1c67b9590e10a8d40cd5996b109deec9afca7e`.
`register_package_file_entry @41BCF0` has a closed628-byte span
`[41BCF0,41BF64)`, SHA256
`77497a2c590e14e4446a36cccd205db724449d36263b01e26a3f05a2fa6a2257`.
All200 decoded instructions are reachable; direct branches stay on internal
instruction starts and the sole normal exit is RET16 at41BF61. The four
stack arguments are filename, archive index, entry size and entry offset.
The caller at41BA70:41BC9D supplies these from its archive-entry parsing loop.
Only this incoming CALL was found in both candidate decoding and a complete
raw `.text` E8-lead scan. The caller's full loader semantics remain unreviewed.

The root is game archive policy around the same container702908 used by
`open_package_file_entry @41BFA0`. It hashes the filename with exact406930 and
finds its unsigned key. A missing key inserts a fresh value. An existing key
always compares filenames, including a singleton; it updates the three
scalar fields on a case-insensitive match or appends a newly owned node on a
collision-chain miss. It leaves stored path spelling unchanged on an update.
No lock or concurrency protection occurs in this root.

Direct Ghidra input hash/base/entry/language/compiler, full mapped `.text` and
root bytes were independently attested before analysis. Observed private
callee storage was applied only as temporary analysis metadata and read back.
The decompilation was checked against raw instructions. All nine primary DB
hashes stayed unchanged and read-only aliases were removed. IDA remains
rejected for target mismatch and supplied no semantic evidence.

## Node construction and copy evidence

The constructor-like helper41B7F0 owns84 bytes, SHA256
`94fe2301dec70d8fd04576336b868a5c1c6a6ca39a7720dc36c272e353dfb701`.
It takes the20-byte receiver in ESI, four arguments on the stack, returns that
receiver in EAX and pops16 bytes. Of32 decoded instructions,31 are reachable;
the three-byte alignment instruction at41B7FD is skipped. Its two CALLs are
both in41BCF0: the initial temporary and the appended heap node.

It allocates `strlen(path)+1` with array new665B8A, publishes the pointer,
copies through `strcpy_s @68AD95`, writes index/size/offset and clears next.
The already-exact destructor41B850 nevertheless calls CRT free for that path.
The old workflow's inference of a CRT allocation from this release was wrong;
both allocation and release are now represented as observed. Child nodes use
scalar new689DCB and delete6898EA instead.

Copying clones the filename allocation and copies all other fields, including
the next pointer. It does not recursively clone a collision chain. The
registration insertion expression only copies fresh values with next0; this
does not establish general safe copying of nonempty chains.

Helper41D320 is an82-byte pair/record copy, SHA256
`afd728b996d5aba69ba4242958b81f0f5bf8477bf971f483f766ecc4e69a3fac`.
Its receiver is ESI and source pair EDI; it has no stack arguments. It copies
the four-byte key then performs the filename-owning value copy inline.
Only41BCF0:41BDF7 calls it. The native map-find helper41C450 still has exactly
two decoded/raw-E8 callers,41BCF0 and41BFA0. No initialized PE absolute-dword
references to either root, constructor, pair-copy or find entry were found.
This bounds current reference evidence; it is not a proof about dynamically
computed addresses or the original translation-unit boundary.

## Three temporary lifetimes

At a missing key, the target constructs three complete owners before insert:

1. A20-byte temporary node, created at41BD8D.
2. A24-byte key/value pair, with its filename clone inline in the root.
3. Another24-byte key/value pair, created through41D320.

Insert41C360 receives the third pair. Normal cleanup frees owners3,2,1 in
that order. FuncInfo6E41FC has magic19930522 and four unwind states; its table
at6E41DC is32 bytes. States0/1/2 form the three-owner chain; state3 rolls back
scalar storage if appended-node construction throws. The27-byte handler is
6BDB83. Cleanup actions6BDB60/68/70/78 use the enclosing frame; pair actions
tail-call44-byte aggregate cleanup41BF70, which takes its pair in EAX.
These are auxiliary compiler/EH dependencies, without new authored credit.

VC8's actual `utility` header implements `make_pair(T1,T2)` by value. Its node
parameter is destroyed before insertion, unlike the target. The first natural
make_pair candidate was therefore rejected for lifetime, independently of
byte similarity. Explicit `pair<unsigned,Node>(hash,Node(...))` retains the
node, pair and const-key conversion pair through the insert call. That source
now lives with the constructors/copy/destructor in
`src/assets/PackageFileIndexRuntime.cpp`; declarations share the unchanged
20-byte physical layout in `PackageFileIndexNode.hpp`.

## Compiler controls and exactness limits

| Private source/profile | Complete registration span | Other evidence |
| --- | --- | --- |
| Ordinary O2, make_pair | 501 bytes | Wrong temporary lifetime; rejected |
| Ordinary O2, both real roots / internal-linkage node | 501 bytes | Same ordinary size and public find105 |
| Ordinary O2, explicit pair | 559 bytes | Three owners / four EH states |
| Real-source GL O2, explicit pair, GS off | 703 bytes | Four RETs; find116; constructor73 |
| Same GL O2 with GS | 707 bytes | Four RETs; find116; constructor73 |
| Both constructors defined in class, GL O2 GS | 707 bytes | Same size/exits/helper signatures |
| In-class copy, out-of-class ctor, GL Ob1 GS | 630 bytes | Still four RETs,212 reachable instructions, wrong private entries |

The GL links have both real roots, actual node ownership bodies, the selected
CRC body, vendored zlib and pinned CRT/SDK providers. They contain no unresolved
symbols or force flags. They specialize find to a fixed global/key-in-EBX
entry, and constructor73 uses another private argument split/RET12. Target
find is generic ESI/EAX/stack-key with RET4, and constructor84 retains four
stack arguments. Near target size in the630-byte control is not matching
evidence. Internal linkage alone did not reproduce these private entries.
No flag/inline/anonymous-type control is selected in public source.

The selected ordinary root is559 bytes. Its normal source find/constructor/
insert/pair-destructor boundaries remain incompatible with target private
entries. The source EH table also has four states and the same owner offsets,
but handler cookie-frame offsets differ by4. The formal unit maps only known
CRC/CRT calls, the accepted destructor, data and handler identity; it fails
closed on `relocation.rel32.unknown_target` for find. Constructor and insert
ABI mappings are deliberately absent too. Handler address identity is not
an exact metadata result. No new exact function or partial-byte credit is added.

## Execution and verification

In67 actual-instruction comparisons, target and selected ordinary source agree
on map values, strings, scalar fields, allocation/free/copy order, preserved
registers and RET16 stack cleanup. Cases include empty/missing/multi-key trees,
matching and colliding singleton/longer chains, case changes, three archive
indices, two stack alignments and large unsigned fields. Six allocation
exception controls stop at the call boundary and agree on live root EH state/call
prefix; a scalar-allocation null return also agrees. There is no OS unwind
execution claim.

Both sides execute actual root/find/node-constructor/copy instructions and
the attested CRC/getter. Insert is a checked contract model with separate
source/target entry adapters; allocation and ASCII CRT operations are modeled.
Red/black tree insertion, locale, concurrency and arbitrary corruption are
outside this proof. Coverage reaches181/200 root instructions; invalid iterator
handlers and fresh-node null-tail deletion branches remain uncovered.

Fresh `gpt-web-package-file-index-runtime` build keeps the accepted destructor
43/43 after adding constructor declarations and enabling GS for this unit.
Its new registration comparison remains blocked on the private find mapping.
The related opener recompiles and its243-case instruction model is rerun
against the current object after the shared node header changes; no differences.
No unrelated cold aggregate replay was run.

Receipts are below `build/package-index-update-20261019/`: target-spans/CFG,
incoming edges and complete raw-reference leads, primary DB before/after pins,
execution.json, entry-execution.json, focused comparison reports and the
real-source link directories with command/source hashes and CFGs. Controls
and execution drivers are under `.analysis/package-index-update-20261019/`.

Remaining work includes original visibility/partition, private helper ABIs,
EH metadata and the archive loader41BA70 before returning to reader/BMP code
generation. Two additional old nonexact probes still name array-new665B8A as
malloc: Ogg SFL418D10 and Winsock connection415340. Correct their source call
interfaces in a separate bounded follow-up; they are not new exact evidence.
