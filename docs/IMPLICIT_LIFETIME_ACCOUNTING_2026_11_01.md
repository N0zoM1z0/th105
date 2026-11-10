# Implicit normal lifetime accounting correction

## Corrected attribution

17 previously counted authored functions /1,434 bytes are implicit compiler
members in the actual selected sources:

-15 CharacterObjectManager normal destructors,81 bytes each. The template
 declares only its constructor and owner pointer; inherited virtual destruction
 emits the entire normal lifetime without an authored destructor declaration.
-ResultList normal destructor447260/55. The real ResultList definition declares
 its constructor and populate override, and owns four deque members. The implicit
 destructor tears those down and enters ResultListBase. No authored destructor.
-CTile copy4396A0/164. The selected CTileCopyLifetime source contains an implicit
 copy, not a user-written copy declaration or body. The source fixture exposes
 that compiler member and is not itself an accepted game function.

The explicitly authored empty ICharacterObjectManager destructor491B90/7 is
not part of this correction. Template constructors with authored pool policy
also retain their authored attribution. No new compiler helpers are claimed.

All17 complete canonical bodies were freshly reproduced from their existing
three owner units. Source, mappings and proofs stay; only erroneous authored
source/exact credit is removed. Corrected totals: exact1428 /443902 bytes,
source1630, authored1650, excluded1969, review408, mapped1815, units769.
Historical1445/445336 and earlier totals are superseded by this attribution
correction, not by a code regression.

## Strict evidence contract

The new implicit_lifetime_origins validator pins the reviewed source and
header declarations, original ordinary owner units, emitted compiler member
names, target/compiler hashes and full native body hashes. Each validation
freshly builds the owners and compares the entire emitted section tail against
the target with all relocations resolved. The complete canonical target/object
hashes and sizes must be identical. Alias ResultList_dtor must resolve to the
actual emitted normal destructor, not an arbitrary named stub.

This is a separate complete-byte proof, not a lowered fingerprint threshold.
In particular ResultList55 has only35 nonrelocation bytes, so the ordinary
70-percent generated-origin fingerprint gate would reject it. That gate remains
unchanged; no masked, partial or alignment-tail acceptance is used here.

The existing canonical source contracts retain their real native RTTI/data,
base-destructor and deque-cleanup bindings. Their surrounding owners and scalar
wrappers were freshly compared in the same three builds. The15 manager methods
retain65/81 nonrelocation bytes with actual per-specialization base calls; this
is not counting a masked clone family as multiple authored implementations.

Source/header pin changes require a renewed ownership review. Seven synthetic
tests cover pins, source mutation, numeric address spelling, selected extent,
actual member kind, original owner profile/source, aliases and duplicate review
inputs. They do not embed target instructions or fixed progress totals.

Tracked anchors enumerate every selected body. No source rewrite, all-exact rebuild,
manufactured destructor or push.
