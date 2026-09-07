# Giant-root instruction and physical-owner audit

## Acceptance boundary

A same-sized switch arm is not necessarily reconstructed. The common Fighter
root supplied three independent counterexamples: `test eax,eax` versus
`test al,al`, unsigned `ja/jbe` versus Boolean `jne/je`, and a same-length
backward jump to the wrong physical owner. None changes an arm's byte count.

`audit-giant-action-owners.py` is a diagnostic companion to the existing target
switch mapper and strict function comparator. It does **not** award partial
function/byte credit and does not write candidate, origin, or match ledgers.
The only acceptance gate remains the complete canonical comparison.

```bash
python3 -m pip install -r scripts/requirements-ci.txt
python3 scripts/check-ida-mcp.py
python3 scripts/build.py --unit gpt-web-fighter-common-action-state --compare --json
python3 scripts/compare-giant-action-switches.py fighter-common-action \
  build/match-units/GptWeb_FighterCommonActionState.obj --json
python3 scripts/audit-giant-action-owners.py fighter-common-action \
  build/match-units/GptWeb_FighterCommonActionState.obj \
  --unit gpt-web-fighter-common-action-state --json
```

The build/comparison command currently returns exit 1 for this nonexact probe.
The audit returning exit 0 means the diagnostic completed, **not** that the
function matched. Its JSON is explicitly marked
`diagnostic_only_not_exact_acceptance` and pins both target and object hashes.
Capstone is pinned to the 4.0.2 decoder used for this checkpoint; the CI
requirements also supply its `distutils` dependency on Python 3.12 and later.

## What the diagnostic preserves

The CLI verifies the canonical target hash, replays the configured relocation
and literal contracts, and pairs target/candidate destinations by the validated
switch cases. It currently requires the selected root at offset zero in its
COFF text section. Split target groups, merged distinct owners, ambiguous
aliases, undecodable bytes, instruction-interior edges, and incomplete owner
partitions fail closed.

Relative direct-control-flow operands are compared by **physical owner name
plus intra-owner byte offset**. External targets retain their exact addresses.
Only the addresses of independently validated destination/index tables are
compared using table identity and offset. Opcodes, register choices, operand
widths, short/near encodings, and other data addresses remain significant.
Thus it cannot hide an `add`/`sub`, `movsx`/`movzx`, branch-predicate, or
wrong-owner difference simply because the operations are related.

The audit counts each physical destination once and adds the dispatcher entry.
For the common root this is **65 destinations + 1 entry = 66 owners**. This
is NOT the older span mapper's 66 rows, which count the cross-region default
twice and omit the dispatcher. Do not interchange their numerators.

The independent raw-code traversal starts at the PE entry, expands only the
validated byte-index switch tables, and follows direct internal control flow.
It records external calls/tail jumps and internal call entries rather than
searching for apparent `E8` bytes inside data or instruction operands. Unknown
indirect exits remain visible; it does not invent destinations for them or
claim to have audited external callee bodies.

## 2026-09-07 common Fighter recovery

Target: `Fighter_update_common_action_state @ 0x004740C0`, original Japanese
TH105 1.06a, SHA-256
`56350024879199861579c11b0e1c67b9590e10a8d40cd5996b109deec9afca7e`.
The callable is `[0x004740C0, 0x004768AB)`, **10,219 bytes**. Source and unit:
`src/battle/FighterCommonActionState.cpp` /
`gpt-web-fighter-common-action-state`.

Fresh baseline and final objects were separately compiled with the pinned VC8
SP1 profile. The retained changes are ordinary C++ source recovery:

