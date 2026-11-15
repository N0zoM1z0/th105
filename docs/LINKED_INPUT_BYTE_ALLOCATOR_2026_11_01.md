# Complete byte allocator in the actual input-state CIL graph

Native 40AB70/78 now canonically matches the original
std::allocator<unsigned char>::allocate emitted from the unchanged
InputStateTableUpdate/InputCluster source. The existing 40A550/266 input-update
root is rebuilt and must remain completely exact before the helper proof runs.

Its real add_tracked_key sibling remains the already-established public source
method and export. No allocator/private helper is exported, no dummy caller is
added, and no private-register declaration appears in source. VC8 naturally
uses ECX for count. The add-key sibling 269/native202 remains nonexact and gets
no credit. The new claim is only the data-independent byte-allocation family.

## Full code and imports

All 78 bytes compare after exactly five typed fields: named calls 11/51/74,
ThrowInfo56 and bad_alloc vptr 69. Every nonrelocation byte remains unchanged;
full inventory replay has exactly one canonical hit. The source has one
unaliased original allocator symbol in the actual CIL owner.

All five source runtime entries used by the allocator/support graph are complete
FF25 import thunks with verified actual MSVCR80.dll IAT identities: operator
new, exception(char const*&), CxxThrowException, exception destructor and copy.
An entry with the same six bytes but another DLL or export is rejected.
The existing input-unit compiler/runtime/source profile is unchanged.

The source call passing ThrowInfo and the actual stack-object address/vptr are
checked as instructions, not arbitrary DIR32 substitutions. Both complete CFGs
close through the normal return or the actual final C++ throw call. The
complete native 74-byte throw,32-byte noncontinuable record and genuine
RaiseException IAT are re-attested. No ordinary terminal-call boundary is
silently accepted by the generic linked decoder.

## Typed metadata and preserved old contracts

Complete source/native ThrowInfo16, CatchableTypeArray12, two 28-byte records and
both whole TypeDescriptors agree after their named pointers are rebased.
The actual bad_alloc primary RTTI and type_info vtable identity are checked.
Original bad_alloc destructor 401630/11 and copy 402680/25 also fully compare
from this same source image; these existing exclusions get no extra credit.

The shared allocator CFG helper adds an explicit 78-byte contract; its old
default remains 85 and still rejects 78. Metadata owner parameters are explicit
for this real CIL/import source; old static-original defaults stay unchanged.
The prior static original bad_alloc gate was rebuilt and all five previously
accepted bodies passed. No old schema, source owner or minimum coverage was
relaxed.

Actual quoted source dependencies are hash-pinned with normal Git LF/CRLF
handling. Original xmemory/new/exception/xstddef header bytes are separately
raw-hash-pinned. Whole source/link/compiler provenance and the exact owner
report are stored with the proof.

## Accounting and checks

Only 40AB70 moves review to compiler-generated exclusion: excluded 2008/
review 364. Authored exact 1431/443916 bytes, source 1635/authored1655/mapped1820/
units 777 stay. There is no new authored or sibling exact claim.

- scripts/repo-python scripts/linked_byte_allocator_origins.py
- Narrow vc8-linked-input-byte-allocator-106a origin replay.
- Fresh existing input-update266 canonical comparison.
- scripts/repo-python scripts/linked_bad_alloc_origins.py: prior five static
  original bodies freshly pass with unchanged defaults.
- Nine new synthetic tests and seven actual code/metadata mutations reject
  changed imports, extents, typed roles, control flow and exception data.
- scripts/repo-python scripts/ci.py and git diff --check pass.

Contract: config/linked-byte-allocator-origin-anchors.toml. Full proof:
build/origin-anchors/linked-byte-allocator.json.

The discovery inspected only four remaining bad_alloc-ending allocation shapes,
not a cold corpus replay. Eight retained leads from 37 hash-consistent images
were observations only. Acceptance used the freshly rebuilt actual unsigned-
byte input context. The other 16/32/80-byte allocation-family candidates remain
unaccepted. Target is the pinned Japanese 1.06a PE; no new IDA semantics,
compiler flag search or generated executable run occurred.
