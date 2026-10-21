# ReimuObject 822: direction width and constant lifetime controls

The selected `496540` source remains unchanged and nonexact at `49655F / +31`.
Fresh complete forwarding-provider witnesses admit byte-direction formals,
but a corresponding private caller view still fails to recover the target
request window. No new source selection or exact credit follows.

## Target and selected baseline

Only Japanese TH10.5 v1.06a SHA256
`56350024879199861579c11b0e1c67b9590e10a8d40cd5996b109deec9afca7e`
is used. Target/status/tracking checks pass; IDA again rejects its different
open executable. No IDA semantics, metadata write or target patch is used.

The fresh focused build reproduces selected CPP
`3b9e4896c3645bb1228db3b432a832154870c5639a80df6c02cb67ce2dba12cc`
and the complete 45700-byte strict comparison hash
`d0ff3d3259c823cc56e322c5e0ec238456d8b490c78b4a5336a249b45a405a58`.
The owned target comparison still requests 46138 bytes; no source padding is
introduced. Same-TU `4963A0` remains canonical 66/66.

Raw `49A2BE..49A2CD` compares the second RNG result unsigned against 50,
sets AL, loads the full ECX constant 1, doubles AL, subtracts it from CL and
pushes ECX. The selected source instead sets CL, doubles it, copies cached
BL into DL, subtracts CL and zero-extends DL before pushing. The source's
packet-pointer register also differs. These are observed register/constant
lifetimes, not a recovered original arithmetic spelling.

## Independent forwarding witnesses

Fresh complete raw packets retain these hashes:

| Target | Bytes | SHA256 |
| --- | ---: | --- |
| Unparented wrapper `64CCB0` | 78 | `9aedc5ceafe11e034397b151e7406e9495ac57c200514d560ac6b3a5b038048b` |
| Parented wrapper `4FCA60` | 77 | `99bb18b6babfa6ce4dbf977af3ba46f6402246cbc697ec01afb74162b3b48426` |
| Reimu manager spawn `4938D0` | 237 | `33cec1265f0607a5fc8ea79307a3246a61d6d042bcde419e21b91904e129b516` |

Manager `493972/493976` reads the direction/variant slots as bytes and
`493990/4939A8` stores CL/DL to object fields +104/+33C. The wrappers forward
full DWORD argument slots; that alone does not establish original int formals.
The complete packets begin at ledger entries, not interior disassembly guesses.

A private copy of the real `CharacterObjectEffects.cpp` changes direction to
`unsigned char` in both wrapper definitions, their header declarations and the
matching `SpawnOwnedObject` callback typedef. Variant remains int. Both complete
providers reproduce their original canonical bodies, **77/77 and 78/78**, under
the ordinary pinned O2/GS-off profile. There are no fake providers, calling
convention substitutions or masked code differences. This independently admits
the narrow binary-interface view while leaving original formal widths and
signedness ambiguous. The accepted public int-view implementations stay intact.
The earlier Fighter-wrapper width witness is corroboration for a different
call surface; it is not substituted for these Object-provider comparisons.

## Caller controls and execution

An ordinary inline byte-facing helper remains an actual source call rather
than inlining here. The strict comparator rejects its unknown local target
`random_spawn_facing`; it is neither mapped to an unrelated target nor forced
inline. Changing only direction arithmetic constants to unsigned is whole-root
byte-neutral and retains the selected strict hash.

The private `ReimuObjectSpawnByteView` then uses the independently witnessed
byte formal at all 106 parented/unparented request expressions in this root.
Its two ordinary thiscall declarations retain the four-byte argument slots,
actual provider targets, variant, pointer and count roles. It is a diagnostic
caller view, not a proven original class or TU. No shared header is changed.

That candidate remains 45700 bytes, strict hash
`50894a8e7a2a42644207e0253bdb4a241fdec290aa10a626a03664e6f4770f3f`;
counter66 stays exact. The interior 822 request window becomes 222 bytes versus
target225. It still reuses the full cached EBX constant for the byte operation;
removing the old zero-extension does not recover the target's fresh ECX=1
lifetime or packet-pointer allocation. No window or whole-root equality is
claimed, and the candidate is not selected.

Fresh executions on **both** selected formal source and private byte-view
candidate pass all **624** existing 822 argument-lifetime inputs each:
576 actual request prefixes and48 actual inactive returns. Original seeding
and RNG instructions execute; 49/50/51 at both comparison boundaries are
required. Outputs, ordered writes, packet publication, pending real stack
arguments, RNG results, logical x87 and retirement checks all agree. Input
SHA256 remains
`5882f06795b2ed383942b71c7304b0dea78c7566bed2050ea171f72b66436dcf`.
Observers stop at opaque request entry; no return is fabricated. Physical x87
TOP/flags, unmasked exceptions, arbitrary aliases and returning-World behavior
remain unqualified. These 624 inputs cover the affected 822 cohort, not all
106 changed request expressions. Older other-action receipts retain their
own source epochs and are not promoted to this private candidate.

## Reproduction and next question

```bash
taskset -c 0 nice -n 10 python3 scripts/build.py \
  --unit gpt-web-reimu-object-action-state --compare --json
taskset -c 0 nice -n 10 python3 scripts/audit-reimu-object-822-argument-lifetimes.py \
  build/match-units/GptWeb_ReimuObjectActionState.obj --output build/reimu-822-current.json
```

`build/reimu-object-822-lifetimes-20261022/` retains baseline/formal reports,
raw width packets, complete native exports, private-provider comparisons and
both 624-case receipts. Native exports at `800000` have their own hashes;
they must not be confused with strict comparison hashes at target `496540`.
Private scripts and frozen controls are in the same-named `.analysis/` directory.

Public source, ABI declarations, profiles, layout, bindings, ownership, origins
and match rows remain unchanged. No aggregate cold replay or new aggregate
result is claimed. Continue from the selected source by inspecting the outer
constant-1 lifetime, unresolved physical call/RET sharing and source context;
these bounded controls establish no compiler or LTCG impossibility.
