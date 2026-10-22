# AyaObject900 shared animation-tail placement, 2026-10-22

## Selected source structure

This continues the [sequence5 checkpoint](AYA_OBJECT_900_SEQUENCE5_AND_LOOPS_2026_10_22.md)
on update61A290. Raw Japanese1.06a bytes place the shared animation advance
at61DC9E, immediately after sequence1/2's related-object coordinate copy.
Other sequence/default paths jump back to it. The retained source placed that
real tail after the entire sequence switch; native VC8 selected a later physical
owner and shared the movement tails differently.

The source now locates the existing tail after sequence1/2 and represents its
actual incoming edges with `goto aya900_advance`. No computation is duplicated,
no inert local is introduced, and no calling convention/layout/flag changes.
This models an observed graph; it does not establish the original C++ spelling.

| Complete-root control | Full bytes | Canonical SHA256 prefix |
| --- | ---: | --- |
| Previous structured breaks |20056|8b221c5c|
| Explicit edges to the same late tail |20056|8b221c5c|
| Duplicate tail in sequence1/2 |20128|43dbc6e9|
| Single shared tail after sequence1/2, selected |20060|2d034e48|

The selected action900 physical region now has target size1773 and412
instructions. It was1770/412 immediately before this control. Size equality
is not acceptance: owner audit still reports two switch-table addresses,
four stack-displacement operands (ESP+18 versus+14), and two conditional
edges to another shared next-sequence exit. No other instruction differences
remain in that physical region under the existing owner diagnostic.

The complete selected root remains nonexact+0x22. Canonical full20060 SHA256:
`2d034e48a8060bba7c9989b29fbc963993a82e5caf5b5fe5a480866b6b39aded`.
Metadata starts19592 versus target19524; owner diagnostics remain3/34.
Target callable remains19522 bytes/4630 reachable instructions/seven switches.
No exact ledger credit, original-TU proof or aggregate cold replay is claimed.
IDA preflight rejects its image; this work uses the independently attested PE.

## Full source-graph preservation

`scripts/audit-aya-object-normal-flow.py` compares old and new relocated roots
from their real entries. All4570 paired instruction-labelled nodes agree.
Only direct internal unconditional JMPs are contracted. Registers, memory
operands/widths, constants, external callees, conditional branch mnemonics,
ordered taken/fallthrough edges, return cleanup, seven checked switches and
index bytes remain significant. Metadata addresses are translated by their
relative table positions. The comparison does not normalize stack offsets.

The graph includes all switch alternatives, not only action900. Opaque calls
are assumed to return normally; it does not execute callbacks, prove exceptions,
or equate either source graph with the target. Machine encoding differences
between equivalent instruction forms are outside this diagnostic, so it cannot
replace the canonical comparator.

## Executed original animation tail

The retirement audit now also allows only the real62-byte helper4351C0.
New2880 cases cover sequences1/2/5 and out-of-range6/-1, counters-1/0/19,
frame-counter0/-1/32767, frame-index0/1, facing+/-1, two coordinates and eight
masked x87 precision/rounding words. The frame limit32767 keeps these paths
below the helper's virtual-call threshold after the actual WORD increment.
Each new execution must enter that real helper exactly once and reach the
original root RET; any unexpected code destination is rejected.

All10840 cases (previous7960 plus2880) agree against the target in fixture
memory, ordered writes, owner-read epochs, x87 status/tag, preserved registers
and stack cleanup. Previous and selected sources also agree throughout.
This includes counter wrap/zero checks and the sequence5 retirement condition
after the helper, but not virtual frame/sequence callbacks or unmasked exceptions.
The previous20 alias cases remain explicitly artificial raw-memory stress.
Five translated owner-read intervals and the599-byte/four-CALL spawn-loop
comparison also continue to pass.

```bash
python3 scripts/build.py --unit gpt-web-aya-object-vslot28-full-root --compare --json
python3 scripts/audit-aya-object-900-retirement.py
python3 scripts/audit-aya-object-normal-flow.py OLD.obj \
  build/match-units/GptWeb_AyaObjectActionState.obj
python3 scripts/audit-giant-action-owners.py aya-object-vslot28 \
  build/match-units/GptWeb_AyaObjectActionState.obj \
  --unit gpt-web-aya-object-vslot28-full-root --json
```

The canonical comparator intentionally remains nonzero. Private complete-source
controls are under `.analysis/aya-900-tail-20261022/`, objects/reports under
`build/aya-900-tail-20261022/`. The selected configured-source results are
`selected-formal.json`, `selected-owner.json`, `selected-graphs.json` and
`execution.json`. Local CI and whitespace gates apply before commit/push.
Remaining concrete900 leads are the two scratch homes and next-sequence exit
sharing; wider root placement and other actions remain unresolved.
