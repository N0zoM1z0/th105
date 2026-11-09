# Profile deck iterator-deque readers

Availability, rendering and update now read the actual
`deque<map<int, SpellRecordView>::iterator>` used by the constructor and
filter writers. Their former declaration-only `at` receivers were bound
to 0x4300B0, the native checked operator[] for eight-byte elements.

A bounded private compile confirmed that ordinary indexing retains the
required out-of-line calls in these three source units. No noinline hint,
wrapper implementation or compiler-profile change was needed. The emitted
99-byte provider matches 0x4300B0 completely, including its three
invalid-parameter calls and RET4. Its eight-byte element address calculation
also explains why this physical helper is shared with the existing
SecondaryAnimationPoint specialization; that does not make the deck's
elements animation points.

The complete before/after comparisons preserve availability358 and
update1339 as exact. Render remains the same nonexact 2521-byte body,
with first mismatch +776. All three canonicalized root bodies and five
complete root/EH sections are unchanged. The actual provider appears in
all three objects, with two, six and four direct root call edges respectively.

Private boundary probes are under
`.analysis/frontier-deck-index-boundary-20261109/`.
The public-source rebuild and complete provider/owned-section proof are
`.analysis/frontier-deck-reader-provider-20261109/{build_units,verify}.py`;
reports are in `build/frontier-deck-reader-provider-20261109/`.
Shared storage layouts, input work and source pins are unchanged.
