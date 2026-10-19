# Exact auxiliary-sprite replacement behind Youmu856/902

## Target boundary and ownership

Only original Japanese TH10.5 v1.06a is used, executable SHA256
`56350024879199861579c11b0e1c67b9590e10a8d40cd5996b109deec9afca7e`.
The existing45CD70 candidate is now `AnimationAuxiliarySprite_replace`:
`[45CD70,45CEC8)`,344 bytes, SHA256
`624f920b25f7097e0e0bb99a16100beae9757efb06799b382774bc6485cf821a`.

**Observed:** raw CFG traversal closes all102 instructions/all344 bytes,
seven direct branch edges, eight direct calls and one `RET4` at45CEC5. Four
preceding and eight following INT3 bytes isolate it from45C500/45CED0.
There are no indirect exits, remote tails, jump tables, EH records or
unreachable bytes inside this extent. COFF independently owns exactly344
bytes. The Youmu543670 initializer's reviewed856/902 arms both call this
address with resource991 before updating the auxiliary object's position,
facing and scale fields. This is authored animation/resource behavior, not
an inferred compiler-library island.

**Observed:** ECX is self; resource_id occupies one four-byte stack slot,
whose signed low word is expanded into the native map key. The old pointer
at self+154 is destroyed/freed when nonnull. The function allocates108h,
constructs a CSpriteEx subobject at offset zero and publishes it to+154.
It finds the requested action in the tree at+160, validates the checked
iterator, validates frame zero of the88h-stride vector, reads the signed
texture/rectangle fields, fetches a texture from the vector at+130 and calls
407160 with seven ordinary integer arguments. It then copies frame+4/+6 as
floats to auxiliary+F0/+F4, initializes FC/F8 to1 and100 to0.

The eight native calls are delete6898EA, new689DCB, find45C320,
invalid-parameter68A143 at three separate checks, texture at40C100 and
texture setup407160. Both vptr operands are independently attested existing
identities: IColor6C0624 during destruction and CSpriteEx6C06E8 during
construction. The latter's COL6D731C/type descriptor6E615C names CSpriteEx.
No vtable symbol is aliased to another class and no vptr is written manually.
The durable name describes this operation; the original declaring class is
not uniquely established. In particular, the retained generic auxiliary-owner
wrapper in AttackObject.hpp contains a full CEffectSprite and is not proved
by this108h allocation. Other writers/global destructor ownership remain a
separate audit; this checkpoint does not change that shared lifetime header.

## Natural source and the lifetime distinction

The shared `AuxiliarySpriteRuntimeView` contains a real CSpriteEx member,
followed by the independently accessed x/y, frame offsets, scale, angle and
facing fields. Its ordinary aligned size is108h; no extra shaping field or
constructor is needed. Composition naturally emits the observed member
construction/destruction. This is a supported physical source model, not
unique recovery of the original wrapper declaration. The void unused-result
model reproduces every byte but does not uniquely establish the original
return spelling.

`AnimationAuxiliarySprite.cpp` uses actual VC8 checked std::map and std::vector
operations. The frame selection remains one full expression:

```cpp
AuxiliarySpriteFrameView &frame =
    reinterpret_cast<AuxiliarySpriteSequenceMap *>(sequence_tree_160)->
        find(resource_id)->second->frames_00[0];
```

The real temporary iterator remains alive through the checked frame access.
Splitting a sequence pointer into a preceding statement changes this lifetime.
That control still emits344 bytes and the same calls/ordinary logic, but uses
8h instead of target0Ch locals and differs in twelve stack-related bytes.
A named iterator produces341 bytes; scope-only and GS controls do not recover
the complete target. No dummy local or fabricated cleanup edge is added.

Four genuinely used rectangle values are captured before texture at(). The
target keeps height/width in saved registers and x/y in stack carriers across
that call. Leaving the reads inside the later texture call emits324 bytes;
explicit snapshots recover the required lifetimes. Using the native containers
instead of a separate texture-vector ABI view preserves the entire exact body.
These observations explain the source without declaring LTCG necessary.

