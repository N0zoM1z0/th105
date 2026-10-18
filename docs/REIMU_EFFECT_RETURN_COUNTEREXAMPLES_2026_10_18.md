# Reimu: executed effect-return counterexamples and wrapper visibility

The effect62 backend now detects three compiled callback/actor errors after
actual native execution. The earlier expanded-root controls stopped at size
qualification and remain pre-execution negatives. The selected root source is
unchanged: explicit coordinate locals and the real effect-wrapper definition
both leave its complete canonical payload unchanged. No exact credit is added.

## Target and source correspondence

Target is original Japanese TH10.5 v1.06a, SHA-256
`56350024879199861579c11b0e1c67b9590e10a8d40cd5996b109deec9afca7e`.
Root478FA0 is the reviewed81,550-byte callable ending48CE2E, SHA-256
`dbf6f375a809fea91cbbccf0f8cff2196f40cba11458c98e475a290b623053e6`.
It remains authored/unclassified/declaration-only. Source baseline is `c39c49b`;
later documentation checkpoints have not changed its source or compiler inputs.

The observed410/414/416 effect62 request sites are47F595/47FB24/47FF5A. Each has
its own following vslot14 call and RET. The candidate merges these requests at
47FB0E and also shares its following next-block exit with other action paths.
Recovering behavior does not establish that physical sharing.

Two new private source controls are byte-neutral:

- Prepare the actual float Y and X coordinates as consumed locals before each
  effect62 call, preserving each expression's rounding and signed-facing X.
- Define the true435240 wrapper before the root, adapting only the existing
  member name/receiver view. It forwards the same arguments and actor context
  through `g_effect_sink`'s vslot0C.

The wrapper's full52 canonical bytes agree with the accepted target anchor,
SHA-256 `766e73525d2dfc9742f5e6e054a58e61f65b5def458e9c42a3aff78b2c075fd8`.
Its unique defined COFF symbol owns section5/value0; all55 root call fields
refer to that provider with zero addends. The complete root's raw bytes and
all2,475 relocation offsets/names/kinds/addends agree with the opaque baseline.
No new sink-global references or helper inlining appear in the root.

Both controls preserve all82,904 canonical root bytes, SHA-256
`c927ac8906a31ee59f3427681c573ad25136d94199a653650ef8c6d881e635cf`.
This is source-to-source correspondence, not root target equality. The ordinary
object baseline remains
`4f2dada4ea46b61e53cadd2b991d9250d307a616d17e9f23df19396ec8c71cfb`;
its first strict difference is still+541=4791BD. The public opaque-provider
qualification is unchanged. Body visibility is byte-neutral in this source
phase; this does not identify the original TU or wrapper declaration.

## A separately admitted behavioral witness

A compact single-switch witness first fails the existing primary-table
qualification (`low: expected one candidate COFF switch table, found0`). No
native host starts for that attempt, and no public guard is relaxed.

The executed controls instead use the previous middle-region flat-exit witness:
74 returns in30 arms become outer-switch breaks through the existing region
completion. Cases with nested loop/switch break destinations remain unchanged.
This witness has worse physical request sharing and is still unselected for
matching; its smaller prefix permits the deliberately wrong callbacks to pass
the unchanged callable/metadata and all15 stack/request-preparation contracts.
All four objects keep the actual void/no-argument thiscall root interface.

| Witness/control | Prefix bytes | Full payload | Native mismatches |
| --- | --- | --- | --- |
| Middle-exit baseline | 81,468 | 82,840 | 0/60 |
| Omit410/416's post-effect next-block call | 81,468 | 82,840 | 40/60 |
| Replace410's next-block call with frame advancement | 81,516 | 82,888 | 20/60 |
| Negate410's facing after creation and before next-block | 81,500 | 82,872 | 12/60 |

