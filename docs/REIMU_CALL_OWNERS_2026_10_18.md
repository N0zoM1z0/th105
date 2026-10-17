# Reimu root: action 619 branches and action 695 effect sequence

## Scope and identity

This is bounded source-shape work on `Reimu_dispatch_action_state_vslot28`
at `478FA0`, callable `[478FA0,48CE2E)` (81550 bytes), in the original JP
1.06a executable SHA256
`56350024879199861579c11b0e1c67b9590e10a8d40cd5996b109deec9afca7e`.
The callable SHA256 remains
`dbf6f375a809fea91cbbccf0f8cff2196f40cba11458c98e475a290b623053e6`.
IDA preflight still identifies another executable, so it was not used. Raw
attested PE instructions, the qualified root CFG, and pinned VC8 SP1 COFF
probes supply the observations below. No analysis database was opened; all
nine primary database file hashes are unchanged.

## Observations and source recovery

A CFG census starts at all 128 nondefault primary action entries, follows
shared tails and guarded loop edges, and counts distinct reachable direct
call sites by callee. This is a static overapproximation: it does not prove
call order, dynamic multiplicity, returned-world behavior, or equivalence.
Before this change, five actions had differing per-callee cardinalities:

| Action | Callee | Target sites | Previous source | Current source |
| --- | --- | ---: | ---: | ---: |
| 400 | `45C030` wave handle | 2 | 1 | 1 |
| 404 | `45C030` wave handle | 2 | 1 | 1 |
| 406 | `45C030` wave handle | 2 | 1 | 1 |
| 619 | `435D60` surface height | 2 | 1 | 2 |
| 695 | `435240` fighter effect | 5 | 3 | 5 |

All other per-action direct-callee cardinalities agree. Whole-root physical
call totals still differ because call sites can serve multiple action
entries; neither this census nor aggregate call totals establishes missing
behavior by itself. The three wave differences remain open sharing cases.

For action 619, target sine call `48A185` feeds the zero comparison and
`JNE 48A1C5` at `48A19A`. The positive path pushes arg5=-1 at `48A1AB`,
then calls height at `48A1B0`; the nonpositive/unordered path pushes arg5=1
at `48A1D4`, then calls height at `48A1D9`. Both paths join the one object869
request at `48A203`. Each path's facing/pointer/arg5 pushes precede its
height calculation. The source now uses two explicit request branches,
rather than a ternary arg5 feeding one request expression. The candidate
has corresponding height calls `48A226`/`48A24F`, arg5 pushes
`48A221`/`48A24A`, and joined request `48A279`. The CFG check follows each
branch to its first request and resolves the actual arg5 stack slot.

For action 695, target event55 call `48AE61` is followed by five consecutive
effect calls at `48AE9B`, `48AED5`, `48AF0F`, `48AF48`, and `48AF73`:
140,140,140 with trailing1, then141,142 with trailing-1. Each call reloads
live coordinates and facing. There is no intervening loop. The source now
spells the first three calls separately. Its five calls are `48AF2A`,
`48AF64`, `48AF9E`, `48AFD7`, and `48B002`. The 67-instruction linear
sequence `[48AE66,48AF78)` versus `[48AEF5,48B007)` has two operand
substitutions: `PUSH EBX` becomes `PUSH EBP` for the trailing-1 arguments.
Every reaching full-width definition of those registers is `OR reg,-1`.
All other mnemonics and decoded operands agree. PC-relative encodings and
absolute instruction addresses still differ; this is not a canonical unit
match or byte credit.

The old loop also requested three140 effects, and the old ternary selected
the same signs. These edits recover observed control structure; they do
not establish that the previous sampled behavior was wrong. Original
source spelling and the contribution of LTCG remain unknown.

## Trigonometric return-type control

Raw helpers `406360` and `4063D0` end in an m32 table load into ST0 and RET.
Their modulo divisor is3600. That return mechanism alone does not determine
whether the original source return type was float or double. Action619
compares with m32 zero at `48A18A`; the current retained double declaration
produces m64 zero at candidate `48A200`.

An unselected private-header float control, based on preceding object
`598a6a781279c59870710c024f750bd783b316528e0a2e95907c4beec010314d`,
produced object
`1dfeb275a86674c12183ab16ea7061e5ae5f829f4e13b38a3740a30de675029c`.
It used all160 bound numeric values, including m32 zero, but retained the
81668-byte code prefix,83040-byte text,2464 relocations, and first strict
mismatch at478FB1. Return-type changes also affected other callers/layout;
this was not a single comparison-byte change. The control was not executed
or selected. Shared declarations, helper implementations, accepted units,
and the relocation ledger remain unchanged. Repeating this type experiment
without new ABI/LTCG evidence will not resolve the size failure.

## Build and verification

Current expanded object SHA256:
`bccd5229742eaab8ee095eb2a130d752c51d5da12475fb60d41681bdb88dd553`.
It has code prefix81716/text83088,126 unique primary destinations/no splits,
1176 E8 calls versus target1188, and2465 fully qualified relocations:
1176 calls,1105 numeric,14 metadata addresses,163 local code pointers,
7 global reads. Both root stack frames are570h. Nine request-buffer
partitions pass. First strict mismatch remains +17/478FB1: source zero
factoring before PUSH EDI. Code exceeds the callable by166 bytes and text
exceeds the original metadata envelope by164 bytes,48 more than before.
Ordinary audits and execution reject the expanded size; explicit oversize
mode is read-only and grants no acceptance.

The independently compiled compact void witness is50744 text bytes, SHA256
`6b480807c382b9409547f39b08eba929d281a752902b6c02f02d20a2c27e7441`.
Fresh integration replay has **0/1010 differences**, input SHA256
`4b34af13b5e3d70775b6a3d3d5fe4e1aa4b39339b6d2d6f50a14d521be26f50b`:
890 RET,82 object requests,30 effect requests,7 common calls,1 set669 stop.
It includes13 inputs each for619 and695, including their object869/first140
request paths. Actual original helpers execute until RET or the first real
world boundary; later effects, later loop iterations after a request, and
returned-world contexts are not proved. The bool staging source also builds.

```bash
python3 scripts/probe-reimu-action-source-shape.py --void-root --output-dir build/reimu-call-sharing/current-expanded
python3 scripts/audit-reimu-root-relocations.py --diagnostic-oversize build/reimu-call-sharing/current-expanded/ReimuActionStateDispatch.obj
python3 scripts/audit-reimu-root-stack.py --diagnostic-oversize --require-contracts build/reimu-call-sharing/current-expanded/ReimuActionStateDispatch.obj
python3 scripts/probe-reimu-action-source-shape.py --compact --void-root --output-dir build/reimu-call-sharing/current-compact
python3 scripts/audit-reimu-void-root.py build/reimu-call-sharing/current-compact/ReimuActionStateDispatch.obj --cohort integration
```

Local `build/reimu-call-sharing/` retains source/compiler/build receipts,
`census.py`, baseline/current call ownership, branch/linear instruction
packets, stack contracts, relocation and native reports. Rejected private
float build products and superseded duplicate emissions were removed;
current witnesses and the preceding negative baseline remain. Generated
reports are not committed. No aggregate cold replay, accepted-unit change,
source selection, or exact credit was made. Next recover physical call
sharing, source overhead and compiler/LTCG ownership with new evidence.