| Consumer | Target observation | Retained correction |
| --- | --- | --- |
| Action 70 | Predicate result tested in AL | Narrow this call's result to unsigned char; preserve the callee's established int ABI |
| Actions 97/98 | Four input dwords compared through unsigned `ja/jbe` chains | Preserve unsigned threshold consumers rather than reducing them to Boolean field truth |
| Action 99 | `jbe` enters the zero arm; subtract falls through | Put the `>3` subtract arm first, preserving byte-width state |
| Actions 691/692/694/790 | Eight effect calls zero-extend the stored direction byte | Convert to unsigned char at the int argument boundary; keep signed facing in motion arithmetic |
| Action 63 terminal | The 66/67 and 163..166 consumers enter the case-62 tail | Join the ordinary switch exit with `break`, not the sibling's independent `return` |
| Landing terminals in 72/73/74/75/88 | The publisher/event suffix is physically owned by case 71 | Join the switch exit in these followers; keep the case-71 return as the publisher owner |

In particular, the exact case-62 landing points are `0x00474409` (rounded
clamp store), `0x00474420` (x87 drop), and `0x00474448` (advance terminal).
Before the action-63 exit correction, the candidate routed the corresponding
consumers to the case-63 copies, one 134-byte owner later. After it, all six
consumer owners (66, 67, 163, 164, 165, 166) are instruction/edge-identical in
the diagnostic. No source padding, assembly, register forcing, fake liveness,
or altered helper ABI is involved.

The second recovered owner is the case-71 publisher/event tail at
`0x0047478F`. Changing just the followers' landing terminals to `break`
restores the target case-71 body and shared epilogue routes. It makes six more
owners (71, 72, 77, 700, 704, 799) instruction/edge-identical and loses none of
the earlier identical owners. The final high owner also loses its three-byte
alignment residual. No case body is reassigned to a different action.

| Fresh diagnostic | Initial source | Width/condition recovery | Case-62 owner | Plus case-71 publisher |
| --- | ---: | ---: | ---: | ---: |
| Instruction/edge-identical owners, including entry | 32/66 | 39/66 | 45/66 | 51/66 |
| Candidate destinations / target-group splits | 65 / 0 | 65 / 0 | 65 / 0 | 65 / 0 |
| Old mapper's same-sized rows | 58/66 | 58/66 | 58/66 | 60/66 |
| Summed absolute span residual | 239 bytes | 239 bytes | 239 bytes | 173 bytes |
| Candidate metadata start | +0x282C | +0x282C | +0x282C | +0x2840 |
| Candidate text section tail | 10,789 bytes | 10,789 bytes | 10,789 bytes | 10,809 bytes |

**Correction to older handoffs:** repeated `+0x27E4` descriptions are stale for
the 10,789-byte baseline. A fresh rebuild of the pre-change source puts the
first metadata table at **+0x282C**. The retained publisher correction makes
it **+0x2840**, while target remains **+0x27EC**. The final metadata placement
is 20 bytes farther from target than the initial baseline, but absolute owner
span error falls by 66 bytes and 19 more owners are instruction/edge-identical.
This tradeoff is explicit: preserving the independently verified physical
publisher owner is progress, not a claim that aggregate text size matched.
The candidate pre-table span may include generated alignment and must not be
reported as newly exact authored code.

Formal comparison still fails normally, with complete relocation/literal
closure, at **root +0x14 / 0x004740D4**, target byte **48**, final candidate
**9D** (initial baseline **86**). The 10,219-byte root stays source-present/
nonexact. The local audit improvement adds **zero** accepted functions and
**zero** accepted authored bytes.

## Bounded candidate-boundary recheck

Fresh IDA attestation/typed evidence was checked against raw canonical PE
control flow. The independent traversal reaches **2,799/2,799 instructions**
and **10,219/10,219 callable bytes**, with no unvisited ranges and no internal
direct-call subentries. Both known switch dispatches are traversed.

All **16 distinct direct external targets** already have candidate ledger
entries; fourteen have accepted authored implementations and the remaining two
are the known deque subscript (`0x004399C0`) and conversion runtime
(`0x0068A1A0`). The generated report includes each target's separate origin
record, so an unclassified candidate status is not confused with authored
origin. No new candidate or authored classification is justified by these
particular direct edges.

There are still **eight register-indirect exits** in this traversal. Their
resolved polymorphic owner sets are outside this bounded check. This is not
proof that the entire image inventory is complete, nor that all indirect
callee implementations are exact. Continue the global review census separately;
do not shrink its denominator because this root's direct-edge closure passed.

