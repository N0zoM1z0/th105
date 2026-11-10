# Typed CSelect cursor storage and byte-valued mix

The shared constructor-facing CSelect and destructor-facing CSelectLifetime
now agree with their actual consumers:

- +100 contains four MenuCursorState records, two axes per player, each20 bytes.
- +1954 contains two selected-effect pointers. Their dynamic interface remains
  unspecified here; these pointers are not recast as a new owning object.
- +195C and +1970 contain the actual stage and variant MenuCursorState records.
- +2D78 is an unsigned-byte guide mix, not a bool. Full owner extent stays2ED8.

All five offsets are compile-time asserted in both headers. MenuCursorState
is the existing trivial five-field record; no constructor, initializer or
cleanup behavior is added to previously uninitialized cursor storage. Existing
entry/frame consumers now access real arrays/members rather than reinterpreting
opaque character buffers. Character binding accesses the actual pointer array.

## Independent behavior evidence

The already exact341-byte update-flow body4208E0 reads the byte at42092E,
adds/subtracts15 according to scene state and its0/255 gates, then writes it at
420950. This independently establishes a byte-valued range rather than a
Boolean. The real890-byte stage update uses both cursor objects; scene-entry
and frame-update consumers establish the four character cursor records. The
constructor still initializes the mix to zero. No new behavior or field is
inferred solely to influence register allocation.

## Complete before/after checks

Fresh unchanged-baseline and typed-state builds have identical entire canonical
candidate bytes for all five directly affected units:
- CSelect construction4247, still13 differing bytes at+2931.
- Scene entry783, still nonexact.
- Scene update685 versus native697, still nonexact. This fresh baseline size
  is recorded rather than reviving an older source variant's reported length.
- Character binding258 exact.
- Destruction845 exact.

Both constructor remote regions remain exact: EH461 and metadata188. Its
implicit CSpriteEx constructor16 and callback7 remain exact; the source review
hashes in sprite-default-origin-anchors are renewed only after these proofs.
The existing guard passes. Update-flow341 and stage-update890 are separately
freshly exact. The actual two-header include closure is five units; both units
containing accepted authored roots were rebuilt. This is not an aggregate
whole-corpus replay, and nonexact entry/update/constructor bodies gain no credit.

The private full-render candidate41FF00 also consumes this mix as an unsigned
byte; its earlier1497/163 nonexact status is not changed or reaccepted here.
No new source-spelling/register grid is opened by the layout correction.

Reproduce with scripts/repo-python, serial CPU0/nice10: the five affected build
units, scripts/audit-select-constructor.py, scripts/sprite_default_origins.py, plus
exact-first-select-update-flow and exact-first-select-stage-update.

Counts unchanged: exact authored1429 /443911 bytes; source1634, authored1653,
excluded2072, review302, mapped1821, units809. This corrects source types and
removes raw-buffer access; it supplies no artificial byte-count improvement.
