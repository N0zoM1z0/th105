# ReimuObject901 scoped flow and shared request tails

This advances the [804 checkpoint](REIMU_OBJECT_804_SEQUENCES_2026_10_20.md)
for authored root496540. The target remains original Japanese TH10.5 v1.06a,
SHA256 `56350024879199861579c11b0e1c67b9590e10a8d40cd5996b109deec9afca7e`.
The strict unit still compares46138 physical bytes through4A197A exclusively,
including46128 owned instruction bytes and10 alignment bytes. The39853-byte
main-span candidate, ownership manifest, void/ECX/RET0 ABI and vslot28 are
unchanged. No exact row, remote_exact flag or authored-byte credit is added.

Current source/artifact pins are superseded by the [900 checkpoint](REIMU_OBJECT_900_FLOW_2026_10_20.md); the901 observations and controls below remain historical evidence.

## Raw901 observations

The physical action interval49CEC2..49D7D6 is2324 bytes, SHA256
`1203bc98d1bcdf89314270747a9c4a320fe00106e14f636b7691f28d5e8f60c0`.
It contains552 instructions/2317 owned bytes and seven alignment bytes; it is
not a standalone function. The signed word13E load, CMP6 and unsigned JA at
49CECF guard the seven-entry dispatch49CED5/table4A1BB0:

| Sequence | Destination |
| --- | --- |
|0|49CEDC|
|1|49D20D|
|2/default|49D783|
|3|49D671|
|4|49D6AC|
|5|49D6D8|
|6|49D720|

**Observed:** damping of parameter1 belongs to sequences3/5/6. Fade belongs
to3/4/5 with signed counter>=5, and6 with signed counter>=0. Default/2 goes
directly to movement/animation. Sequence1's successful-impact World call at
49D42E also jumps directly to movement49D783. It does not reread the sequence
and enter a different arm's fade logic after that opaque call.

**Source correction:** move those operations into the corresponding switch
arms. The old source's common post-switch sequence tests introduced extra
physical branches after0/1/2. Existing concrete prefixes did not expose the
potential post-World alias difference because World remains an entry stop.
Raw branch placement, rather than an invented returning-World execution,
supports the corrected snapshot flow.

901 initializes EBX=-1 at49CEC9 and uses it only in three330 decrements:
49D0C5,49D1FC and49D7C5. Direction stores49CF27/49CF30 use immediate FF/1,
not BL. The selected source retains the unsigned-byte header and255/1 values;
its signedness is not inferred from the decrement register. Exact allocation
of that constant register remains unclosed.

## Real buffer initialization and lifetimes

Let F be ESP after the root's fixed allocation and four saved-register pushes.
Account for intervening argument pushes when reading LEA/store offsets:

* Sequence0's owner730 request pair uses the same four-float buffer at F+A0.
  The first request has count3, but the target initializes all four words to
  `{0,.75,3,0}`. The second request reuses that pointer with count4 after
  assigning heading, value174*.25,1 and parameter3.
* Sequence0's health burst reuses a three-float buffer at F+3C across its first,
  second and eight particle requests. Ghidra's split stack-local names do not
  establish distinct buffers here.
* Sequence1's exhausted-impact burst uses F+48; its health burst uses F+54.
  These are distinct live request objects. Both finalize their own packet and
  jump through49D54C/49D66C to499DF6's receiver setup and World CALL499DF8.
  They share the final call, rather than one buffer for both branches.

**Source correction:** use a natural four-element aggregate with three explicit
initializers, which defines the fourth element as zero. The existing fourth
element is genuinely used by the later count4 request; no extra padding or
request argument is introduced. Keep two separate sequence1 arrays alive in
the case scope and pass their selected pointer to one final emission label.
Keep sequence0's two local retirement exits and the local animation completion
decrement. The pointer and both arrays carry actual request data; no inert
variable, synthetic return, assembly or copied instruction array is used.

A focused input seeds the free stack below entry ESP with A5 bytes before any
root instruction executes. Actual first-World observations are:

| Build | Requested words | Four-word caller object |
| --- | --- | --- |
|Original target|3|`0,.75,3,0`|
|Fresh starting source|3|`0,.75,3,A5A5A5A5`|
|Selected aggregate|3|`0,.75,3,0`|

The first three requested words and ordinary prefix checks agree in the old
source. This additional observation exposes its missing initialization without
claiming that World consumes a fourth word for count3. Input stack seeding does
not alter code, the return address or helper returns. Raw ESP accounting and
the later count4 request establish the real four-word object being inspected.

