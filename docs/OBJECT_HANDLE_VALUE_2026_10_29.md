# Object handle value initialization, JP1.06a

Two complete constructors are now canonical exact:

- CSelectObject422140:59/59, SHA256
  0c17ec23851f5d740813369743b2677df264f7df05c6f44b85161cb19335d9cd.
- InfoEffectObject46F150:59/59, SHA256
  f4e382a34023303244fda6fbf4ed726b4a5d898cdd0d5e6b7a07c29d93c794e2.

Only118 new authored bytes are counted. The original primary RTTI COLs6D782C
and6D98B4 still establish AnimationObject at0, AnimationObjectBase at4 and
non-polymorphic CObjectBase at158. No base declaration order, field offset,
virtual slot, complete extent or constructor call target is changed.

## Recovered initialization-bearing value

The actual four-byte handle is now represented by ObjectHandleValue. Its normal
constructor initializes its backing unsigned word to0. CObjectBase's body then
initializes state_000 to1. This separates handle-value initialization from the
base body, naturally reproducing the handle store before this+4 preparation.
The old source wrote both unsigned fields in the base body and let VC8 hoist
the LEA before the handle store.

The new type has exactly four bytes, no destructor work, vptr, allocation or
extra storage. Ordinary inline conversion/assignment preserve the existing
unsigned handle API and all32 bits. Its name and original nominal type remain
source hypotheses; canonical code proves this valid initialization context,
not a uniquely recovered spelling. It is an active owned value, not an inert
local or a register-order directive. Existing native packed-token writes,
object-handle offsets and value-initialization behavior constrain the model.

## Focused shared-header validation

Six affected units were rebuilt, not the corpus. Fourteen previously accepted
functions remain exact:

- Existing hierarchy/update/scalar bodies5/73.
- Two actual handle-pool acquisition callers434/434.
- CharacterObject constructor/normal/scalar lifetime78/145/30.
- SystemEffectObject lifetime/state/render107/30/248/35/222.
- Actual Sakuya handle assignment/list functions117/94.

The handle-reading roster release helper remains its known122/122 nonexact
result at+46; it gains no credit. New conversion/assignment creates no unresolved
symbol or layout change. Other pointer-only views do not construct the value;
all existing size/offset assertions remain valid.

scripts/repo-python scripts/build.py --unit gpt-web-effect-object-hierarchy-lifetime --compare --json

Shared source:src/characters/CharacterObject.hpp.
Receipts:build/frontier-object-handle-value-20261029/, including one JSON per
replayed unit. The initial private typed-header probe also reproduced both59-byte
constructors and all three CharacterObject lifetime bodies before publication.
The old blanket LEA/store scheduler stop is superseded by these actual receipts.
