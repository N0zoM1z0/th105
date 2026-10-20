# ReimuObject817 coordinate argument lifetimes

Both817 sequence0/9 periodic requests now prepare facing and outgoing arguments
before the coordinate RNG calls. The selected source keeps the actual coordinate
expressions inside `spawn_owned_object_via_manager`, rather than computing two
float request locals first. New native observation rejects the predecessor
even though final prefix outputs agree. Whole496540 remains **nonexact+31**;
no new exact function or partial-byte credit is recorded.

## Observed target and source correction

All observations use original Japanese TH10.5 v1.06a, SHA256
`56350024879199861579c11b0e1c67b9590e10a8d40cd5996b109deec9afca7e`.
Fresh target/status/tracking checks pass. IDA rejects10350095... and provides
no semantics. No Ghidra process, database write or target patch is used.
Candidate39853, full46138-byte comparison ownership, authored classification,
ECX/RET0 boundary and inferred void source view remain unchanged.

The periodic paths first create their three-float packets using RNG270/40.
At the two coordinate-call sites, target reads facing byte104 and pushes the
packet/count/variant/facing arguments before evaluating Y with RNG100 and X
with RNG200. It captures both double coordinate origins before RNG100 and
loads owner348 after RNG200. The existing double origin locals are retained.

The predecessor5210f5ab computes `request_y`, then `request_x`, then calls the
owner method. Consequently its facing read and outgoing argument stores occur
after the coordinate RNG calls. Putting the real X/Y expressions back into
their call arguments restores the observed VC8 order. RNG270/40/100/200, casts,
float round trips and source arithmetic association remain. This describes
pinned VC8 emission, not a portable C++ argument-order guarantee or proof of
unique original source spelling. No helper shim, register forcing, inert work,
assembly, ABI or shared header change is introduced.

Two diagnostic windows agree in every byte after replaying their three known
direct calls at the target location:

| Target window | Bytes | Calls |
| --- | ---: | --- |
|498F0A..498F81|119|RNG100, RNG200, owner request465190|
|49976C..4997E3|119|RNG100, RNG200, owner request465190|

`facts-summary.json` pins both raw hashes, source locations and call fixups.
These windows are not independently bounded functions or new match units.
Their agreement does not accept the surrounding root.

## New observer, physical slots and negative control

`scripts/audit-reimu-object-817-coordinate-arguments.py` observes actual facing
reads, original RNG entries and the outgoing stack words.640 cases cover two
sequences, four periodic counters, two facings, five actual MT seeds, two x87
control words and four coordinate pairs including NaN. Entry facing is read
back. All640 target/source paths execute the four real RNG calls and stop at
the actual owned-object request entry465190, without returning it.

The observed root order must be:

```text
rng270, rng40, facing, rng100, rng200
```

At RNG100 entry, facing/variant/packet/count must already occupy the outgoing
stack slots. At RNG200 entry, the real Y float must precede those words. The
observer compares pending scalars, packet bytes and the actual packet offsets
from root-entry SP. It validates target pending data against its real eventual
request. The two observed packet offsets are-484/-460 and agree per case.

All640 selected cases agree in output, object/owner/parameter writes, facing
order and pending arguments. Predecessor5210f5ab has zero output/write
differences but fails facing order and pending arguments in **640/640**.
Input SHA256:
`8e216ee2a3e12fdbe34f26ab78f6e40bacf60ea45fe6502d75ac7b69c31d83de`.
This is finite native prefix evidence, not arbitrary alias/resource coverage
or opaque-return execution.

The existing817 sequence3 turn-lifetime audit freshly passes320 actual RNG/RET
paths, input cc46775a. The retirement sample passes3600 at stride37, input
e90a5943, with zero final-output, ordered-write or logical retirement-x87
differences. Logical x87 excludes physical TOP and exception flags. Scoped
905/907/908 selector checks pass12 first-request prefixes and conditional
normal-return graphs. Sixteen packet-prefix observations retain the12 matching
906..908 slots;905's four placements still differ. Earlier6720/256/133192/26342
receipts remain evidence for their own source epochs.

## Full comparison and compiler impact

| Selected artifact | SHA256 |
| --- | --- |
|CRLF CPP|`78d85ab4deb4890e28016823dbbf3ccb5d733de435d474157a9d265b66136da8`|
|Unchanged header|`6f469e6886959fd41ee6976b3c784c3df0c2e753ad4729a536764a3c8cd28b4b`|
|Tested formal COFF|`05fdccc7ef8d4aeff6dd3bc38d6596d45422ee2ec91da0567aa6aad4c4ee6af6`|
|Whole46144-byte canonical source section|`5e5bc7ab0678610ba165670cee0463786e150059d5dd6552b9f6b4934d362ea3`|
|Fixed46138-byte compared prefix|`b2ee43cc5871a1cad876d3fc64fce7daeca4752a58ac4fc46be067fe9804abb5`|

Ordinary SP1 O2, GS off, retains438h frame and exact same-TU4963A0 at66/66.
Source has45276 code bytes plus868 metadata bytes and10444 decoded instructions;
target owns46128 code bytes/10670 instructions. Section-size proximity is not
code-size equality. Source426 calls/71 RETs still differ from target433/68.

Source-to-source instruction/edge diagnostics, excluding the recorded NOP forms,
leave41/43 physical owners unchanged.817 changes argument lifetimes.902 changes
only a short JNE to a near JNE: all other normalized instruction tokens, the
condition and symbolic destination/fallthrough agree. Every switch table and
both complete call/RET membership multisets remain unchanged. RET-distance27
and call-membership distance9 remain diagnostics.817 still shares advance with
860/861;906 still shares three final-World/wave pairs kept private by target.
905 placement and908's post-wave FILD/FADD-memory form remain unresolved.

The tested private candidate and formal object export identical full native
sections. A final metadata-only build is bridged by the same equality in
`final-inputs.json`. No other accepted unit source, layout, flag, partition,
binding, origin or match row changes. Only the affected mixed root/helper unit
is built; no cold aggregate replay is claimed.

## Retention and reproduction

Current frozen inputs, COFFs, receipts and private recipes are under
`build/reimu-object-rng-captures-20261021/` and its matching `.analysis/` scope.
The active scope remains uncompressed. Six historical diagnostic JSONs from
predecessorf158594 were losslessly compressed3456992->219205 bytes, with
`build/reimu-object-817-tail-20261021/historical-diagnostics-compression.json`
recording every hash. All prior source/COFF/native inputs and execution/build
receipts remain; restore the JSON `.gz` copies before older private recipes.
Primary databases, compiler installations and canonical target are preserved.
All heavy work runs serially at CPU0/nice10.

```bash
taskset -c 0 nice -n 10 python3 scripts/build.py \
  --unit gpt-web-reimu-object-action-state --compare --json
# Expected exit1: root nonexact+31, helper66/66 exact.
taskset -c 0 nice -n 10 python3 scripts/audit-reimu-object-817-coordinate-arguments.py \
  build/match-units/GptWeb_ReimuObjectActionState.obj --output build/817-coordinate.json
python3 scripts/validate-tracking.py --require-target
taskset -c 0 nice -n 10 python3 scripts/ci.py
git diff --check
```
