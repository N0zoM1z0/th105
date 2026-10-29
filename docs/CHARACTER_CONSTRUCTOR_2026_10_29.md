# Character base constructor source, JP1.06a

462AB0 now has a reproducible selected complete557-byte source. It is still
nonexact: nine differing byte positions at the first sprite/EH-state stores.
No accepted bytes are added.

Native SHA256:6843409d8f8d40e4f3ebf4d1bd9615a666c72f0abda652943492913297aaa5a5.
Source SHA256:55da99cc034adc2525857bc6c42c71e9cf319d595bc4dfd0e8e8894c11e800cd.

Authored ownership and all557 reachable target bytes were already established
by exact roster constructor callers and the boundary review. Current RTTI
COL6D9560/type descriptor6E7A24 names Character and owns vtable6C2BE4.
The source now makes that previously private body reproducible through the
normal manifest, without requiring a match or changing accepted callers.

## Current typed evidence

The stack argument is a pointer to MatchSetup::Side: the native constructor
reads character key+0, option bytes+5/+4, deque payload+8, transition link+1C
and category byte+6. The new constructor-facing declaration uses that pointer
rather than an integer-carried address. Its ordinary stack/RET4 ABI is unchanged;
existing derived caller declarations are not edited.

The source uses the actual AttackObject base, genuine std::map<int,
AnimationSequenceBlock*> and std::vector<int>, and a64-element array of real
four-byte zero-constructed handles. The same9-byte handle constructor is folded
with an already accepted body at40CF10; it is not credited again.

Sprite members have the current eight-slot interface and94-byte layout.
The existing ProfileDeckResourceGroupNative20 gives the spell resource core
its real checked deque/map ownership. SpellDataOwner's existing typed side
payload method receives the actual input deque. At+674 the render-history
owner is14 bytes; a separate unaccessed Character field is at+688 before the
next owner+68C. The old18-byte opaque member conflated that field.

Other unaccessed fields and declaration-only member cleanup boundaries remain
explicitly incomplete layout knowledge. The constructor-facing class is not a
claim that the full original nominal class hierarchy or all destructor bodies
have been reconstructed. No objects of this analysis view are allocated by
new unrelated code.

## Lifetime and comparison

Native full27-byte handler6BB127 references FuncInfo6E0CD4 and thirteen states
at unwind map6E0CF8. The source retains the real base/member/new-expression
lifetimes. Native writes sprite+340=0 before storing EH state0; source stores
that state first. The two stores exchange order over the same ten-byte span,
producing nine unequal bytes. Every byte outside that span agrees.

The setup pointer, real tree, current sprite interface, actual spell core,
correct render-history extent and removal of forced-inline annotations all
retain the same557-byte candidate. No EH liveness, extra locals, frame flags,
manual vptr stores or assembly were introduced to force the residual.
The older extensive profile/context controls remain negative evidence and
are not repeated.

Source:src/characters/CharacterConstructor.cpp.
Command:
scripts/repo-python scripts/build.py --unit exact-first-character-constructor --compare --json

Formal comparison and target/source disassembly are under
build/frontier-character-constructor-20261029/. Existing shared headers and
accepted consumers remain unchanged. Default CI and diff checks cover final
source selection, aliases and progress.
