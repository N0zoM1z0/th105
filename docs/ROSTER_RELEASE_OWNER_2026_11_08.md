# Typed roster release owners

The shared native release helper at `0x0056DA90` belongs to the fifteen
`TObjectManagerBase<RosterObject, CharacterObject>` specializations. Each
already-exact manager destructor calls its own decorated member symbol, while
the old source implemented the shared body on a separate `RosterObjectManagerBase`
view. The fifteen preallocation functions also called that substitute member.

`RosterObjectRelease.cpp` now defines the actual template member and explicitly
instantiates it for all fifteen roster classes. Each preallocation function
calls its matching specialization. The common storage view no longer declares
a callable release method. A local non-owning checked-list view remains because
the shared template still exposes that storage as `CollisionList`; its pool,
list and object handle retain offsets +0x04, +0x54 and +0x334.

## Complete comparisons

All fifteen emitted release bodies have the same 122-byte canonical candidate
hash, `c10136c192f6d39bcce89920804706eb32475e9526d4fb29fa787ecc2f5d077d`.
Each complete body and every relocation were checked. Their only differences
from the target remain +46 and +51, the EAX/EDX choice when forwarding the
object handle. The actual-owner correction does not make this root exact.

The check also connects thirty native call/jump sites to their emitted member
identities: fifteen exact destructors and fifteen exact preallocation functions.
The seven-unit changed-source/header closure and two direct owner/runtime
witness units preserve all 129 accepted roots. Every comparison result and
comparable canonical hash is unchanged. No new authored exact credit is added.

Private before/after reports are in
`build/frontier-roster-release-owner-20261108/`. The focused
`.analysis/frontier-roster-release-owner-20261108/check-owners.py` verifies
current object/compiler/source provenance, all fifteen bodies, the thirty
native owner edges and the affected accepted roots. It uses the existing
repository comparison tools; no shared validation tool was added.

The polymorphic `CharacterObjectManagerRuntime` family still uses a separate
runtime receiver. It cannot truthfully be replaced by an arbitrary roster
specialization: recovering that template/virtual interface is a separate
structural task. This change closes the statically identified destructor and
preallocation providers without making that substitution.
