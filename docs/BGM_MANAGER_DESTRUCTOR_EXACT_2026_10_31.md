# Owning BGM manager destructor: full body and cleanup exact

Original Japanese TH105 v1.06a SHA-256 remains
56350024879199861579c11b0e1c67b9590e10a8d40cd5996b109deec9afca7e.

## Accepted result and corrected identity

The complete279-byte normal destructor403F60 is canonical exact. Native and
source SHA-256:
c82e783703aaa05f448c6cd8529ef1b83a4dba8797b31b1a2e18604d0556e578.

The target's full RTTI spelling is CHandleManagerEx<BgmBuffer>, not the
pointer-resource CHandleManager family recovered separately. Vtable6D69A4,
zero-offset COL6DC948, descriptor6FA3A4 and scalar entry404090 identify the
owning0x50-byte manager. An older abbreviated table's pointer spelling must
not be treated as the full RTTI identity.

The existing physical BgmAllocationManager50 type is correct: stream pointer
vector04, generation vector14, free-slot list24, counter30 and critical member34.
The added ordinary destructor loops by unsigned index over streams_04.size()
and deletes streams_04[index], then real C++ member destruction runs. Native
checked access uses invalid-parameter guards rather than a vector at() throw.
No manual member free sequence, vptr store, fake register interface or padding
is introduced.

## Complete EH, without a waiver

The279 main bytes and all139 additional cleanup/EH bytes pass strict replay:

- Handler6BDA2C:27 bytes.
- Four funclets6BDA00/0B/16/21:11 bytes each.
- FuncInfo6E4054:36 bytes.
- Unwind map6E4034:32 bytes.

Actual receiver adjustments are+4,+14,+24,+34. The first vector cleanup uses
ESI; the generation-vector cleanup and final two use ECX. A first genuine CIL
control had the complete279-byte main body but used ESI for the second cleanup,
and was rejected. Adding the existing unmodified unsigned-vector COFF source,
alongside the already-existing unsigned-list COFF source, naturally recovers
all four observed forms. No cleanup bytes are ignored or credited as authored.

Source stays in BgmStreamAllocation.cpp so the independently reviewed private
release/stream caller graph remains within its established same-source contract.
The actual CriticalSectionWrapper.cpp definition is included. The strict
private-caller source requirement was not relaxed to accommodate an aggregate.

## Focused regressions and accounting

Public unit exact-first-bgm-stream-lifetime now verifies the new279-byte root
and its30-byte scalar wrapper. The old stream destructor220, spatial-buffer
destructor139 and reader destructor15 freshly remain exact with their existing
private-call/cleanup proofs. The other actual changed-source unit's stream
constructor89 also remains exact. Unrelated source/codegen scopes are unchanged.

The scalar wrapper404090 remains compiler-excluded. The manager adds one whole
authored function and279 bytes:1562 exact /445075 bytes.
Source1759, authored1779, mapped1786, excluded1658, review590, units752.
No allocator/release/lookup or helper credit is added.

The preceding list-only CIL control remains private evidence.
