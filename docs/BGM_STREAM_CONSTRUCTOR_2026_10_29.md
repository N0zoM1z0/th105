# BGM stream constructor, JP1.06a

402820 is canonical exact 89/89, SHA256
124de7ed11ac64ee0b724656f9ceda7d2c77920d2324cc8a6a82c62de04d49f8.
Only 89 new authored bytes are counted. The 401-byte allocator 4040D0 is supporting
source/ownership evidence, not an exact function. Its current CIL body is 571 bytes.
The earlier service 4036C0 still has its 26/28 nonexact source contract.

## Actual object ownership and the recovered subobject

The native pool allocates 1378 bytes at 40414B. It calls 402820 at 404160 for a fresh
allocation and at 404231 when reusing an existing nonnull slot. The helper
initializes a string at 0, CDSBuffer at 24, gain/timing/state and linked-stream fields.
Its native receiver is EAX with RET 0; the ordinary C++ constructor acquires that
private convention naturally inside the genuine allocation/placement-new CIL.
No source calling-convention or register instruction pretends to express EAX.

A raw independent caller 402A00 computes ESI=stream+30 at 402A1B and calls the
reviewed Ogg open function 418A10 at 402A1E. Two PCM paths also pass stream+30 to
418B70. This proves that the two zero stores at 30/34 belong to the existing
OggDataSource reader/stream-size prefix, not two unrelated stream-body fields.
Its recovered 1310-byte layout includes the real Vorbis/loop/format fields.
The initializer-facing adapter only initializes reader and stream_size; it does
not claim that the original source had a derived class. Unknown 1340..134B bytes
remain untouched, as do start/target/master gain and the unobserved 1374 tail.

Flat body assignments and flat initializer-list assignments emit the same wrong
ordering: gain FSTP before the 30/34 stores. The actual Ogg member constructor
places those stores before gain publication and closes the whole 89-byte body.
No dummy lifetimes, alignment, padding for codegen or redundant writes are used.
The 1378 extent and member offsets are independently asserted against allocation
and consumer evidence; opaque unaccessed ranges are not extra stack storage.

## Canonical relocation and private-entry qualification

The sole address-bearing instruction publishes the member CDSBuffer table 6D6D44.
The existing full eight-byte anchor contains initialize 418310 and scalar deletion
4182A0; its primary RTTI names CDSBuffer. The generated CIL table independently
has the corresponding two functions, actual source-class RTTI, read-only storage,
unique CIL ownership and no extra executable third slot. The code field has its
actual HIGHLOW relocation. The table is not manually written in source.

Both complete normal caller CFGs are decoded. All two actual constructor calls
must be present on each side: target 404160/404231 and the two generated CIL sites.
The caller's EH/security addresses are separately recorded as source-owned mapped
fields with exact relocation coverage. This qualifies the private constructor,
not byte equality or exception-state equality of the 571-byte source caller.
Its standard ECX manager receiver remains different from native EDI.

The comparator gains two bounded contracts for this evidence only: an optional
bool(const void*,unsigned) initializer before an owning scalar destructor, and
an explicit pair of ordered constructor call sites. Full target anchor/RTTI,
both source method identities, extra-slot rejection, complete call multiplicity
and HIGHLOW checks remain mandatory. Legacy one-slot and one-call behavior is
preserved. Three focused tests reject wrong slots/owners, extra slots and
missing/duplicate/reordered call-site claims; no gameplay matrix was added.

## Reproduce only the restored constructor

scripts/repo-python scripts/build.py --unit exact-first-bgm-stream-constructor --json
scripts/repo-python scripts/compare-linked-unit.py exact-first-bgm-stream-constructor --address 0x00402820 --json

The configured allocator is deliberately an exported caller witness. It is not
accepted, and selecting every unit function is not a successful full-unit claim.
The normal accepted-function workflow selects 402820 while retaining the complete
unit for its private-caller evidence.

Source:src/audio/BgmStreamAllocation.cpp, using the real DirectSound resource source
and existing OggDataSource/BgmHandleResult/critical-section layouts. Focused legacy
replay preserves package lifetime 163/228 and effect/listener71/157, covering old
one-slot and one-call contracts. No all-unit cold rebuild or target execution is
claimed.

The 2026-10-30 lifetime follow-up extends the same source with real stream
destruction and pool lookup/release. The constructor-only unit now uses the
pinned static CRT and original Xiph archive because the full source contains
codec close; its 89-byte constructor remains exact. Its exported allocator
context remains 571 bytes, while the larger lifetime context outlines additional
STL consumers and gives 509. Neither allocator is accepted. The reader-prefix
ownership adapter now covers destruction as well as initialization. See


The later token/erase follow-up changes the supporting allocator to 552 in this
constructor-only context and 492 in the larger lifetime context, without exact
credit. Constructor 89 remains exact. See BGM_LOADING_WORKER_2026_10_30.md.
