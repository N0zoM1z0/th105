# System-effect tracked release source, 2026-11-03

The native system-effect tracked-release body at `0x436E60` is 119 bytes, SHA-256 `a88e31755974913ecefd93f6777aca63d70add23ac2274bf75aea5db627cd4a9`, with 48 decoded instructions and one return. The exact specialized manager destructor calls it at `0x4372B6`; all twelve existing matches in that lifetime unit freshly replayed.

The source uses the actual `CHandleManagerEx<SystemEffectObject>` and checked list of `SystemEffectObjectBase *`. It releases each object's handle through the pool and then clears the list. Its non-owning manager view fixes the observed pool and list layout without constructing a synthetic object. The earlier typed-handle and semantic evidence is in `SYSTEM_EFFECT_TRACKED_ACQUIRE_2026_10_29.md`.

The new public `exact-first-system-effect-tracked-release` unit emits 119 bytes, but its first difference is at offset 46: source and target choose different registers for the handle. Equal size is not byte equality, and this is source-present but nonexact. No register forcing, artificial liveness, partial-byte or exact credit was introduced. Fresh receipts are `build/frontier-system-effect-release-source-20261103/source.json` and `caller.json`.


## Real callable owner, 2026-11-08

Release is now the actual specialization of
`TObjectManagerBase<SystemEffectObject, SystemEffectObjectBase>::release_all_tracked_objects`,
rather than a method on a separate receiver view. The specialized destructor
calls this owner at `0x4372B6`. Scenario clear calls the same target at
`0x457E26`, and Scenario reset tail-calls it at `0x457F89`. Both Scenario
methods now reference the implemented base member; their obsolete
`release_all_system_effects` declaration and relocation aliases are removed.
The provider and callers emit the same decorated member symbol.

The non-owning checked-list view remains necessary because the shared owner
currently exposes that storage as `CollisionList`. It preserves the observed
0x60-byte manager and list offset 0x54. Using a reference directly to that
layout emits 101 bytes and drops the target's retained owner comparison; the
original checked-list member access is retained instead. No register-allocation
search follows from this result.

All 27 affected units were rebuilt before and after the change. Their 34
accepted roots remain exact, including the five Scenario runtime methods and
twelve effect-manager lifetime roots. Every comparable candidate is unchanged.
Release still emits the same 119-byte candidate hash
`1faf890b2f5515e32c92dbb8eeb45878e44cd6ff4bdd966d68065f2f5b914e8f`,
with the existing two handle-register differences. The real-owner correction
adds no exact function or byte credit.

Private before/after reports and the affected-unit list are in
`build/frontier-system-effect-real-release-20261108/` and
`.analysis/frontier-system-effect-real-release-20261108/`. The bounded source
and relocation comparison covers these functions, not a whole-program link.