The source's own native map find also compares105/105 against the already
excluded45C320 helper, SHA256
`3be84050d552bc5febe06a6be1b509ce5db9dd0cc3a4d6ea9b57ade5bde24229`.
This supports the function-pointer binding and adds no compiler byte credit.

## Accepted result and affected root

`cross-v106a-animation-auxiliary-sprite` freshly compiles the selected source
with the pinned VC8 SP1 `/O2 /GS- /GR /EHsc /MT` profile. The ordinary strict
comparator reports canonical344/344, with complete replay of eight REL32 and
two DIR32 fields, exact COFF ownership and matching target/candidate SHA256.
Source SHA256 is
`345ff2bcc137325aa4ec62ae0443972899ec0e95880dc1c56cb6b36dd14ff489`.
The candidate, mapping, source-present, authored-origin and exact ledgers are
updated together. This accepts344 authored bytes only.

The existing `SpriteTextureSetupView` declaration is shared in a small header.
Its two accepted implementations replay193/193 and261/261 after extraction.
Youmu's auxiliary pointer now uses the real shared storage view, and856/902
call the accepted provider through its typed owner declaration. Root source
SHA256 becomes
`7b0dac5f0c3d568080e2c53cba574838cd270c0bcd72d67108d1923870005cec`.
Its whole5488-byte canonical payload remains
`594a91c1273e04ea2f3bd6524c4fc844ba44194a06f4efd31e147465bb77df64`.
All23 prior equal owner diagnostics survive and the592-case real-selector
audit still passes. Private ordinary same-TU controls include this real provider
before or after the root; both preserve the entire594a91c1 payload. Definition
visibility in these two tested contexts does not recover the missing tail copy;
this is not an original-TU or LTCG impossibility claim. The old851 negative source remains reproducible and
fails only its four deliberate ABI alias inputs; its legacy relocation alias
is retained for that command. This audit does not execute856/902 allocation
or arbitrary live texture/resource graphs.

The5159-byte Youmu initializer remains **nonexact**, first+80/5436F0, with
820/850 physical sharing and821/823/851 preparation still open. The recovered
provider closes a concrete dependency and its ownership model; it does not
supply partial root credit or uniquely identify its original TU/compiler phase.
No cold aggregate replay or aggregate authored percentage is claimed.

## Reproduction and independent analysis

```bash
python3 scripts/build.py --unit cross-v106a-animation-auxiliary-sprite --compare --json
python3 scripts/build.py --unit cross-v106a-sprite-texture-setup --compare --json
python3 scripts/build.py --unit gpt-web-youmu-object-action-entry --compare --json
python3 scripts/audit-giant-action-owners.py youmu-object-action-entry \
  build/match-units/GptWeb_YoumuObjectActionEntry.obj \
  --unit gpt-web-youmu-object-action-entry --json
python3 scripts/audit-youmu-object-entry-calls.py \
  build/match-units/GptWeb_YoumuObjectActionEntry.obj
python3 scripts/check-match-literals.py --require-target
python3 scripts/validate-tracking.py --require-target
```

The first two units return0/exact; the root comparator returns1/nonexact;
owner/native checks return0. Formal reports are under
`build/youmu-entry-context-20261019/`: `formal-auxiliary.json`,
`texture-setup-replay.json`, `root-after-layout.json`, `root-owner.json` and
`root-native.json`. Private controls and direct Ghidra recipes are under the
corresponding `.analysis/` directory. Generated evidence stays outside Git.

The required IDA preflight still rejects the wrong open image, and none of
its semantics are used. A direct128MiB/CPU0 read-only Ghidra pass independently
attests the imported/file hash, image base, entry, all mapped text, root and
provider hashes, complete provider decode and CSpriteEx RTTI identity.
All nine primary database hashes remain unchanged and the temporary project
alias is removed. Its decompiler text is retained only as a hypothesis:
inherited callee parameter metadata gives an undefined argument carrier,
so it is not used to establish the texture-call ABI. Raw stack/register
observations plus the independently accepted407160 provider establish that
contract. No analysis metadata or target bytes are patched or saved.
