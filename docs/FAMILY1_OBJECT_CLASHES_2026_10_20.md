# Family1 object traversal46DD40: complete686-byte exact recovery

## Canonical target and role

Only original Japanese TH10.5 v1.06a is used, executable SHA256
`56350024879199861579c11b0e1c67b9590e10a8d40cd5996b109deec9afca7e`.
The dispatcher is `[46DD40,46DFEE)`,686 bytes/192 decoded instructions,
SHA256 `aa250ed95904cbc1b0d78f04b2f4a09ef1bcd53f844cc298140474e89f2ea8ec`.
Raw CFG closes the complete span with one RET0, no external branches,
switch metadata or remote owned chunks. The reviewed parent46DFF0 calls it
at46E48B with ECX context. Both out-of-line pair calls at46DE75/46DFB7 pass
the same context plus two pointer stack slots; the542-byte pair resolver46CA80
has RET8 exits. The caller discards its result.

The function traverses the two lists at context44/50. The first phase handles
ordered same-side pairs when the outer object's prepared frame50 has100000h;
frame4C bits40h/80000h and byte1A0 filter each object, and equal payload pointers
are skipped. The second phase traverses list0 against list1 with those filters,
without the first phase's frame50 gate or payload-inequality test. Object1A4
supplies the prepared frame. These are observed grouping/filter roles, not
new gameplay names or an assertion of the original complete C++ class.

## Natural source and strict acceptance

The old unselected `Family1Clashes.cpp` manually implemented iterator checks.
It emits664 bytes and misses checked owner behavior in the cross-side phase.
The replacement uses genuine `std::list<void*>` iterators, with no hand-written
sentinel assertion, inert owner local, copied code or padding.

| Fresh source control | Whole dispatcher |
| --- | --- |
| Retained manual checked iterator |664 bytes, first+2 |
| Native containers, explicit list pointer, end before begin |686 bytes but nonexact; first+7 |
| Native pointer traversal, begin before end |686 bytes but nonexact; head-pointer induction still differs |
| Direct `family_1[slot]` indexing plus begin-before-end lifetimes |686/686 canonical exact |

The indexed first phase retains the full list-owner relation. The explicit
pointer version folds its induction to the head field, changing the prologue,
comparisons and alignment. Begin/end order also explains the observed node
loads before saved end-node bindings. Native headers naturally reproduce all
25 invalid-parameter call sites, including two owner-compatibility guards that
compare a register with itself. No check is manually removed or synthesized.

`gpt-web-family1-object-clashes` freshly builds
`src/battle/Family1Clashes.cpp` under pinned VC8 SP1 `/O2 /GS- /GR /EHsc /MT`.
The strict comparator reports equal686-byte COFF extent, no differing bytes
and identical target/canonical SHA256. Its two REL32 roles are the standard
invalid-parameter routine68A143 and genuine pair member46CA80. Runtime prefix
assertions pin list44/12-byte stride and object1A0/1A4. Original class/TU
identity remains unknown; the durable role is
`BattleCollisionPhase_dispatch_family1_clashes`.

The accepted dispatcher moves to the canonical-exact authored baseline. The
old combined origin rule now selects only the remaining542-byte pair resolver;
its two matching dispatcher callers and eight exact reset-helper witnesses
remain pinned. Neither pair execution nor a matched caller makes46CA80 exact.
Authored/excluded totals do not change; one686-byte authored exact result is
added. No cold aggregate replay is claimed.

## Parent-context and narrow-tail controls

A private closed source experiment puts the genuine686-byte member definition
before the complete46DFF0 caller, using one truthful context and refined
prepared-frame/object fields. The dispatcher remains exact686/686. The caller
retains the complete1449-byte canonical payload ea3990e6 and first+559; merely
making this member definition visible does not resolve its tail.

New caller controls also preserve the selected tail failure: direct unsigned
word carriers, low-word extraction, overlapping word-storage views, pre-guard
narrow locals and external type visibility. A repeated cap expression reaches
1452 bytes but changes the frame to28h. A by-value three-short policy also
reaches1452 bytes, with31 differing bytes and the early narrow carrier on the
maximum rather than the pending delta. These witnesses are not selected and
do not prove an original helper, source spelling or LTCG requirement.
The parent remains source-present/nonexact; this checkpoint accepts46DD40 only.

