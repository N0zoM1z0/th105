# Physical archive global and lifecycle, 2026-10-19

## Accepted observations and source state

The archive names, entry map and count belong to one physical global beginning
at 7028DC. They are now represented by `PackageArchiveStore` in
`src/assets/PackageArchiveStore.hpp/.cpp`, rather than three independent
source globals. Loader, registration, opener and FileReaderOwner consumers use
its actual fields. Original class name, inheritance and ownership of the game
methods remain unknown. The source uses a bounded composition view; this is
not an original class-name or inheritance claim.

Only original Japanese TH105 1.06a SHA256
`56350024879199861579c11b0e1c67b9590e10a8d40cd5996b109deec9afca7e`
is used. Two complete game composite-object functions are mapped and
source-present and now **accepted exact: 391 authored bytes**:

| Entry | Complete bytes / instructions | Target SHA256 |
| --- | --- | --- |
| PackageArchiveStore_ctor, 41B8C0 | 163 / 39 | a28bb00b955795f62ce713629f764857a98a4ac84cf790abd27f41aadc1a145e |
| PackageArchiveStore_dtor, 41B980 | 228 / 57 | 90b792e322ddf8f0e0fa8886c7b1d8448a6fbcb51ab8fea088d8712183c631f5 |

Both CFGs close at their final RET, with no remote branches or indirect jumps.
The constructor's private entry has no incoming this parameter and returns
fixed 7028DC. The destructor similarly operates on that fixed global. Normal
C++ methods acquire these entries in the genuine closed CIL control; the
ordinary object retains its this-bearing ABI and is not claimed to match.

The initializer pointer at 6C0374 names 6BE7B0. Its complete 17-byte body calls
41B8C0, pushes destructor callback 6BEE60, calls atexit at 68AF1E and returns.
The five-byte callback tail-jumps to 41B980. These two compiler startup helpers
remain outside authored mapping/exact credit; the formal comparator verifies both complete helpers as compiler witnesses.

The next independent global initializer writes a 260-byte path object from
702918. The recovered archive storage occupies 7028DC..702917:

| Offset | Observed storage |
| --- | --- |
| 00..1B | CCriticalSection subobject, vptr at 00 and Win32 critical section at 04 |
| 1C..2B | Native vector<string>, first/last/end at 20/24/28 |
| 2C..37 | Native map<unsigned,PackageFileIndexNode>, head at 30, size at 34 |
| 38..3B | Unsigned archive count |

The critical vtable is 6D6A14, COL 6DCA68, descriptor 6FA458 naming
`.?AVCCriticalSection@@`. It identifies that subobject, not the enclosing
archive class. Native source members preserve the observed 1C/10/0C/04 sizes;
compile-time checks guard the complete 3C view and field offsets.
An independent ordinary COFF build defines this symbol at offset zero in a
60-byte, four-byte-aligned uninitialized .bss section with no data payload.
That native-global-layout.json receipt is a real data-layout witness, not a
standalone function match or a fabricated symbol-only storage definition.

Construction initializes the critical section, then names, then map, then
count zero. The head allocator sets color black and the constructor sets nil,
self links and size zero. Destruction first clears names, clears entries and
sets count zero, **then** automatically destroys map, names and critical
section. That explicit clear policy precedes member destruction and was
missing from the independent-global hypothesis.

## Source and relocation change

`g_package_archive_store` is the only source definition of this storage.
FileReaderOwner reads count_38; the loader appends names_1c and publishes
count_38; registration and opening query entries_2c. Existing free-function
interfaces are retained: the original member/free ownership of those game
functions is unproved. No custom register declaration, source ABI facade,
assembly, inert local or artificial stack buffer is introduced.

The former three relocation aliases are replaced with the physical global's
symbol and independently observed member addends. Its initial loader bytes
are zero, before the real C++ initializer runs. The previously accepted Node
layout and destructor are unchanged. The loader's 256-byte local path buffer
is unchanged; its original declaration remains unknown.