## Cross-root smoke check: an unexpanded nested switch is not a new function

The same CLI was exercised against the existing Youmu/Aya Object action-entry
probe objects without recompiling those unrelated sources. This tests tool
reuse, not fresh source exactness. Aya's raw target traversal reaches all
4,531 callable bytes. Youmu's main-table-only traversal reaches 5,083 of
5,159 bytes and explicitly reports the indirect jump at `0x0054464F` plus the
unreached interval `[0x00544656, 0x005446A2)` (76 bytes).

Fresh IDA xrefs to `0x00544656` identify both the jump at `0x0054464F` and a
data reference from `0x00544BD4`. Independent pinned-PE decoding confirms
`cmp eax,3; ja 0x005446A2` followed by the indexed jump through that table.
Its four dwords, in index order, point to `0x00544692`, `0x0054467E`,
`0x0054466A`, and `0x00544656`. These are the four existing action-901,
sequence-6 `g_match_identifier` arms in `YoumuObjectActionEntry.cpp`; they
write the +0x366/+0x368 state pairs and rejoin at `0x005446A2`.

These 76 bytes are therefore not evidence for a new authored function. The
unmodified automatic report intentionally leaves the supplemental table
unresolved because only the configured main action tables are expanded.
Do not silently add arbitrary table edges, call the partial traversal complete,
or promote unreachable spans to candidates without tracing their incoming
control flow. This is a concrete additional inventory check, with no candidate,
origin, source-present, or exact-count promotion.

## Rejected source hypotheses and next discriminator

The new diagnostic also prevents a more attractive local count from concealing
a global regression. A complete natural action-0 cohort made the early
53/54/55/56 owners identical and reached 50/66 diagnostic owners, but expanded
159..162 to **146 bytes each versus target 61** and moved metadata to
**+0x2930**. It was rejected at the earlier 45/66 checkpoint rather than retained for its
higher local count; it is not part of the final 51/66 source.

Target-rounded nested/independent case-50 clamp variants were retested with the
actual per-operation float conversions, rather than assuming older probes had
preserved those lifetimes. The nested form shrank case 50 to 49/134; the
independent 159..162 form expanded each to 146/61. Sharing a real float scalar
instead removed required x87 spill/reload structure. None is retained.
Changing the case-62 exit was neutral; changing case 64 damaged the 66/67
spans. Individual case-50/51/52 or shared-terminal exit changes were neutral.
Nested casts and successive member updates in the rejected action-0 cohort did
not restore its 159..162 backward-owner chain.

The remaining early discrepancies include the selector encoding, the
case-73/75/88 sequence ownership, and the case-50 versus case-162 clamp owner.
The case-71 publisher ownership is now recovered. Independently inlining the
sequence followers was rejected: it restores the 73/88 span sizes but expands
case 75 to 195/148 and misplaces shared epilogues. Rewriting the action-74
advance terminal to `break` alone is byte-neutral. Some later differences are shared epilogue anchors and final
alignment. These are **observed unresolved source/code-generation differences**,
not proof that source-only recovery is exhausted or that LTCG alone explains
every mismatch. The successful case-63 and publisher corrections are counterexamples to the
older blanket blocker conclusion. Inspect instruction and edge identities
before launching another size-only spelling matrix.

## Replay artifacts and regression tests

Private local evidence for this checkpoint is under
`.analysis/gptweb-common-owner-audit/`: `typed.json`, independently cold-built
`baseline.cpp` / `baseline.obj`, `audit-baseline.json`, `audit-final.json`, and
`formal-final.json`. These files contain proprietary target observations or
build products and are intentionally not committed. The commands above
regenerate the durable diagnostic from a locally supplied target/toolchain.

`tests/test_giant_owner_audit.py` supplies 24 synthetic, target-independent
regression tests for opcode/width retention, owner identity, switch address
proof, alias accounting, invalid partitions, raw traversal, and unresolved
indirect exits. Their small instruction fixtures are test inputs only and are
never linked into reconstruction sources or used to manufacture exact bytes.
