# AyaObject entry sequence-word ABI, 2026-10-19

The4531-byte initializer at61F0B0 now differs from target in only two bytes.
Its local vslot+0C sequence parameter is `short`: this recovers all19 virtual
call preparations. The root remains nonexact and earns no exact credit.
A separate natural short-parameter witness reproduces the already-accepted
45C390 callee's entire202 bytes without changing the shared header.

## Target observations

The original Japanese1.06a executable SHA256 is
`56350024879199861579c11b0e1c67b9590e10a8d40cd5996b109deec9afca7e`.
Callable `[61F0B0,620263)` SHA256 is
`31c7399e608cfc6eb2a663ca53a99e6d8eaf12df221cbe1d0440cbed4ba919bd`.
All1195 instructions/4531 bytes are reachable through the32-destination
action switch; there are no unledgered direct targets or unresolved exits.
The one NOP and tables after RET620262 are outside callable credit.

AyaObject primary vtable6C624C, proved through COL6DB6FC, places45C390 at
slot+0C and this initializer at+3C. Its RTTI hierarchy has AyaObject,
CharacterObjectEx<Aya,AyaObject>, CharacterObject, AttackObject and
AnimationObject at primary offset0; CObjectBase is a separate+330 base.
The current method-prefix view does not reconstruct that full hierarchy.

At45C3E8 the sequence callee loads a full four-byte stack slot into EAX.
Every relevant use consumes its low word: TEST AX at45C3EC/45C40E, the
word publication at45C3EF, and modulo-low-word decrement/termination. EAX
is overwritten at45C419 before the next unrelated computation. RET4 at
45C457 confirms four-byte stack cleanup. The initial DWORD load alone does
not establish an original `int` parameter.

The old int-facing implementation explicitly casts the argument to short
both for publication and every loop test. Its accepted202-byte equality
therefore did not distinguish a wider source facade from a native narrow
parameter. Target observations establish low16-bit consumption; the coupled
caller experiment below supports the signed short source interpretation.

## Coupled caller and callee evidence

[The older scheduling note](AYA_ENTRY_VSLOT0C_SCHEDULING_2026_10_02.md)
identified11 CALL EDX sites. Complete current owner comparison finds another
eight CALL EAX sites in the same sequence-operation class. Each obtains its
method from vtable+0C. The old candidate delays MOV ECX,ESI until after
argument preparation; every target site prepares ECX earlier.

Changing only the local Aya view's sequence parameter from int to short
recovers all19 complete preparation sequences. No argument bits are patched,
instruction order is not forced, and the existing casts/decision bodies are
retained. Vtable order, receiver, four-byte argument slot, fields and root
void-return convention are unchanged.

The manual probe
`scripts/probes/animation-sequence-word-abi.cpp` uses a real short parameter
and ordinary `while (sequence != 0) { --sequence; ... }`. It inherits the
existing data prefix and calls the real tree lookup and virtual frame setter.
It needs no repeated cast in its loop and reproduces the complete202-byte
callee, including its ordinary receiver and RET4. This is an alternative
witness at an already-matched address, not a new function/byte claim.

Reproduce it using the existing unit's boundary and relocation contract:

```bash
scripts/compile-unit.sh scripts/probes/animation-sequence-word-abi.cpp \
  build/aya-entry-word-abi.obj
python3 scripts/compare-unit-object.py cross-v106a-animation-sequence-virtuals \
  build/aya-entry-word-abi.obj --address 0x0045C390 --json
```

This is a fresh manual compile followed by an existing-object comparison;
the latter does not attest build provenance or replace the default unit's
producer receipt. The comparator reports202/202, target/candidate SHA256
`dd6808825102feaf752f50030bba523485d6c03828599435509c2e09359abcd4`.
The shared int facade, its accepted implementation and all other callers
remain unchanged in this bounded checkpoint. No ABI rule is inferred for
another vtable implementation merely because it uses the same slot number.

## Complete selected root result

Selected source SHA256 is
`8f0364340bc1f3d3e693199a49321ee969e79d9f1c068351f8e704a8e9b736f7`.
The canonical4859-byte COFF payload SHA256 is
`6f70b6f354fdff459a628bdfbf0a7a3c12fe854a65f95f6cf33731b5d606b066`.
Code-prefix/table start remains4532; actual RET remains at4530. Comparison
of the **entire payload**, including every relocation and all metadata,
finds only these differences:

| Address / offset | Target | Candidate |
| --- | --- | --- |
| 61FCA7 /+BF7 | MOV ECX,[ESI+340] ModRM8E | MOV EAX,[ESI+340] ModRM86 |
| 61FCAF /+BFF | FLD dword [ECX+8] ModRM41 | FLD dword [EAX+8] ModRM40 |

