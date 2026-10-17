# Reimu400/401/404/406: mode capture before shot costs

## Observed target control flow

Target is original Japanese TH10.5 v1.06a, SHA256
`56350024879199861579c11b0e1c67b9590e10a8d40cd5996b109deec9afca7e`.
Root478FA0 remains81550 bytes, body SHA256
`dbf6f375a809fea91cbbccf0f8cff2196f40cba11458c98e475a290b623053e6`.
The root remains authored, unclassified and declaration-only. No source/exact
credit, accepted-unit or aggregate-total changes.

Each of these four action entries increments the signed WORD730, computes
its signed remainder once, then separates BYTE750's ordinary/random paths
before testing the remainder/WORD732 and applying shot costs. Each path owns
its state180 store, initial counter adjustment, scaled-counter work, parameter
array, request, wave0 call and WORD732 increment. The earlier source shared
the cost block before reading the mode and shared its wave/increment suffix.

| Action | Target mode compare | Current source compare | Target random-loop backedge |
| --- | --- | --- | --- |
|400|47DBB1|47DB6A|47DDC3 ->47DD20|
|401|47E0F4|47E088|47E305 ->47E262|
|404|47E86F|47E639|47EA8B ->47E9E8|
|406|47EE6E|47EBE4|47F08A ->47EFE7|

The target random loops start at2, subtract1 after each request and continue
on nonzero. Every loop contains two actual selector_random_range sites and
one object800 request site. Counter-register entry definitions and the real
CFG backedge establish the count; a backward physical jump to a shared return
tail is not a loop. Ordinary and random paths retain distinct three-float
buffers, with the random buffer reused across its two requests.

## Source inference and compiler evidence

Only `ReimuActionStateMidProjectileCases.hpp` changes. The two mode blocks now
each contain their own remainder/limit gate and complete firing work. Existing
helper ordering, short wrap, actor/peer reads, per-request random updates and
parameter initialization remain. The local loop is written as countdown2
with a nonzero condition. The earlier increasing spelling also compiled into
two iterations; this is not a claim that it emitted the wrong request count.

Target/source action-entry traversal now shows that the mode branch dominates
every shot-cost call in all four current arms. The preceding source fails
that ordering fact in all four. Both old and current emitted loops have
initial value2 and decrement value1; source register constants are resolved
rather than mistaken for literal operands. A private greater-than-zero loop
control emitted TEST/JG and was discarded in favor of the observed nonzero
condition. No dummy local, forced register, padding, fake helper or ABI change.

The unchanged official map retains126 primary destinations and11 switches.
Current expanded object SHA256 is
`598a6a781279c59870710c024f750bd783b316528e0a2e95907c4beec010314d`.
Frame remains570h. Decoded direct-call count changes1168->1178 versus target1188;
the count also reflects compiler sharing in other arms and is not byte credit.
Counter482/scaled-counter counts now agree with the target, while wave and
other call-site sharing still differs.

The expanded prefix/text are81668/83040: **118 bytes beyond the target callable
and116 beyond its reviewed metadata envelope**. All2464 relocations classify
and replay in a read-only diagnostic. First strict mismatch remains478FB1/+11h,
zero-register sharing. The size failure is retained; this is not an exact
result, accepted source boundary or executable expanded witness.

## Verification without enlarging execution bounds

```bash
python3 scripts/probe-reimu-action-source-shape.py --void-root --output-dir build/reimu-projectile-branches/current-expanded
python3 scripts/audit-reimu-root-stack.py build/reimu-projectile-branches/current-expanded/ReimuActionStateDispatch.obj --diagnostic-oversize --require-contracts
python3 scripts/probe-reimu-action-source-shape.py --void-root --compact --output-dir build/reimu-projectile-branches/current-compact
python3 scripts/audit-reimu-root-stack.py build/reimu-projectile-branches/current-compact/ReimuActionStateDispatch.obj --native-only --action 400 --action 401 --action 404 --action 406
python3 scripts/audit-reimu-void-root.py build/reimu-projectile-branches/current-compact/ReimuActionStateDispatch.obj
```

`--diagnostic-oversize` permits only read-only COFF classification/CFG facts.
The ordinary relocation audit still rejects this expanded object. Both
execution flags reject combination with the oversize diagnostic, and
`--native-only` rejects the expanded83040-byte object independently. No canonical
comparator, target boundary, relocation ledger or native execution envelope
was relaxed.

`--compact` preserves the input's existing case sharing, without cloning the
three source regions. It still verifies the128 nondefault keys, emits a real
void/default method and private checked header, and uses the same compiler
profile. Default expanded emission was checked unchanged before the source
edit. Compact receipts have empty owner groups/no target-map claim; stale
mapping output is removed. `--native-only` requires the entire compact text
to fit inside the original callable window and cannot claim expanded contracts.

Current compact text is50584 bytes, object SHA256
`368dce8668c099bc26589be68f0117fbb0a81089d36f75344e64eca03776336d`.
Its complete canonical-replayed bytes and all relocation records are identical
to the earlier private compact object that passed **0/2312** affected inputs.
The native adapter source is unchanged from4fd3772. This concrete binary
equivalence reuses that run rather than inventing a new execution report.
Its input SHA256 is
`ff1f97a91db8f89632196fc2db6f16b13f6e4f0fb46040403a6d896f9ba6b902`;
stops are1732 actual RETs,568 object-request entries and12 effect entries.

Fresh current compact void passes **0/1544**, with unchanged input SHA256
`c61982a9ccc694e3b6667371b5a4882e896da92d11320dd4aa3784f464787b80`.
Fresh bool passes0/12 smoke and0/8 indeterminate740 boundaries. Earlier
710/711/720 static loops,48 510 packets/12 reloads and all9 buffer partitions
pass. Helpers, MT/actor state and first pointed payloads are real; returning
world calls and complete random-loop iterations remain outside native proof.

Envelope controls reject unsafe/contradictory modes as expected. Two new
target-independent regression tests protect read-only oversize mode and the
absence of an owner-contract claim in native-only mode. No historical/full
aggregate cold replay was run.

## Handoff

Bounded branch/counter facts, equivalence receipts, matrices and source/compiler
hashes are under build/reimu-projectile-branches/. Raw PE supplies the new
facts; no IDA semantics or new Ghidra process/clone. All9 primary database
hashes remain unchanged under the prior attestation. Superseded objects,
prototype sources and caches are cleaned. Keep the full expanded size failure
visible while recovering remaining call sharing/source overhead and returning
world contexts; canonical root acceptance remains pending.
