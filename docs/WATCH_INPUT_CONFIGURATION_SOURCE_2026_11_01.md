# Watch input configuration: complete source, nonexact

The140-byte watch-input helper42BC40 now has complete selected source and
independent application ownership. All48 instructions and both RET8 exits close;
native SHA-256 is
327ec78bdfd5cb6898887235d0ef68037400996666d03fc379a0d86385b68687.
Fresh exact LoadingWatch4268F0/209 reaches it at42697C. Its source remains139
bytes and nonexact, so no authored exact bytes are added.

The routine computes the two-side descriptor mask and saves the setup before
rebinding descriptors. It resets the low words68/D0 and readiness bytes6C/D4,
copies tags into owned metadataD8/E0, then publishes those owned descriptor
addresses to the setup. The native second-side branch reads the tag through the
already rebound first-side descriptor, and the source deliberately preserves
that behavior. No extra null guard, independent-right-tag replacement or other
defensive behavior absent from the target is introduced.

The related setup view now names these actual fields instead of leaving the
whole prefix opaque; offsets are asserted and size/layout are unchanged. A
normal nonvirtual declaration is added to BattleInputGate. No shared field,
vtable, ABI or provider implementation is changed. View names do not establish
unique original class/member spelling.

## Complete comparisons and bounded context control

The selected ordinary COFF unit preserves selector4284C0/60 and save42B9B0/305
exactly. Existing load42BAF0 stays332/nonexact at+0x92. The new helper first
differs at42BC6E (+46), where native keeps constant1 in AL and source uses CL,
with downstream pointer-register choices. Its old private137-byte report is
historical; this complete public source emits139/native140.

A genuine CIL control includes the actual completed save/selector provider
source, with their real public entries. Selector60 remains exact, save becomes
352/native305, and the watch helper stays139 with the same first mismatch.
That source context does not close the residual and is not selected. No fake
callers, opaque return stubs, noinline/COFF barriers, register variables or
source spelling grid is used. The original COFF remains the reproducible unit.

Receipts: build/frontier-watch-input-20261101/coff.json, caller.json,
ownership.json, linked.log and linked.json. The origin rule pins the complete
native body and actual exact-caller edge. No corpus-wide replay is claimed.

Totals: source1782/authored1802/mapped1809, excluded1789/review436, units764.
Exact1582/449309 remains unchanged. This is source/ownership progress only.
