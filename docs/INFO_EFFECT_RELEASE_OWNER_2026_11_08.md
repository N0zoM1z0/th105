# Info-effect release owner, 2026-11-08

The source for `0x46EEB0` now implements the real
`TObjectManagerBase<InfoEffectObject, EffectObjectBase>::release_all_tracked_objects`
member. The normal and story InfoManager binding routines call that same member
instead of an undefined method-only alias. The fake release manager, opaque
handle pool and padded effect-object receiver are removed.

The exact InfoEffect manager destructor at `0x46F020` already identifies this
member through its decorated call relocation. Its exact constructor fixes the
0x60-byte manager and the pool/list offsets at +0x04/+0x54. The existing
RTTI-backed effect hierarchy supplies the actual `CObjectBase::handle_token_004`
member at completed-object offset +0x15C. A local checked-list view remains
because the shared manager still stores its recovered list as `CollisionList`;
it introduces no second callable owner. The two InfoManager callers retain their
observed secondary-manager offset +0x08.

## Affected comparison

Five units were built before and after with the pinned 1.06a target and unchanged
VC8 profiles. All 23 complete comparison results retain their canonical body
hashes. The 21 existing exact roots remain exact, including manager lifetime,
normal/story bindings and the shared effect virtual lane. Release remains
122/native122 with its prior mismatch at +46; update/prune remains 207/native207
with its prior mismatch at +165. No exact ledger changes are made.

The baseline and final reports are retained under
`build/frontier-effect-shared-owner-20261108/`. Changed source files are
`EffectObjectManagerRelease.cpp`, `InfoManagerBaseBinding.cpp` and
`InfoManagerStoryBinding.cpp`; their decorated keys are updated in the existing
match units. No shared header was changed.

## Shared virtual declaration still needs reconstruction

A separate controlled substitution exposed a concrete limitation in
`EffectObjectHierarchy.hpp`: its real base `AnimationObject` currently declares
only virtual slots +0x00 through +0x0C. Consequently, taking
`&EffectObjectBase::update_slot_28` through that header emits a dispatch thunk for
+0x10, not the native +0x28. The existing target thunk at `0x421D20` and its exact
manager caller `0x422E80` require +0x28.

Raw bytes of the RTTI-owned AnimationObject vtable at `0x6C0914` independently
show pure-call entries from +0x0C through +0x28, followed by render callbacks at
+0x2C, +0x30, +0x34 and +0x38. The incomplete shared declaration cannot yet
replace the virtual receiver in `EffectManagerVirtuals.cpp`. That trial was
restored, and all its roots were rebuilt. Its reports use the `hierarchy-` prefix
in the same evidence directory.

The next structural step is to recover the missing shared virtual declarations
and their derived overrides from the target, then verify their actual consumer
closure. Adding slots only to the effect class or changing the thunk binding
would hide the missing base contract. The retained release implementation uses
only the established nonvirtual state/handle layout and is unaffected by this
virtual-interface limitation.