All **17 existing affected units / 36 comparison outcomes** are rebuilt from
fresh objects. Every outcome and every available complete canonical payload
hash is unchanged, including all **22 accepted exact functions**. Before the linked contract was added, the two
ordinary lifecycle probes failed closed on their unknown EH-handler relocations
(`relocation.dir32.unknown_symbol`); private STL boundaries also remain
unsupported. No unknown handler is bound merely to obtain a result.

## Compiler/context evidence

The previous all-GL archive graph emitted loader627/frame148h. Adding the real
FileReaderOwner count consumer preserves that result. Compiling just actual
MT19937 as ordinary COFF restores its target61-byte seed ABI but leaves the
loader627/frame148h. Making registration ordinary next yields loader595/frame138h,
also obtained by the broader mixed-native control. This localizes the frame
change to the observed dependency context without proving the original TU.

A physical-owner hypothesis with normal C++ members generates constructor163
and destructor228, both with the target instruction structure. Ordinary
internal-class compilation instead produces constructor139/destructor264 and
a16-byte public wrapper, so that control is not selected. Neither private
register entries nor one failed ordinary control prove a universal LTCG rule.

A second, fresh CIL graph uses the **actual selected source files**, including
PackageArchiveStore, all package/reader operations, CCriticalSection source,
MT19937, the selected CRC body and real zlib/CRT providers. It links without
unresolved symbols or force flags. Its loader remains627 and nonexact.

A private complete relocation replay of this selected graph finds zero
differences in both lifecycle bodies (163/228), their five cleanup funclets,
two handlers, both FuncInfo records and both unwind maps. It accounts for
every source HIGHLOW field and named external branch, without masking fields
or cropping function extents. Source/target states are 2 for construction and
3 for destruction, with matching cleanup frame offsets and flags.

The original selected-graph receipt remains private compiler evidence. A new,
smaller **formal** CIL unit now includes the real PackageArchiveStore,
PackageFileIndexNode and CriticalSectionWrapper implementations. Node lifetimes
are factored into `PackageFileIndexNode.cpp`; the existing registration TU
includes that file, retaining the same definitions and visibility. Its accepted
43-byte Node destructor remains exact.

## Formal linked acceptance

The `gpt-web-package-archive-store` unit uses the pinned VC8 SP1 LTCG profile
with actual libcmt/libcpmt/oldnames/Kernel32 libraries. It has the real
`__DllMainCRTStartup@12` from libcmt:dllcrt0.obj, without a custom entry provider,
forced constructor/destructor exports or executable absolute symbols. The old
import-runtime/NOENTRY profile keeps its existing contract.

`scripts/linked_lifecycle.py` verifies:

- A separately compiled native COFF from the actually included Store source:
  one strong global at offset0 in a sole60-byte, align4, uninitialized .bss
  section, no payload, aliases or relocations. The witness is not linked.
- The complete source/target60-byte initially zero writable storage, the
  individually attested field addends and unique source CIL ownership.
- The private natural constructor/destructor identities; the exact17-byte
  generated initializer and5-byte callback; the real `_atexit` library member
  and positively classified target runtime; one initializer pointer between
  real CRT `___xc_a/___xc_z` sentinels and the readonly target slot6C0374.
- The actual static-CRT security-cookie object/value, native critical vtable
  and source RTTI identity. Typed references restrict global fields, cookie
  reads, handler PUSH and FuncInfo MOV EAX to their supported operand forms.
- Both complete parent CFGs, both handlers, all five cleanup funclets, both
  36-byte FuncInfo records and the16/24-byte unwind tables. Cleanup state/frame
  offsets, flags and all other bytes are compared, with exact HIGHLOW coverage.
  Unsupported catch metadata, states, pointers, edges or unmapped calls fail.

Local quoted include dependencies are followed transitively, including .cpp
aggregates, and hashed into build provenance. Native layout artifacts, static
libraries, image/map/CIL and the comparator are also pinned. No current function
is accepted from an old/private report or a parent-only byte comparison.

The fresh public report
`build/archive-linked-contract/gpt-web-package-archive-store-formal.json`
reports **163/163 and228/228 exact**. The13 parent/EH code+data regions cover606
bytes with zero differences; only the391 authored body bytes enter matches.csv.
The initializer, callback, table slot and compiler cleanup regions add no
independent authored credit. All three existing linked accepted units are
cold-rebuilt/replayed: scene408870/281, packet-pool413820/98 and shared release
405200/167; all remain exact. The affected Node41B850/43 is also cold-rebuilt
and exact. No aggregate all-unit replay or percentage claim is made.

