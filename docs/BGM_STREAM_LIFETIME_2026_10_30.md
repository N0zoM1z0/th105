# Exact BGM stream destruction and pool lifetime

The complete220-byte stream destructor402880 is canonical exact, SHA-256
88bce6b50dae9b814e5dd70c76dab807abdf1c3e89b387262778740c9aed5a1b.
The incremental ledger is1528 exact functions /433849 authored bytes.
Only these220 authored bytes are added; cleanup metadata and supporting
manager/library/reader bodies receive no extra credit.

## Ownership recovered from native exception states

The destructor unlinks its next stream, releases its DirectSound buffer, and
explicitly closes the codec when stream_size is nonzero. Closing deletes and
zeros the current reader, calls the real ov_clear, then zeros stream_size.
Only afterward does ordinary member destruction delete any remaining reader,
destroy the buffer and destroy the string, in that order.

Native state2 remains active throughout codec close. State1 is published only
before the reader-owning member cleanup. Putting close inside the Ogg member
destructor instead emitted176 bytes and moved the state transition before the
call. The actual stream-body close operation naturally restores all220 bytes
and the complete cleanup graph. No inline directive or private register
annotation is used. The layout adapter is an observed ownership view, not a
claim about original C++ class names or inheritance spelling.

The15-byte independently padded418A00 body is the reader-owning destructor,
reached by the actual third stream cleanup funclet. It was missing from the
candidate inventory and is now authored/source-present, not separately exact.
The existing89-byte stream constructor remains an independent accepted root.

## Actual pool context

src/audio/BgmStreamAllocation.cpp now includes the actual allocation service,
pool acquire, checked token lookup and token release, alongside stream lifetime.
Release404270 locks, validates generation through checked indexing, clears the
generation, explicitly destroys the stream, appends the slot to the free list,
then unlocks. It has no invented RAII exception cleanup. Lookup404330 uses the
observed guarded lock and checked slot lookup. Existing caller receipts and the
full raw bodies independently establish these authored relationships.

The real release caller naturally selects the destructor's stack receiver and
RET4. Its current183/native184 body remains nonexact. Lookup195/native196, allocator
494/native401 and allocation wrapper26/native28 are also supporting source,
not accepted functions. Adding real lookup/release consumers exposes the actual
vector specialization but does not yet recover all native STL boundaries.
The old standalone allocation probe is replaced by this shared source graph.

## Full canonical proof

The same image verifies the complete destructor and:
- handler6BD8DE,27 bytes;
- string cleanup6BD8C0,8 bytes;
- buffer cleanup6BD8C8,11 bytes;
- reader cleanup6BD8D3,11 bytes;
- FuncInfo6E3ED4,36 bytes and unwind map6E3EBC,24 bytes.

Every call and data reference retains its typed source ownership, actual
relocation coverage and full native identity. The CDSBuffer table is verified
in full, and codec providers use the already pinned original Xiph SDK.

The cleanup contract now also admits an ordinary private normal destructor
through its real exported caller. The existing complete caller CFG, unique
source/target call-site and source symbol witness qualify its entry; they do
not confer caller exactness. The complete child body, all cleanup states and
metadata still require byte equality. Other private methods still require the
existing exact-parent route. There is no handler-only or frame-waiver mode.

Reproduce:

    scripts/repo-python scripts/build.py --unit exact-first-bgm-stream-lifetime --json
    scripts/repo-python scripts/compare-linked-unit.py exact-first-bgm-stream-lifetime --address 0x00402880 --json

Evidence: build/frontier-bgm-service-allocation-20261030/public-compare.json.
The mixed unit's other roots deliberately remain unaccepted.

Final focused native replay rebuilds only the three affected units: seven
DirectSound resource roots, the existing89-byte stream constructor and the new
220-byte destructor all match. Per-unit final receipts are in the evidence
directory above. The constructor unit now links the same actual pinned static
CRT/Xiph providers required by the expanded source. Target-independent CI
passes142 tests and whitespace checks; no cold all-unit build was performed.

The token/erase follow-up is detailed in BGM_LOADING_WORKER_2026_10_30.md;
new focused replay retains both accepted stream lifetime bodies.

The shared unsigned-list library follow-up now derives the native release
frame naturally. It retains full destructor equality but gives no additional
exact credit; see BGM_LOADING_WORKER_2026_10_30.md.