## Cross-sequence call projection

The new `scripts/audit-reimu-object-901-flow.py` checks eight actual prefixes:
one per sequence0..6 plus the seeded-stack owner730 case. Actual helpers, RNG,
lookup initialization and terrain initialization run unchanged. It validates
the observed signed-sequence/CMP6/JA/indexed-JMP protocol and the dispatch
actually reached by each input. Opaque entries remain frontiers.

It then projects static normal-return continuations from all seven sequence
destinations onto direct calls and a collapsed RET node. Each individual
projection is compared, followed by a joint graph that retains one node per
physical call and labels which entries reach it. This preserves sharing by
only some sequences. Seven independent graph bijections alone can miss an
extra shared or cloned call across the family.

The selected source passes all eight prefixes/buffer checks, all seven graphs
and their joint bijection with23 target/23 source call nodes. Input SHA256 is
`8b14d1524e4269ba02a534e8835deb69ec68a4318585c84a227f1c787c9f862d`.
The graph preserves call order/cycles and sharing; branch predicates, object
effects, exact instruction encodings, physical RET identity and actual returns
from World are not proved by that projection.

Two independently compiled counterexamples remain useful:

* The fresh baseline has23/23 joint call nodes, but fails individual modes0/1/2,
  joint topology and the seeded caller-buffer observation. Equal node totals
  do not rescue its different structure.
* The joined-tail control with both sequences' retirement tails merged passes
  all eight runtime observations and all seven individual graphs. Its joint
  graph has23 target/22 source call nodes and is rejected for incorrect
  cross-sequence sharing. This is a physical-structure failure, not a claimed
  concrete-prefix runtime error.

The reusable `combine_call_graphs` helper lives beside the existing selector
projection. Three additional portable tests cover global renaming with partial
sharing, individually equal graphs with cloned calls, and equal site totals
with the wrong sharing subset. The previous loop/order tests remain in place.
Reports retain `build_provenance_verified=false`; their source/object/tool pins
and the formal build's compiler/input/object receipt remain separate evidence.

## Controlled VC8 results

Every experiment uses the same VC8 SP1 O2/GS profile, header, bindings and full
46138-byte comparison. All retain438h and first31 target bytes. No result is
accepted from section size, CALL/RET counts or owner diagnostics.

| Shape | Section bytes | CALL /RET | World sites | Animation sites |
| --- | --- | --- | --- | --- |
|Starting804 source|45100|401 /61|107|11|
|Local901 advance only|45164|402 /62|107|12|
|Local901 retirements only|44968|396 /56|102|11|
|Both local tails, old outer fade|45032|397 /57|102|12|
|Scoped fade/damping only|45052|400 /60|106|11|
|Scoped plus local advance|45084|401 /61|106|12|
|Scoped plus all four World retirements local|44984|397 /57|102|12|
|Aggregate plus scoped/local advance|45068|401 /61|106|12|
|Aggregate plus all four local World retirements|44968|397 /57|102|12|
|Joined sequence1 tail, common sequence0 retire|45020|400 /60|105|12|
|Selected joined tail and local sequence0 retire|45068|401 /61|106|12|

Two asymmetric retirement controls also emit identical45132-byte canonical
code despite different source placement; neither fixes the joint graph.
The aggregate/all-local-World control passes all individual sequence graphs
while still failing the joint23/22 graph. These phase-scoped experiments explain
the selected scopes; they do not establish unique original source spelling.

The selected full comparison remains **mismatch** at49655F/+31, the default
branch displacement. Code after that prefix also differs. The source decodes
10268 instructions, has metadata44184/884 bytes and final RET end44182 before
two alignment bytes. Root totals remain404 target/401 source direct CALLs to
25 targets,68/61 RETs and0/43 identical owner diagnostics. World99/106 and
animation22/12 are the remaining callee-count differences; other23 totals agree.
These count gaps are not missing-behavior counts or partial exact credit.

## Selected build and runtime

| Artifact | SHA256 |
| --- | --- |
|Selected CRLF CPP|`663a48b656afc71a7b44e07f25c5d4437570c2248edef95bc4b83fb4f832e8f7`|
|Unchanged header|`348794fa1087721b1444eacdc1d421355b6b8f76f656bd216b41261221876adc`|
|Canonical45068 bytes at496540|`d44dee159143ff793f810282fef1e55e011c3031f3e9f09fd22a8a97845ce770`|
|Native45068 bytes at800000|`9a91844725774e6a3b15e9adbef9ffd69600629995ee1810d74d72d676edd470`|
|Fresh public object|`1af684fcb4ebd7213682ed310063e5f6040d165931915189b441cca3d6d9abd9`|

