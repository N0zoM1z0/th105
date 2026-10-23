# AyaObject807 angle lifetime at the alpha write

## Observed target and source recovery

Original Japanese1.06a SHA256:
`56350024879199861579c11b0e1c67b9590e10a8d40cd5996b109deec9afca7e`.
Startup target/tracking checks pass; IDA still rejects the wrong-image session.
New observations use the hash-attested PE and complete native VC8 objects.
Root61A290 remains the19522-byte bounded callable, not an accepted exact root.

For807 sequence1, target61A86D loads angle field12C into x87. SUB AL,15 at
61A873 precedes FADD10.0 at61A875;61A87B then writes alpha113, and61A881 stores
the computed angle back to12C. Thus the live sum spans the alpha write.
The previous source subtracted/stored alpha before evaluating the angle sum.
Its generated ordered memory writes and final values agreed on tested paths,
but the x87 state at the alpha write did not.

Selected source computes a used `double const next_angle`, subtracts alpha,
then stores the converted angle. This real value lifetime generates the exact
26-byte target interval61A86D..61A886 at candidate61A87B. No extra spill/reload,
inert local, assembly, fake return, ABI or shared header change is introduced.
This is evidence for the lifetime; it does not establish original source spelling
or unmasked exception delivery.

## Original-code execution

`scripts/audit-aya-object-807-angle-lifetime.py` extends the guarded804/903/901
fixture and executes the original gate and animation helpers. It observes
complete actor/parameter memory, ordered writes, calls, alpha reads, final
x87 status/tag, WORD13E read epochs, and live x87 registers/status/tag plus
angle bits at each alpha write.

3968 cases cover sequences0..3, phases0/1/5/6, owner actions49/50/149/150,
signed counter thresholds3/4/32767, time0/1/5, alpha0/15/16/255 and eight masked
x87 precision/rounding settings. Sixteen angle bit patterns cover signed zero,
denormal, adjacent finite values, maximum finite, signed infinity and distinct
quiet/signalling NaNs. Results:

- 3524 actual root returns with stack/saved-register checks.
- 120 prefixes stopped at the original465190 owner-spawn entry; seven argument
  words, owner receiver and pointed-to three-word payload agree.
- 324 prefixes stopped at original435240 effect entry; five argument words and
  receiver agree (the gate's first effect ID is201 for this action).
- 688 alpha-write snapshots agree in selected code; all688 predecessor x87
  snapshot differences disappear. Final effects and ordered writes already agree.
- 2044 sequence-read differences remain in both previous and selected code.

Stopped spawn/effect helpers receive no fabricated return. The default audit
requires every observation to agree and rejects those remaining sequence reads.
The explicit `--allow-sequence-read-differences` option checks other effects and
alpha-write snapshots while reporting the unresolved field. It never permits
alpha-store or final-effect mismatches. Arbitrary resources, complete effects/
spawn execution, callbacks, unmasked exceptions and full-root behavior remain
outside the execution evidence. No gameplay defect is inferred from the prior
x87 snapshot difference alone.

## Complete delta, other paths and remaining mismatch

The selected complete canonical payload stays20136 bytes, metadata at19668.
Exactly18 bytes change, all inside the recovered26-byte interval. All other
canonical code, relocations and metadata bytes are identical to086a772's object.
The auditor pins the unique target interval and rejects any other payload change.
Outside807,4464 strictly labelled normal-return graph nodes agree with no carrier
allowances. Calls remain opaque normal returns in that graph proof.

Full canonical SHA256:
`0e7ae68b65b6d31f195d4b8d82cf726847ae05c2f600faf1a276553d864613d4`.
The19522-byte comparison SHA256 is
`494623a1c5a158261964492db36c084e2b118a43e3355aa76a06f2871a148262`.
The full-root comparator stays nonexact at hex offset22, target0F/sourceA1.
No exact function or byte credit is added.807 remains502 bytes/110 instructions
versus target414/89: sequence CSE/register choice and shared frame-tail ownership
remain unresolved.

## Other target-motivated controls

| Compiled form | Full bytes | Canonical SHA256 prefix | Finding |
| --- | ---: | --- | --- |
| Predecessor086a772 |20136|fd8dc276|Alpha stored before the live angle calculation|
| Explicit post-spawn sequence snapshot |20136|033fcd2e|112 owner instructions; extra jumps and other-action x87 scheduling changes|
| Explicit common801/807 frame tail |20332|21f012bc|VC8 still duplicates807's tail; physical layout worsens|
| Used angle carried across alpha write |20136|0e7ae68b|Selected; exact26-byte interval and confined delta|

The first control matches a real target snapshot at61A853, but the spelling
causes branch-exclusive optimization and does not reproduce target CSE/layout.
It remains unselected. The second control uses the actual shared frame logic
seen at61A5D9, without dummy operations, but explicit source sharing does not
force physical sharing. It is also unselected. Neither failure proves that the
root needs LTCG or that the target semantics differ.

## Reproduction and retention

```sh
taskset -c 0 nice -n 10 python3 scripts/build.py --unit gpt-web-aya-object-vslot28-full-root --compare --json
taskset -c 0 nice -n 10 python3 scripts/audit-aya-object-807-angle-lifetime.py --previous-object build/aya-807-sequence-20261023/previous.obj --allow-sequence-read-differences --output build/aya-807-sequence-20261023/native.json
python3 scripts/audit-aya-object-normal-flow.py build/aya-807-sequence-20261023/previous.obj build/match-units/GptWeb_AyaObjectActionState.obj --exclude-action 807 --output build/aya-807-sequence-20261023/angle-outside807.json
python3 scripts/audit-aya-object-predicate-widths.py
python3 scripts/validate-tracking.py --require-target
taskset -c 0 nice -n 10 python3 scripts/ci.py
git diff --check
```

The configured full-root comparator is expected to report nonexact. Omit the
previous object option for current native replay only. The previous object's
full canonical SHA256 isfd8dc276...; it is copied before this source change.
Reports, source controls and integrity receipts remain in
`build/aya-807-sequence-20261023/`; private artifacts are not committed.

Two completed unselected objects were archived after SHA256 round-trip checks,
80674 to24271 bytes. `retention.json` retains member/archive hashes
and target/source/current/previous object pins checked before/after removal.
Restore controls with `tar -xzf build/aya-807-sequence-20261023/completed-controls.tar.gz`
from the repository root. Frozen source and reports remain uncompressed.