Both instructions are in action856 before the real conversion helper. All
later bytes, branch displacements, helper identities and switch metadata
agree exactly. No opcode is normalized away for this finding. The owner
diagnostic rises13/33->31/33; action856 and the post-RET alignment owner
remain different. Counts or matching individual bytes do not confer partial
exact credit. Original action856 source lifetime/register choice is unknown.

```bash
python3 scripts/build.py --unit gpt-web-aya-object-action-entry --compare --json
python3 scripts/audit-giant-action-owners.py aya-object-action-entry \
  build/match-units/GptWeb_AyaObjectActionEntry.obj \
  --unit gpt-web-aya-object-action-entry --json
python3 scripts/ci.py
git diff --check
```

The first command intentionally remains nonzero at+BF7. Since the ordinary
machine changes are the19 commuting call preparations, the complete dataflow
comparison is more direct than a sampled replacement-helper execution.
No new native gameplay or exception-equivalence claim is made.

## Rejected controls and analysis limits

The saved pre-change baseline is sourcec9d1abb5, canonical payloadb4f36926.
Pinned RTM, embedded debug information/Z7,19 explicit int argument carriers,
an inherited virtual-prefix view, a discarded-return declaration and an
action856 heading-pointer local are fully payload-identical on that input.
/Zi instead fails C1902 due to its PDB manager; it is not a codegen result.

After the short fix, direct/explicit short conversions, inherited virtual
prefix, local/shared heading carriers and real shared scalar carriers leave
the same two bytes. An unsigned-short parameter changes the frame and removes
the19 conversion-helper calls, so it is not selected. Narrowing the real
float-copy-only shared_angle alias to float adds eight bytes and is rejected.
Do not repeat these unchanged controls as if the source context were new.

The subsequent action856 pass starts from selected8f036434 and retains the
same6f70b6f3 payload/two differences. A double Y-offset literal, direct
angle-argument expression, EHa exception model, generic copied-word storage
with real float reads, and a layout-checked multiple-inheritance model are
each fully byte-neutral. The latter preserves a330-byte primary prefix,
an8-byte secondary base at+330, and the observed338/340/348 fields; it is
a source-layout control, not proof of the original complete class definition.
A genuine repeated conversion/virtual operation fails the normal comparator
when emitted out of line; no invented binding is supplied. Its inlined
control is also fully payload-identical.

A real sequence-word snapshot changes prefix/payload to4524/4851 and no
longer has the target comparison structure. Explicitly widening the returned
angle before negation adds the non-target materialization,4540/4867.
Combining an unsigned formal with explicit signed conversion still produces
the previously rejected5052/5379 payload without the19 conversion calls.
None of these controls is selected. No register-normalized acceptance,
source change, native claim or exact credit follows. Receipts are under
`build/aya-entry-action856/`; the new bounded read-only Ghidra pass under
`.analysis/aya-entry-action856-20261019/` leaves all nine DB hashes unchanged
and removes its alias.

A genuine /GL diagnostic uses seven actual source-provider objects, real
static CRT/SDK libraries and real DLL startup. The baseline and preserved-type
short source both acquire an aligned EBP frame, unlike target. The short
source fixes the call preparations even there. A float-copy variant restores
the entry frame but retains the wrong4540-byte metadata boundary. Linked
images are neither executed nor accepted; preliminary table/CFG inspection
does not claim full linked relocation or tail qualification.

The link has no placeholder functions, unresolved overrides, fabricated
callers or absolute code bindings. Its only function alias joins the two
source names for the real596370 receiver-only operation. Six direct engine
providers compare exact;596370 and the two quantized lookup providers retain
their known nonexact status. For a coherent private float lookup declaration,
changing only the two return declarations preserves their full94/88-byte
COFF sections and relocation inventories. This does not accept those helpers
or modify their public sources.

Private reports, pinned input receipts, RTTI, complete byte/slot comparison
and genuine-link recipes are under `build/aya-entry-context/`. Direct Ghidra
independently verifies imported identity, entry and all mapped text bytes.
Its primary project initially has no Aya function; bounded read-only decoding
of the1195 attested instruction starts and a4531-byte temporary function
supports a decompiler hypothesis, whose unreachable-block warnings do not
override the raw CFG. All nine DB files remain unchanged and the temporary
project alias is removed. CPU0/384MiB recipes are under
`.analysis/aya-entry-context-20261019/`. Required IDA preflight rejects its
wrong target; no IDA semantics or factory adapter is used.
