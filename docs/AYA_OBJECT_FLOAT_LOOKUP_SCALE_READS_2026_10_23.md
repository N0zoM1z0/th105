# AyaObject float lookup view and scale reads, 2026-10-23

Target: original Japanese 1.06a, SHA256
`56350024879199861579c11b0e1c67b9590e10a8d40cd5996b109deec9afca7e`.
Root `0x61A290`, unit `gpt-web-aya-object-vslot28-full-root`; raw PE evidence
only. IDA preflight still rejects the open database. No target bytes changed.

## Selected source and full comparison

Only the root-local sine/cosine quantized lookup declarations change from
double to float. Source SHA256:
`da5c622d4808d6dd1516dee567923ede8f1a2c6c4ae0655730ba006505710f46`.
The full emitted payload remains 20,120 bytes, metadata at 19,652, SHA256:
`fad6fa5af2baa1d8b9013d3fe7279bcfea3f136474a0bb9f9a0a52ccd30caf2c`.
Callable ledger remains 19,522 bytes. Canonical comparison is **nonexact +0x22**,
target `0F` / source `8E`, the initial JA displacement. No new exact credit.

Target lookup bodies `0x406360` / `0x4063D0` return through FLD m32 table
loads. This supports the float caller view but does not uniquely identify the
original C++ return declaration. The public oriented helper `0x435160` already
uses that float view and freshly compares 57/57 exact. The unverified global
definitions in `src/engine/AngleLookup.cpp` remain unchanged.

Relative to checkpoint `a04ba76`, exactly sixteen ordinary payload bytes change:
four adjacent twelve-byte FLD/FADD pairs now read `ESI+0x370` before `ESI+0x11C`,
as the target does. Old source reads those fields in reverse order. All other
payload bytes agree at both canonical `A=0x61A290` and mapped `S=0x800000`,
including all 123 calls, seven switch tables, branches and metadata. The changed
pairs have no external interior entries. Complete source CFG traversal assigns
them only to 820, 826, 853 and 861; the default path cannot reach them.

| Action | Target pair | Selected source pair at S |
| --- | --- | --- |
| 820 | `0x61B623` | `0x801490` |
| 826 | `0x61C2DF` | `0x8020CE` |
| 853 | `0x61CC2C` | `0x802A7A` |
| 861 | `0x61C2DF`, shared with 826 | `0x80357F` |

The lookup calls occur in action 812, whose instructions remain unchanged.
The effect on other actions is an observed compiler-context result, not a
general rule about return types. This source selection preserves the preceding
852 correction by unchanged reachable code; its 9,728-case matrix was not
rerun. Branch-local FILD duplication and ESP+0x14 scratch remain unresolved.

## Scoped actual-code observations

The scale auditor's optional `--scale-read-lifetimes` mode observes the actual
typed m32 operand reads, values and live x87 state. It retains actor/parameter,
ordered-write, call and store checks, and expands the old eight control words
to twelve masked PC24/53/64 modes. Each case must execute both operand reads
and return normally. The completed diagnostic matrix has 18,576 inputs:

| Action | Cases | Selected differences | Predecessor additional differences |
| --- | ---: | --- | --- |
| 820 | 6192 | none | 6192 scale-read traces |
| 826 | 3096 | none | 3096 scale-read traces |
| 853 | 6192 | none | 6192 scale-read traces |
| 861 | 3096 | 3096 known ordered-write differences | 3096 scale-read traces |

All 18,576 selected operand-read traces agree; all recorded observations agree
in 15,480 cases. The report explicitly has `selected_target_agreement=false`:
861's existing alpha/position write-order issue remains visible. Inputs use
six action/sequence pairs, sixteen scale and sixteen growth patterns, twelve
control words plus 144 alpha/phase cases. Owner Y is finite; spawning, arbitrary
callbacks, unmasked exceptions and whole-root equivalence remain unproved.
Wrong operand width and an injected actual-read-hook error are rejected by
separate guard checks; target bytes remain unchanged.

## Genuine joint compiler context and rejected controls

A consistent float-view update/initializer source, real lookup/runtime bodies,
ten other hash-verified provider objects and pinned CRT/SDK libraries compile
and link with `/GL` plus `/LTCG`. Seventeen of nineteen requested dependencies
compare exact. Restoring the already accepted 57-byte helper accounts for the
increase from sixteen; only the two lookup bodies remain nonexact. There is
no new helper credit, all-exact dependency closure, DLL execution or original
translation-unit claim.

Complete linked caller replay equals native at A and S: seven switches,
362 HIGHLOW fields (67 destinations, eight switch addresses, 287 literals),
123 calls and three game-data references. Payload/metadata remain 20120/19652;
the 20128-byte linked envelope has eight following INT3 bytes. Initializer
selection remains 4859 bytes with two nonexact register bytes.

The 826/861 shared-tail and shared-phase-tail source controls were retried on
both the previous double-view and selected float-view epochs. In each epoch,
one actual 807 return witness has target/selected/shared/shared sequence-read
counts 3/3/2/2. The float controls emit 19864/19872 bytes but remain nonexact and
are rejected. No full 3,968-case replay is claimed for these new epochs.
Integer movement locals, per-action used payload arrays and an ordinary member
movement helper were byte-neutral on the previous double-view epoch only.

The normal-flow utility previously fabricated a fallthrough after immediate
unconditional JMP. Its successor fix removes phantom owners from raw CFG
traversal. Four independent synthetic CFG tests pass. The preceding outside-852
proof still pairs 4,558 nodes plus one qualified two-instruction EDX/EAX carrier;
the strict canonical comparator is unchanged.

## Reproduction and retention

Private recipes: `.analysis/aya-852-sharing-context-20261023/`.
Receipts and frozen inputs: `build/aya-852-sharing-context-20261023/`.
`audited-float.obj` preserves the exact COFF used by the large matrix;
`selected.obj` is the preceding a04ba76 control, despite its historical name.
Key receipts are `complete-pair-delta.json`, `scale-read-lifetimes.json`,
`scale-guard-checks.json`, `prior-852-graph-revalidated.json`,
`float-lookup/{unified,comparison-summary,replay}.json`, and `oriented-anchor.json`.
The final rebuilt public object is checked against frozen native/CIL bytes.

```sh
taskset -c 0 nice -n 10 python3 scripts/build.py --unit gpt-web-aya-object-vslot28-full-root --compare --json
taskset -c 0 nice -n 10 python3 scripts/audit-aya-object-scale-adds.py --actions 820 826 853 861 --scale-read-lifetimes --control-object build/aya-852-sharing-context-20261023/selected.obj --diagnostic --output build/aya-852-sharing-context-20261023/scale-read-lifetimes.json
taskset -c 0 nice -n 10 python3 scripts/build.py --unit cross-v106a-character-runtime-oriented --compare --json
python3 -m unittest discover -s tests -p test_aya_normal_flow_successors.py
```

The root build exits nonzero for known nonexactness; explicit diagnostic mode
keeps 861's failure in the report. Only two root-local REL32 aliases are added
for the float lookup names, retaining double names for frozen COFF replay.
No accepted-unit header, ABI, profile, partition or shared relocation change.
Authored exact totals remain 1381 functions /234914 bytes, with no aggregate
cold-replay claim. Subsequent work prioritizes whole-function exact comparisons
as recorded in the [workflow](RE_WORKFLOW.md).
