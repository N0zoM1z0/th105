# Unsigned-deque pop_back from the actual timeline owner

The remaining identical23-byte body413DF0 is now independently qualified.
The actual SceneTimelineLoader.cpp TU emits std::deque<unsigned>::pop_back,
while its range _Insert at451E30 has an original REL32 field1491 naming that
member. Native call452402 selects413DF0, not the short-deque body428680.
The original full1818-byte insertion owner is pinned and its existing strict
provenance gate freshly recompiles all eight original owner anchors unchanged.

Both23-byte bodies remain separately present in the native image and both
still appear in the whole-byte inventory. The first proof selects428680 from
short-deque _Insert_n; this proof selects413DF0 from unsigned-deque range insert.
No exclusive template specialization spelling or linker ICF inference is made.
No proof is extended merely because its bytes happen to match another address.

The entire23-byte member is relocation-free and closes through RET. Current
compiler, actual source hash and official deque/xmemory/xutility headers are
pinned. The existing Timeline unit adds only the new selector. Its accepted
4540F0 function remains1584/1584, and the separate full-payload checker verifies
all1676 bytes including tables/alignment and fresh build provenance. Source,
layout, compiler flags and the existing TimelineSpriteOptionsView are unchanged.

Ten tests and1864 actual byte mutations (both23-byte identities plus1818-byte
owner) are rejected. The previously accepted short-deque gate freshly passes.
This adds only23 compiler-library bytes: excluded2066, review305, units808.
Authored1432/443941, source-present1637, authored1656 and mapped1821 do not change.
No new insertion/EH/timeline support credit is counted.

The earlier Nov1 statement that 413DF0 remains review is superseded by this separate
positive caller proof.
