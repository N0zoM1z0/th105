# Guide overlay natural lifetime, JP1.06a

The local lifetime source and eight-slot inference below are superseded by
actual GuideOverlay.cpp and the global nine-slot CSprite. Constructor20 and
nonexact destructor90 remain unchanged. See GUIDE_REAL_OWNER_2026_11_02.md.

The selected GuideOverlay constructor43F540 remains20/20 canonical exact,
now from ordinary polymorphic member construction rather than the legacy
UiSprite94 manual-vptr representation. No new exact bytes are counted.
SHA256:ce9a93317e0946a83e05b769eb56b142ce0e0c6abbc6dec71ceb1b30711afea2.

The full A8 guide view has a real94-byte sprite at8, a texture handle at4,
scroll9C, widthA0 and alphaA4. Actual IColor construction zeroes its value;
normal derived sprite construction publishes the table, then the guide body
clears its texture and visible flag. No vptr field or manual assignment exists
in this selected source.

Fresh raw RTTI pins sprite table6C0668, COL6DCCDC, TD6FA52C to CSprite;
IColor table6C0624, COL6DCD78, TD6FA560 names IColor. The source models the
established eight-slot sprite interface and its real vertex/size fields.
The narrow view is not a shared-header or whole-program class replacement.

Destructor43F330 now also uses actual C++ member/base destruction. It remains
90/native92, first+40: source caches the handle while target compares memory
then reloads. Source SHA256:
40b7c204051af94d5a4d9806495760ac09e74de8e6469a5b0a37abcc74b35cbe.
The existing27-byte native EH handler6B905B anchors the destructor. No extra
credit is assigned and the handle-load residual is not forced.

The old GuideOverlay.cpp load/render source and shared headers are unchanged
by this checkpoint. Its legacy lifetime definitions are no longer selected as
constructor/destructor evidence. Guide update keeps the newly accepted112-byte
separate definition. All caller ABI mappings remain unchanged.

scripts/repo-python scripts/build.py --unit exact-first-guide-overlay-lifetime --compare --json

Source:src/ui/GuideOverlayLifetime.cpp. The report intentionally combines the exact
constructor and nonexact destructor.

## November 9: complete exception cleanup comparison

The current real `GuideOverlay` destructor now has complete local equality
for its remote cleanup support, including every relocation:

- `0x006B9050`, 38 bytes: the eleven-byte sprite unwind action followed by
  the 27-byte handler at `0x006B905B`.
- `0x006DF02C`, 44 bytes: the one-state unwind table and FuncInfo at
  `0x006DF034`.
- `0x0040AD50`, 7 bytes: the actual `CSprite` destructor used by the unwind
  action, restoring the `IColor` vtable.

The single unwind state has predecessor -1. Its action loads the saved owner
from frame offset -0x10, selects the sprite at owner+8, and tail-calls its real
destructor. The handler performs the original security-cookie check and tail
jump to `CxxFrameHandler3`. Both main-body graphs close through 27 instructions.

The complete main candidate remains 90/native92 with the same first mismatch
at +40 and the previously recorded candidate hash. Native code compares the
handle in memory and reloads it before the release call; the compiler retains
the load in EAX. The matching support regions remove an EH uncertainty without
resolving that main-body difference. No source or exact-ledger change is made
for this destructor.

The private check verifies current source/compiler/object provenance, complete
section ownership, relocation roles, unwind state and closed control flow. The
already accepted constructor still compares 20/20.
