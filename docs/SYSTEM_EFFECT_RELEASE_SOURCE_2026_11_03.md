# System-effect tracked release source, 2026-11-03

The native system-effect tracked-release body at `0x436E60` is 119 bytes, SHA-256 `a88e31755974913ecefd93f6777aca63d70add23ac2274bf75aea5db627cd4a9`, with 48 decoded instructions and one return. The exact specialized manager destructor calls it at `0x4372B6`; all twelve existing matches in that lifetime unit freshly replayed.

The source uses the actual `CHandleManagerEx<SystemEffectObject>` and checked list of `SystemEffectObjectBase *`. It releases each object's handle through the pool and then clears the list. Its non-owning manager view fixes the observed pool and list layout without constructing a synthetic object. The earlier typed-handle and semantic evidence is in `SYSTEM_EFFECT_TRACKED_ACQUIRE_2026_10_29.md`.

The new public `exact-first-system-effect-tracked-release` unit emits 119 bytes, but its first difference is at offset 46: source and target choose different registers for the handle. Equal size is not byte equality, and this is source-present but nonexact. No register forcing, artificial liveness, partial-byte or exact credit was introduced. Fresh receipts are `build/frontier-system-effect-release-source-20261103/source.json` and `caller.json`.