## Native execution

`scripts/audit-family1-object-clashes.py` reuses the bounded environment from
the parent auditor. The original parent first prepares valid object geometry;
its node allocator/free environment callbacks are limited and disclosed there.
The standalone dispatcher entries then execute original game, pair and
geometry instructions, with no supplied dispatcher/pair result or code patch.
The child phase itself must perform no allocation. Code/resources are read-only
while native writes stay within the fixture arena/stack/SEH cell.
The subsequent collision-phase v2 review corrects source168 ownership in the
parent seed and rejects non-SEH zero-page reads. This226-record child matrix
replays with zero mismatches after that change; refreshed receipts are under
`build/collision-tail-20261020/family1-final.json`. The canonical source and
686-byte exact result are unchanged.

The full matrix has226 records: zero/one/two nodes per side, three same-side
flag patterns, four suppression/active patterns, separated or overlapping
prepared boxes, varying signed priority words and duplicate payloads within
one list. Each record resets from the same original-parent snapshot and
compares all128KiB of arena bytes, ordered direct calls, real return/ESP,
nonvolatile registers, restored SEH/x87 state and MXCSR. Target helper542 and
its actual predicate/extent routines execute even on overlap paths; no hit
answer is supplied by Python.

The driver records target/source instruction coverage, unvisited offsets,
helper hashes/counts and observed pair-return sites. Full coverage requires
all dispatcher instructions except the25 invalid-parameter calls. Bad
containers, allocation/throw failures and arbitrary game states remain outside
this finite execution claim. Existing-object build provenance is reported as
unverified; the fresh formal producer independently records source/compiler/
object/input hashes. Canonical acceptance comes from the strict comparator.

The final226-record run passes with zero mismatches and167/192 dispatcher
instructions visited on both sides; the remaining25 are exactly the invalid
parameter calls. Pair resolution and its predicate execute186 times per side;
actual AABB tests and extent resets execute93 times each. Seven of the pair
resolver's eight physical return sites execute. That sampled helper coverage
is not a source or exact claim for46CA80.
The subsequent [standalone pair review](FAMILY1_PAIR_RESPONSE_2026_10_20.md)
covers the missing46CB74 path and selects source after2638 native cases;
the pair remains557/542 nonexact. It does not change this traversal's exact
acceptance or add new aggregate exact bytes.

A guarded source negative control reverses the payload inequality in the first
phase and fails9/15 smoke records. It is compiled at the original source path and restored before auditing,
so anonymous namespace identities stay stable. This tests the real same-side
identity filter, separately from whole-body byte comparison. Private recipes
and generated reports are retained below the analysis/build directories.

## Analysis safety and reproduction

A direct read-only128MiB/CPU0 Ghidra pass independently re-attests the original
file/imported identity, entry point, full mapped text,686-byte root and inbound
46E48B call. It reads back ECX/void signatures for the dispatcher and the
context/two-pointer pair contract. All nine primary database hashes remain
unchanged; disposable metadata is discarded. Decompiler text is a hypothesis.
IDA preflight still rejects the wrong open image; no IDA semantics or factory
adapter is used.

```bash
python3 scripts/build.py --unit gpt-web-family1-object-clashes --compare --json
python3 scripts/audit-family1-object-clashes.py \
  build/match-units/GptWeb_Family1ObjectClashes.obj
python3 scripts/validate-tracking.py --require-target
python3 scripts/check-match-literals.py --require-target
python3 scripts/ci.py
git diff --check
```

Focused build returns0/exact. The audit returns0 for the supported matrix;
`--smoke` selects15 records. Reports, raw instructions and DB receipts are
under `build/family1-clash-20261020/`; source/closure controls and guarded
negative recipes are under `.analysis/family1-clash-20261020/` and
`.analysis/collision-phase-20261020/`.