All are within81,550 callable and82,924 metadata-envelope limits. Each uses
the same60 profiles:410/414/416, facing-128/-1/0/1/127, X640/33554432 and both
x87 precision settings. The flip control changes only three of the five
directions: zero remains zero, while negating-128 and narrowing to signed byte
produces-128 again. Thus12/60 is the expected detection set, rather than16/60.

The passing middle-exit object SHA-256 is
`484631b6ad2f375718aec9f913d40c7eb8f46aae02a6f6fd4887a9cb2e657227`.
It is a separately qualified behavioral witness, not a replacement for the
selected expanded root or a canonical target match. These sensitivity results
do not turn the earlier rejected expanded objects into executed controls.

## What actually differs

Each object runs target, independent target-repeat and source in separate Wine
processes. The backend executes genuine target CRT/locks, the InfoEffect
manager, effect62 construction, the actual virtual-next callback, root RET and
destruction. Only kernel32 imports are resolved; no game callback or callback
result is fabricated. Target text and candidate bytes remain unchanged.

Each case compares6,980 bytes of actor/effect/MT/count/FP state. The target and
target-repeat are identical in every run, and all four sets also have identical
complete target snapshots, SHA-256
`a983c3fd28b5a73067cfe7f68e47a94e5ab3a71040dbde84a1d8a42f74e48e3f`.
The deliberately wrong source executions finish normally; their audit CLI exits1
because raw snapshots differ, rather than failing admission or host execution.

Observed field differences isolate the errors:

- Missing next-block:40 cases retain sequence0 and frame6/3, versus target
  sequence1/frame0. Their counter144 also stays8 instead of resetting to zero.
- Replacement frame advancement:20 cases have wrong sequence/frame/timer/counter
  results after the second real advancement instead of the required next-block.
- Facing flip:12 cases differ at actor BYTE104. Sequence/frame/timer/counter
  still agree with the target.

For every case in all four sets, the complete effect, MT, object-count and FP
snapshot suffix is unchanged. The detector therefore observes the post-creation
actor errors while preserving the actual effect creation. This proves these
specific callback-return counterexamples under the supplied read-only,
untextured resources. Arbitrary world/resource graphs, later effect ticks,
exceptions and other returning families remain unproved.

## Reproduction and operational state

Private recipes and receipts remain under `build/reimu-effect-exits/`.
`positions.py` and `effect-visible.py` reproduce the source controls;
`admitted-controls.py` records the exact preceding middle-exit transform and
builds all four native witnesses from the pinned current root cache.
`native-sensitivity-proof.json` retains per-object hashes, execution status,
profile/snapshot hashes and field-difference counts. `control-sizes.json`
records all four reviewed extents. Regenerate removed object products before
running the focused commands:

```bash
nice -n 10 taskset -c 0 python3 -B scripts/audit-reimu-shot-effect-returns.py \
  --object build/reimu-effect-exits/admitted-controls/baseline.obj \
  --output-dir build/reimu-effect-exits/native-admitted-baseline
nice -n 10 taskset -c 0 python3 -B scripts/audit-reimu-shot-effect-returns.py \
  --object build/reimu-effect-exits/admitted-controls/missing-next.obj \
  --output-dir build/reimu-effect-exits/native-missing-next
```

The other two commands substitute `extra-advance` or `flip-facing` in both
paths. Expected CLI statuses are0 for baseline and1 for the three detected
controls. No historical native matrix or aggregate exact-unit replay is run.

Heavy work stays serial with CPU0/nice10; native audits peak307,252KiB, about
300MiB. The earlier Ghidra instruction readback is reused after target and all9
primary-database hash checks; no new Ghidra process or metadata write occurs.
Cleanup removes63 completed control/native products and unused leads,14.64MiB;
all164 current genuine-cache files and all9 primary DB pins remain unchanged.
Recipes, receipts, proofs and the small real-wrapper source remain available.

The next matching work remains the unresolved physical exits and live values,
including the complete shared-next memberships. Keep the known owned/wave and
landing partitions. Neither neutral coordinate/visibility changes nor these
deliberately wrong controls should enter the selected root source.
