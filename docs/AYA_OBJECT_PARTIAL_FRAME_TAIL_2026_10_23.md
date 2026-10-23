# AyaObject partial frame-tail recovery, 2026-10-23

Target: original Japanese 1.06a SHA256
`56350024879199861579c11b0e1c67b9590e10a8d40cd5996b109deec9afca7e`.
Root `0x61A290`, unit `gpt-web-aya-object-vslot28-full-root`. IDA preflight
still rejects its open database; target observations use the attested PE.

## Selected complete source

The selected source joins 807's frame/sequence2 exit to the existing817 tail,
captures the used float rotation before the alpha read in817/822, and uses
double views for the two root-local quantized lookup returns. The full root
is compiled and compared; no isolated window earns progress credit.

| Property | Selected result |
| --- | --- |
| Source SHA256 | `59bcfc3149acb4cfe422451e0198ae92c49639894e0812206a578924b6cec928` |
| Complete canonical payload | 20000 bytes, `5f2966cb6b34c844d210ac54e52894b5d510c17362c3fe2424c1d2de6b89c4ec` |
| Mapped payload at S=0x800000 | `e8add2f904c6336d4449795688a4c44a2526dd2d455f59719e1c48ccae9c91c5` |
| Last source RET end / metadata start | 19529 /19532; three following bytes `8D 49 00` |
| Target callable ledger | 19522 bytes, unchanged |
| Canonical result | **Nonexact +0x22**, target `0F` / source `16` |
| Physical frame-helper calls | 12, down from13; target11 |

Relative to `f15dccf`, the payload shrinks by120 bytes without changing the
dispatcher instruction form or the four recovered scale/rate read orders.
Target frame/sequence2 tail61A5DB serves801/807/811/817/822/854. Source now
has two sites for that policy instead of three. Complete physical sharing,
852's branch-local FILD/scratch and other target differences remain open.
No root or new authored exact credit is claimed.

Target code plus its reviewed tables ends at offset19992, followed by eight
INT3 bytes before initializer61F0B0. The selected 20000-byte COFF payload
contains table data through that offset; equal enclosing sizes do not imply
equal instructions or metadata. Source metadata offsets include preceding
alignment and do not enlarge target callable ownership.

## Observed lifetimes and the complete source graph

Combining both double lookup views with the partial tail restores all four
target rate-first scale pairs. A single changed lookup declaration does not.
The combination initially reverses the817/822 rotation sum at the alpha read.
A used float snapshot before that read restores target61B2DD's order:
FLD `[ESI+12C]`, read/compare alpha, FADD `[ESI+370]`, then store rotation.
Float/double snapshots and compound forms produce the same tested payload;
the selected source needs only a float value. These are context-specific
compiler observations, not a general return-type tuning recipe.

Private complete instruction-labelled graph comparison pairs **4569 nodes**
against the preceding selected source. No action or floating window is excluded.
All field operations, x87 operations, switch guards/index bytes and ordered
successors agree after contracting internal direct JMP. Exactly one separately
proved difference moves MOV ECX,ESI for807 from S80067A to S801249, just before
the same reviewed frame helper4351C0.

Seven intervening floating instructions agree, byte for byte: FILD scratch14,
FMUL velocity, FADD/store X, then FLD/FADD/store Y. None reads/writes ECX or
writes ESI; no opaque call or conditional branch intervenes. The common-source
JMP is contracted explicitly. Both paths supply the same receiver at the
helper. The target's corresponding40-byte sequence at61A8F5 likewise jumps
to the shared receiver load at61A5D9. Normal-return effects are qualified;
callback and unmasked-exception register observers are not covered. The public
strict graph checker and canonical comparator are unchanged.

One actual807 witness retains all existing observations and its three sequence
reads. Older852,826 and scale-read matrices were not rerun: their field/x87
observations are preserved through the complete source-graph proof under the
same reviewed normal helper contracts. This is a transfer argument with those
limits, not a new execution-count claim. The selected861 still writes alpha
before X in the recorded counterexample; target writes X before alpha.

## Rejected combinations and genuine compiler context

The previously rejected hard 826/861 shared fade was retried on this source
epoch, with both lookup views. The double-view version agrees with the861
write/scale witness, but both variants still lose807's second zero-sequence
read (3/3/3/2/2 reads for target/baseline/selection/two controls). Neither is
selected. A three-pair source scale layout is not sufficient evidence.

Natural861 owner-Y captures preserve807's three reads, but move alpha after
Y and scale-X stores. They still fail the target's position/write observations.
Some emit19992 bytes and advance the first mismatch to+0x1C7; those apparent
byte improvements are rejected. Float-Y capture and a baseline-epoch double-Y
control also retain write-order failures. An additional X capture is byte-neutral
to the tested double-Y form. No unsupported ordering or alias assumption is added.

Retained hash-verified VC8 RTM was also tested on the new selection and the
Y-after-X candidate. It emits20016/20008 bytes, respectively, both nonexact+0x22.
This closes those fresh compiler controls without excluding every RTM/TU shape.
The configured SP1 profile is unchanged.

A genuine joint update/initializer source with consistent double lookup views
compiles natively and with `/GL`, then links with twelve real provider objects
and pinned CRT/SDK inputs under `/LTCG`. Native joint and public-view caller
payloads agree. Full linked replay agrees at both canonical and mapped bases:
seven switches,362 HIGHLOW fields,122 direct calls,287 literal references and
three game-data references. The linked envelope is20000 bytes without trailing
alignment. No source stubs, fabricated calls or DLL execution are involved.

This reused double-view context retains earlier16/19 provider results with
source/object/library hashes rechecked. Two lookup providers and its private
oriented body remain nonexact. The accepted public float-view oriented unit
is unchanged and is freshly replayed separately. Original lookup declarations,
nominal owner and original translation-unit membership remain unknown; the
target lookup return tails load F32 into x87, compatible with the tested caller
views. No all-exact dependency or original-program link claim is made.
Initializer remains4859 bytes /`6f70b6f3...`, with its two register-byte differences.

## Reproduce and continue

Recipes: `.analysis/aya-tail-callviews-20261023/`; frozen inputs/receipts:
`build/aya-tail-callviews-20261023/`. Key records are `controls.json`,
`angle-captures.json`, `proved-flow.json`, `native-witnesses.json`,
`fade-native-witnesses.json`, `fade-captures.json`, `rtm-controls.json`, and
`joint/{unified,replay}.json`. Native final/public identity and final gate:
`final-identity.json`, `final-formal.json`, `oriented-anchor.json`, `ci.log`.

```sh
taskset -c 0 nice -n 10 python3 scripts/build.py --unit gpt-web-aya-object-vslot28-full-root --compare --json
taskset -c 0 nice -n 10 python3 scripts/build.py --unit cross-v106a-character-runtime-oriented --compare --json
```

Root comparison exits nonzero for its documented mismatch. No shared header,
profile, partition, global relocation mapping or accepted-unit ABI changed.
Both lookup-name aliases were already root-local; retain them for frozen COFF
replay. Rebase future trials on this source and verify the complete function.
Do not carry the rejected fade's smaller size or older return-view effects
forward as acceptance evidence. Accepted ledger totals are unchanged; no
aggregate cold replay was performed.
