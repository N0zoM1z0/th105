# Direct3D backend global lifetime

D3DBackend constructor 4146E0 is canonical exact 131/131 bytes, with complete
cleanup EH, native global storage, C++ startup table and atexit callback proof.
Body SHA256: 4270eabea2af08441873f9dd69b54f65a9dec489692f40ff0be4b325ef7f6d86.
Incremental authored progress is 1531 exact functions / 434264 bytes.
Destructor 414770 remains source-present/nonexact and contributes no bytes.

## Native lifetime and source

The existing D3DBackend aggregate at 7036A0 is 0x1B8 bytes. Its critical
section and reset-listener list construct before the body zeros COM owners
+1C/+20/+24 and the unknown flag +1A8. No other scalar fields are initialized
by the constructor body. Native pointers in the list are not deleted by the
container. The original class name is unknown; retained source names express
the independently recovered aggregate and COM ownership.

Startup 6BE870 calls this constructor, then registers callback 6BEEB0 through
atexit 68AF1E. Its real C++ initializer-table slot is 6C0388. The callback
is the complete E9 tail to destructor 414770. These compiler wrappers and
the 440-byte loader-zero object receive no additional authored credit.
The constructor closes all 31 instructions; destructor closes all 25 native
instructions / 103 bytes. There are no omitted remote tails or padding.

Source D3DBackendLifetime.cpp defines the ordinary constructor/destructor and
actual global. The linked context also includes the existing COM shutdown and
critical-section implementation. No custom register ABI, synthetic startup,
forced alignment, manually copied machine code or extra storage is used.

Native destructor behavior is shutdown_d3d_backend(), then list destruction,
then critical-section destruction. The current same-CIL source inlines the
shutdown and emits 169 bytes versus native 103. An actual separate COFF build
of the existing shutdown source recovers the 103-byte shape, but authored COFF
provider composition is not yet an accepted linked contract. That control is
diagnostic only. Constructor acceptance does not claim destructor equality.

## Complete constructor evidence

The canonical linked replay checks handler 6BD728 / 27 bytes, FuncInfo 6E3CF0 /
36 bytes, one-state unwind map 6E3CE8 / 8 bytes and cleanup 6BD720 / 8 bytes,
including real critical-section destruction and all relocation fields.
The native critical-section vtable, original CCriticalSection RTTI and the
real pinned static CRT cookie are independently attested.

Two bounded verifier cases were needed for this real object:

- VC8 emits its sole 440-byte .bss object with ordinary 8-byte COFF alignment.
  The layout reader now accepts only native 4- or 8-aligned zero sections of
  exactly the declared extent, without raw bytes/relocations/aliases. Linked
  source and target addresses must honor that recorded native alignment.
- The one-slot critical-section vtable is immediately followed by the separate
  pinned frame.obj datum __pDestructExceptionObject. Its exact map owner/name,
  ___DestructExceptionObject destination and HIGHLOW field establish a CRT
  datum boundary, not an extra virtual slot. Unnamed, wrong-owner, mismapped
  or unrelocated adjacent function pointers still fail closed.

These changes do not waive bytes, EH states, global identity or vtable slots.
Focused negative tests cover both cases. Previous global and UDP lifetime
contracts were rebuilt and reverified along with shared-header consumers.

## Verification scope

41 directly affected accepted units / 106 prior exact functions all replay
unchanged. Three generated-origin anchor families that include the header were
also rebuilt and revalidated. Only the new destructor origin rule and the
changed constructor baseline were added; unchanged origin evidence is retained.
This is targeted incremental validation, not a full-corpus cold replay.

Private receipts: build/frontier-d3d-global-20261030/ctor-final.json,
affected-units.json, numbered verification reports and origins.log. Earlier
private controls are retained in the matching .analysis directory.

Reproduction:

- scripts/repo-python scripts/build.py --unit exact-first-d3d-backend-lifetime --json
- scripts/repo-python scripts/compare-linked-unit.py exact-first-d3d-backend-lifetime --address 0x004146E0 --json
