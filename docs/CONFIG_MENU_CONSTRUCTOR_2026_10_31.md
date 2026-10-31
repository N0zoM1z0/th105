# Configuration menu constructor: complete source, still nonexact

CMenuConfig construction at441520 is now source-present and independently
authored. The complete candidate is863/native868, first mismatch at441855
(offset821). No exact function or byte is added.

The pinned original JP1.06a body hash is
c0c5a6d883abb20351c78aa60a5c7774d24e4f67eee8f5d6a5d63b773645da80.
RTTI vtable6C1A94/COL6D81B4/type6E6BFC names CMenuConfig. Exact Title425990
calls it at425CCF, and the root publishes that vtable at441560.

## Complete behavior

The 0x28C owner retains Menu, GuideOverlay8, textureB4, two spriteB8 elements,
design1E8 and both cursor records264/278. The source preserves normal
construction/unwind ownership, the exact six/four/two/two object-binding loops,
checked singleton lookups for IDs300/400 and their unchecked enabling behavior.
No null guard absent from the native program is added.

The config design and meter bitmap use their original paths. Meter widths are
unsigned width*volume/100 calculations with independent config loads around
virtual sprite calls. Guide20 becomes visible, optionB0 is cleared, the horizontal
cursor binds four entries and the saved option is clamped to signed0..3.

Actual MenuCursorBindings.cpp and DesignObjectLookup.cpp definitions provide
the observed initialization and checked-tree code. The existing
TextureHandleResult return-by-value interface preserves the real temporary
lifetime, rather than a named raw output slot.

## Remaining boundary

The native final clamp has an extra upper-bound comparison at44185E after its
initial upper-bound and lower-bound branches. Ordinary structured source
does not retain that redundant physical comparison. The full first821 bytes
are exact, but prefix equality earns no acceptance.

A standard-library reference clamp changes stack homes and emits884 bytes.
The real Windows SDK macro clamp emits869 or863 depending on its equality
operand choice; neither matches. The selected nested structured clamp remains
863 bytes. No redundant hand-written branch, volatile, unused storage,
register directive or optimizer barrier is inserted to imitate the target.

The public unit exact-first-config-menu-constructor compares the entire body
and intentionally reports mismatch. Existing provider source, shared headers
and accepted units are unchanged, so unrelated native replays are not needed.
Fresh target/IDA attestation is retained under
build/frontier-medium-discovery-20261031/. Formal comparisons and bounded
controls are under build/frontier-config-constructor-20261031/ and its
.analysis counterpart.

The new narrow authored rule revalidates the whole body, actual exact-caller
edge and vtable publication. Its single origin row is updated incrementally;
all prior origin evidence is retained. Totals become source1742, authored1762,
review845, while exact remains1547 functions /439428 bytes.