The old candidate inventory omitted `41C200`. Its complete57-byte RET body
ends41C238, followed by seven INT3 alignment bytes. Native ESI vector access,
string-range destruction41D5A0, operator delete6898EA, the two actual unwind
callers and an independently compiled pinned VC8 vector<string> destructor
establish template ownership. Full57-byte canonical replay agrees, SHA256
`13256e6800e8d778c2a207a543d7a0d8ba420e11f487b2c82951b820a3808608`.
It is recorded separately as a compiler exclusion, with no authored mapping,
source-present or match row. Receipt:
`build/archive-linked-contract/vector-dtor-boundary.json`.

Target-independent rejection tests cover storage/layout tampering, native
providers/aliases, complete startup chain, typed operands, tail boundaries,
unwind code/metadata changes even with unchanged parent bytes, missing/extra/
duplicate/straddling HIGHLOW fields and transitive implementation dependencies.
All40 linked tests pass with both supported Capstone4.0.2 and5.0.6 using
pefile2024.8.26.

## Execution and analysis evidence

Seven integration scenarios execute actual target and selected-source
instructions through the real initializer, loader, string/vector operations,
map find/insert/rebalancing, Node lifetimes, CRC, MT19937 and final atexit
destruction. They pass for all 11 API invocations / 170 registrations, covering
failed open, empty and unused index bytes, long archive/name strings, empty and
embedded-NUL entry names, punctuation CRC collisions, case-insensitive updates,
four archives, vector growth and tree balancing. Red/black-tree links, ordering
and black heights are checked. Allocation/release sizes and order agree;
final destruction leaves no live allocations and clears all container/count
state. Target/source coverage is 2245/2156 distinct instruction addresses.

Only Win32 I/O/uncontended critical-section operations, successful allocation/
release and ASCII stricmp are modeled. Container initialization is executed,
not supplied by a guessed sentinel fixture. This does not establish full CRT
startup, OS unwinding, concurrent operation, allocation failures, locale behavior
or malformed/short-read indexes. The separate current-source loader model also
passes100/100 cases, including its four exception call-boundary controls.

Direct Ghidra input/base/entry/x86-Windows/full-text and scope hashes are checked.
The 60-byte bounded data view, both signatures, zero purges and163/228-byte
bodies are read back. Decompiler output remains a hypothesis; source was
derived from raw control flow and lifetimes. The read-only/noanalysis process
uses CPU0/nice10 and a384 MiB heap; all nine primary DB file hashes remain
unchanged and aliases are removed. IDA fails identity preflight and supplies
no semantic evidence.

Receipts and commands are under `build/package-loader-context-20261019/`,
especially source-change-controls.json, selected-store/commands.json,
selected-store-store-regions.json, selected-store-integration.json,
execution.json and database before/after pins. Private scripts and hypotheses
are under `.analysis/package-loader-context-20261019/`.

Reproduce the accepted lifecycle and the still-nonexact loader with:

```bash
python3 scripts/build.py --unit gpt-web-package-archive-store --compare --json
python3 scripts/build.py --unit gpt-web-package-archive-loader --compare --json
```

Continue the loader's private vector-helper/EH/frame context and the
registration, opener and reader/BMP residuals. Original archive class name,
inheritance, TU partition and game-method ownership remain unknown. The formal
byte/EH proof does not expand the execution model's OS/runtime coverage.


The later [loader context review](PACKAGE_ARCHIVE_LOADER_CONTEXT_2026_10_19.md)
adds actual native allocator header-method support to this linked unit. A fresh
public cold rebuild preserves163/163 and228/228 with complete EH replay;
`build/archive-loader-shape-20261019/store-with-library-formal.json` is the newest
receipt. Compiler42/42 adds no authored credit. That checkpoint also persists
four loader/helper ABI views and real Win32 import prototypes in a verified
private Ghidra copy before primary replacement; its nine-file pins supersede
the earlier unchanged-primary snapshots described above.
