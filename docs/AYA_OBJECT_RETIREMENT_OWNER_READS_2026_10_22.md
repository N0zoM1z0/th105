# AyaObject action900 retirement owner reads, 2026-10-22

The entry/TU controls below retain their original source epoch. The
[current joint CIL replay](AYA_OBJECT_JOINT_CIL_REPLAY_2026_10_23.md) completes
the update caller's address replay and finds zero ordinary-byte changes against
current native code; the older eight-byte result is not a current-source claim.

## Selected result

Observed target: Japanese1.06a SHA256
`56350024879199861579c11b0e1c67b9590e10a8d40cd5996b109deec9afca7e`.
AyaObject update61A290 still owns19522 callable bytes,4630 decoded/reachable
instructions and seven switches. IDA preflight rejects its open image; this
work uses the independently hash-attested PE, not IDA semantics.

The action900 sequence0 retirement tail now reads the current owner for each
state730 publication/check and spells the observed mode0-or1 predicate.
Target61DC18 reads owner348,61DC28 writes WORD730=1,61DC2F reads mode6FA894,
61DC3C reloads owner before writing3, and61DC4B reloads owner before the
state2-to3 check. The old source cached the initial owner and a short reference.

The selected candidate at61DC72 reproduces all76 bytes of target
[61DC18,61DC64) under placement translation, including internal branches.
The following lifetime decrement still uses EBP instead of target EDI.
This local observation is not canonical function equality.

The complete candidate is20028 bytes, canonical SHA256
`b05357e645d63a2beb6db788048d3c075d0738e87e0f665253b3239c90a08017`.
Metadata starts19560 versus target19524. The configured19522-byte comparison
remains nonexact at+0x22, target0F/source32; compared-window SHA256
`bb963d8e48202ba53753b05212fb630bdd16a4e1034ad26812ce3b3e47053345`.
Owner diagnostics remain3/34. No new exact credit, shared header, helper,
ABI declaration, compiler flag or relocation-ledger change is selected.

## Independent controls

All controls compile the complete update body and replay its relocations.

| Source | Full payload bytes | Canonical SHA256 prefix |
| --- | ---: | --- |
| Previous source |20016|cd4b9c34|
| Explicit mode0-or1 only |19996|d5ddc90e|
| Repeated owner reads only |20020|a9192d0b|
| Both, selected |20028|b05357e6|

Smaller output is not the selection criterion. Only the combination recovers
the target's complete76-byte state-publication interval. Previous owner-read
notes addressed action861, not this900 tail.

## Executed scope and limits

`scripts/audit-aya-object-900-retirement.py` runs the original root and the
relocated selected COFF from their real entries through their actual RETs.
It supplies no callback/helper returns and rejects execution outside the root.
Target image pages are read/execute; the fixture mode page is writable.
Candidate code is relocated to800000, separate from the target.

All2688 disjoint-object cases agree in complete fixture memory, ordered object
writes, x87 status/tag and returned stack/callee-saved registers. Cases combine
six initial WORD730 values, seven mode values, four outside-stage X values,
two owner sequences, and eight masked x87 precision/rounding words. Owner
state186=1 skips movement, object state364=1 skips spawning; no helper is
called. This is a finite retirement-path audit, not full update/game equivalence,
and does not close exceptions, spawn callbacks, or other action900 sequences.

Twenty additional raw alias-stress cases overlap owner730 with the actor's
owner-pointer storage. The previous source differs in eight; selected source
agrees in all20. These overlapping objects are an artificial machine-memory
fixture, not a claim about legal C++ object overlap or reachable game ownership.
Normal disjoint cases do not demonstrate an ordinary gameplay bug.

Reproduce after the focused build:

```bash
python3 scripts/build.py --unit gpt-web-aya-object-vslot28-full-root --compare --json
python3 scripts/audit-aya-object-900-retirement.py
python3 scripts/audit-giant-action-owners.py aya-object-vslot28 \
  build/match-units/GptWeb_AyaObjectActionState.obj \
  --unit gpt-web-aya-object-vslot28-full-root --json
```

The canonical comparator intentionally exits nonzero for the nonexact root.
Optional `--previous-object PATH` compares an old object under the same ABI.
Private recipes and reports are under `.analysis/aya-entry-owner-context-20261022/`
and `build/aya-entry-owner-context-20261022/`; `tail900-selected-*` identifies
configured-source results. Whole-root numerical and non900 behavior remain
outside this finite execution proof; complete byte/owner audits stay nonexact.

## Entry/TU experiments that exposed this lead

Aya entry61F0B0 remains4859 full bytes, canonical6f70b6f3: its4531 callable
bytes differ at+BF7/+BFF only, using EAX instead of target ECX for the action856
parameter read. Fresh isolated17-slot owner, primary storage, typed parameter
records, void-short selector, inline member/free handler, chained zero stores,
and default-fastcall controls leave the complete payload unchanged. A real
void-short selector provider itself compares202/202, but this does not prove
a unique original declaration or justify changing shared ABI views.

A combined owner/TU with both complete entry and update bodies and consistent
short selectors leaves both native payloads unchanged. A genuine combined
GL/LTCG link closes with twelve actual native provider source objects and
pinned CRT/SDK libraries; no absolute code-provider stubs are used. Its entry
has no changes outside188 ordinary relocation fields. Its update moves a mode
comparison ahead of the initial state730 store, changing eight nonrelocation
bytes. That ordering is not target ordering and is unselected. Full linked
relocation replay has not been completed, so these observations do not claim
linked canonical equality.

That link uses a coherent private double-return lookup contract; its real
oriented provider remains57-byte nonexact because FCHS/FMUL order differs.
It is not an all-exact helper closure. Strict floating mode with exceptions
disabled is separately blocked on an unbound130.0f literal, not a completed
canonical negative. These experiments do not establish that LTCG alone explains
the remaining register/tail differences. They led back to the raw900 target
reads and the selected bounded source correction above.