The private selected shape passes0/7292 upper-state/901 value/fade/orbit/impact/
color/steering/animation inputs, SHA256
`4e730f62236ae28682b7376cf246361056bdc2896191043f4b763e3118a1a5c3`:
5626 actual RETs,1570 first World entries and96 CRT qNaN entries. The cleaned
public source emits byte-identical canonical/native code to that private
shape. The fresh public eight-input flow proof passes independently.

The frozen selected public source passes **0/133192** unchanged full inputs,
SHA256 `f46a849ff57f64bb16e77fd0e28f7f51eee7238501c04049add99e7f77fc3b8b`.
It visits9215 target/8831 source instructions. Endpoints remain119356 actual
RETs,10422 first World,915 setup,1151 owned-spawn,26 effect,114 wave,
472 parented-spawn,112 CRT errno and624 CRT qNaN entries. Existing object/
owner/parameter, helper trace/argument, stack/RET, saved-register and x87 checks
remain active. Entry stops do not establish returning opaque graphs.

Existing selector0/16 and8040/3144 checks pass. Both808/812 caller proofs,
orientation0/400, alpha0/1170 and terrain288 pass. Focused original4937D0
manager-entry passes0/3168 upper-state/901-fade inputs, SHA256
`98dab974afdf8d76412e8ac1d30428cc79c9ef4edcfe82f1e2ba07d06907210d`:
2856 real wrapper RETs and312 first World entries,668 target/618 source
instructions visited. Input vtable cloning, zero freeze/hold words and null
secondary preserve its controlled scope. No shared header/layout/profile or
relocation key changes invalidate other accepted objects in this batch.

Fresh preflight, raw full-root closure and shared-callee ranking precede the
work. IDA metadata identifies another image and supplies no semantics. One
direct read-only/no-analysis Ghidra run independently attests imported/file
identity, entry, mapped text, root and vtable with CPU0/nice10/128MiB heap.
All nine primary DB hashes remain unchanged and its alias is removed.
Decompiler local names/array sizes remain hypotheses; push-adjusted raw ESP
addresses resolve the actual buffer identities above.

Generated reports/objects/controls stay below
`build/reimu-object-901-tails-20261020`; private scripts and Ghidra work stay
below `.analysis/reimu-object-901-tails-20261020`. No generated artifact,
executable, database or compiler install is committed.
Redundant unselected full-root owner diagnostics are reduced to901 plus their
root/hash metadata, and redundant canonical byte copies are removed. Source,
COFF and regeneration recipes remain; full baseline/selected/sharing-control
diagnostics are retained. This reduces the new build scope from11.1 to6.3MiB.

```bash
taskset -c 0 nice -n 10 python3 scripts/audit-reimu-object-update-target.py --json
taskset -c 0 nice -n 10 python3 scripts/build.py --unit gpt-web-reimu-object-action-state --compare --json
# Expected nonexact result across all46138 physical bytes.
taskset -c 0 nice -n 10 python3 scripts/audit-reimu-object-901-flow.py build/match-units/GptWeb_ReimuObjectActionState.obj --output build/reimu-object-901-tails-20261020/flow-selected.json
taskset -c 0 nice -n 10 python3 scripts/audit-reimu-object-scalar-actions.py build/match-units/GptWeb_ReimuObjectActionState.obj --final-actions --output-dir build/reimu-object-901-tails-20261020/positive
python3 -m unittest discover -s tests -p test_reimu_selector_call_graph.py -v
python3 scripts/check-match-literals.py --require-target
python3 scripts/validate-tracking.py --require-target
taskset -c 0 nice -n 10 python3 scripts/ci.py
git diff --check
```

Next recover remaining animation/World/RET sharing and constant/stack lifetimes
against complete raw control flow. Correct partial sharing and438h alone do
not establish exact root bytes, a standalone compiler boundary or an LTCG
impossibility. Returning world/setup/event/wave/CRT graphs, arbitrary aliases/
resources, nonnull rendering and unmasked exceptions remain open. Terrain
retains48 hardware-unqualified nonfinite contexts, its measured SSE emulator
gap and the runtime6FA894 adjacent-word load. Preserve Fighter478FA0 and
initializer4A1CE0 checkpoints. No cold aggregate or percentage is asserted.
