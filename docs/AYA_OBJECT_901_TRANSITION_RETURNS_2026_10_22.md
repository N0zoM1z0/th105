# AyaObject901 transition returns and alpha read, 2026-10-22

## Target-backed correction

In update61A290, action901 sequence0's branches61E03A/61E04D reach61BCF1;
sequence3's61E263/61E276 reach61A368. Both destinations call vtable slot14
and then restore registers/frame and RET. The retained source instead called
`next_sequence_block()` and continued into speed decay, oriented movement and
animation advancement. Both call sites now return immediately.

This is a real control-flow correction, not a code-size or first-mismatch
optimization. Raw facts come from Japanese1.06a SHA256
56350024879199861579c11b0e1c67b9590e10a8d40cd5996b109deec9afca7e.
IDA preflight rejects its image and is not used. The AyaObject vtable6C624C
slot14 is independently read as45C220, the original next-block function.

Sequence2 additionally snapshots the actual alpha byte before its two scale
updates. Target61E18F loads the first scale,61E195/61E19B read/compare alpha,
then61E19D..61E1B3 update scales before deciding whether to retire or subtract5.
The previous source read alpha after both stores. A consumed unsigned-byte
snapshot recovers that target ordering without changing the0.1f expression.

| Complete source | Full bytes | Canonical SHA256 prefix |
| --- | ---: | --- |
| Previous shared-tail source |20060|2d034e48|
| Two immediate returns |20056|4238bb2e|
| Plus early alpha snapshot, selected |20056|b505fec8|

No shared type, ABI, compiler flag, TU partition, helper or relocation ledger
is changed. The complete root remains **nonexact at+0x22**, target0F/source51.
Full canonical SHA256:
`b505fec8d12efd152ff17ab8d5d093fc1ef28eb06f7a9af39959e41db76a9c40`.
The configured19522-byte window SHA256 is
`fd9167665b150d12d07a5a9d41f31b18b9aafcc14922bb07831c209faa80ab63`;
metadata starts19588 versus target19524.

The physical901 region now has1168 bytes/293 instructions, equal to target;
previously1170/301. The owner diagnostic leaves one table operand and four
relative edges to differently placed shared code. Its all-owner diagnostic
count is4/34, which is not canonical function acceptance. Target traversal
still closes4630 instructions/all19522 bytes/seven switches. Exact ledgers
and aggregate strict totals are unchanged.

## Actual transition execution

`scripts/audit-aya-object-901-transition.py` uses a concrete animation fixture
and original target instructions for phase-counter64CD00, next-block45C220,
frame application and texture-null sprite operations. It uses the actual Aya
vtable, advances real block/frame records, and checks receiver, writes, real
root RET, stack cleanup and preserved registers. Animation resources are
read-only; writes are limited to actor, its actual parameter record and stack.
No helper return is fabricated. Used helper ranges/hashes are in the report.

All780 transition cases pass against the target. They exercise sequence0/3,
six phase values, zero/negative owner health, four amplitudes and eight masked
x87 precision/rounding words, plus positive-health cases for nonzero phases.
Every target and selected execution calls the real next-block helper once and
returns from the root. Every predecessor execution instead proceeds to435160
oriented movement, where the audit stops before executing that unexpected
helper. Thus780 denotes demonstrated continuation differences on the fixture,
not old-source full-return executions or a claim about arbitrary game assets.

All5760 additional sequence2 cases pass, crossing five alpha values, twelve
scale-X bit patterns, twelve scale-Y bit patterns and eight control words.
Scale inputs include signed zero, subnormals, finite boundaries, infinities,
quiet NaN and signaling NaN. The predecessor differs in alpha-read timing;
this is not a demonstrated normal-value output bug. Cases with alpha>=5
execute the original animation-advance helper below its virtual-call threshold.

The combined6540 cases compare actor/parameter memory, ordered writes, alpha
read epochs, helper traces and x87 status/tag. Unmasked exceptions, textured
assets, arbitrary callback graphs, spawn cases and whole-root equivalence
remain unproven.

## Other-action preservation and reproduction

The source graph checker now supports one explicit `--exclude-action`. It
verifies that the requested primary entry is unique, skips only that paired
entry, reports the exclusion, and retains all other switch/edge checks.
With901 excluded,4285 paired normal-return instruction nodes agree against
the previous object, including the dispatcher and other action paths. This
cannot prove callback/exception behavior or replace target comparison.
The existing10840 action900 executions are replayed against the selected root.

```bash
python3 scripts/build.py --unit gpt-web-aya-object-vslot28-full-root --compare --json
python3 scripts/audit-aya-object-901-transition.py
python3 scripts/audit-aya-object-900-retirement.py
python3 scripts/audit-aya-object-normal-flow.py OLD.obj \
  build/match-units/GptWeb_AyaObjectActionState.obj --exclude-action 901
python3 scripts/audit-giant-action-owners.py aya-object-vslot28 \
  build/match-units/GptWeb_AyaObjectActionState.obj \
  --unit gpt-web-aya-object-vslot28-full-root --json
```

The canonical comparator intentionally reports mismatch. Optional
`--previous-object OLD.obj` adds the finite predecessor contrast to the901
execution audit. Private prior source is in `.analysis/aya-901-return-20261022/`;
objects/reports are in `build/aya-901-return-20261022/`. Selected evidence is
`selected-formal.json`, `selected-owner.json`, `selected-execution.json`,
`other-graphs.json`, and `regression900.json`. Local CI and whitespace gates
are mandatory before commit/push. No aggregate cold replay is claimed.
