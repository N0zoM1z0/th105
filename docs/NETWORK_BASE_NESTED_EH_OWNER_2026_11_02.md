# Network base: recover the nested queue lifetime

The original411-byte CNetworkBase constructor44DB10 already compared exactly,
but its retained source flattened a real nested member. The missing lifetime
boundary made the source remote EH section207 bytes versus native197.

Native unwind action5 at6BA457 loads the parent receiver, adds20C and jumps
to43C380. That real19-byte helper destroys two32-byte queue slots at its+8
through callback43BF50 and runtime iterator68A2A9. It ends with RET at43C392;
following INT3 alignment is not part of it. It was absent from the provisional
inventory and remains supporting evidence, with no new inventory or byte credit.

## Ordinary source correction

NetworkQueuePair48 now holds an opaque8-byte prefix and two NetworkQueueSlot20
members. It occupies the observed72-byte cleanup region beginning at parent20C.
The old input_records region ends at20C, the slots remain at214, and the old
eight opaque parent bytes at254 remain. Assertions retain the complete6DC owner
and all relevant offsets. The original aggregate's full name/extent beyond its
last owned member is not uniquely established by destruction; this is the
minimum observed lifetime view, not a claim about extra trailing storage.

No destructor is declared for the group. Ordinary C++ emits its actual19-byte
cleanup and replaces the flattened24-byte EH action with the target14-byte
this-adjusting tail. Main constructor bytes do not change. No frame tuning,
inert local, noinline directive, custom register ABI or manual EH state is used.

This owner also stops using the legacy UiPrimitives raw-vptr sprite facade.
Its two sprite members are now actual ::CSprite objects, whose ordinary lifetime
definitions are verified separately. Their physical extent94h and callback
addresses remain unchanged; no shared header is edited.

## Complete replay

scripts/audit-network-base-constructor-eh.py verifies fresh build provenance,
all source relocation roles and these whole regions:
- Main constructor411 at44DB10.
- Remote EH code197 at6BA400, including handler6BA4AA at source offset170.
- FuncInfo36 at6DFE98 and its80-byte unwind map6DFEBC,116 bytes total.
- Queue-pair support19 at43C380 and implicit packet cleanup8 at43BE90.

The ten real source action offsets are0,11,25,49,63,87,101,115,142,156.
Every actual source symbol belongs to the same EH section. Full metadata keeps
magic19930522, max-state10, flags1 and the exact previous-state/action chain.
All197 bytes decode in the ten cleanup regions and handler; only original
named E9 exits are admitted. No generic CFG rule or source-label remapping is
relaxed. EH SHA256:b12e2a907c2fb95c3d7603443b8e0a53fb2c2dd8d588ccbb160d27482cdbd211.
Metadata SHA256:33e4b2fe2b6704aa1215ce4a1e7a3fe298022636e26c99aca2bd9f8d25febc39.

The packet member at+90 has its real std::deque<short> at+10. Its undeclared,
implicit destructor emits all8 bytes at43BE90. Source unwind funclet1 at offset11
replays the native14-byte action6BA40B, ending in the actual43BE90 tail. This is
an original compiler lifetime, not an authored handwritten cleanup. The earlier
6B8C6B reference is a different owner and was not used as this constructor's EH
base. Other incoming cleanup edges are not newly claimed owned.

Eight target-independent EH tests reject the old207-byte flattening, partial
metadata, wrong handler position, broken state chains and bypassed this-adjusting
actions. Actual corruption checks cover782 distinct constructor/EH/support bytes.
The separate CSprite type/callback checks have their own378-byte scope; overlapping
checks are not added as unique coverage. Full OS exception execution and previously
nonexact provider bodies are not newly proved.

Only the existing whole constructor remains in authored totals; EH, group support
and new compiler cleanup are not recounted.
