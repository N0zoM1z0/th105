# ReimuObject retirement writes and x87 cleanup

The selected496540 source remains CPP555da070 and canonical88bd9c9b.
Complete-root exactness is still unachieved, first mismatch49655F/+31.
This work uses the hash-attested original Japanese1.06a PE; the attached
IDA fails target attestation and is not used. No source/profile/ownership
or exact ledger changes are selected.

## Observed distinction at the write

The preceding helper-entry diagnostic sees equal live x87 values on3600
selected inputs. Recording live x87 values at each object/owner/parameter
write exposes22 additional differences despite equal final outputs and
ordered memory events. Every difference is a root-owned dword decrement
of object+330. The target still has one live x87 value at the write and
pops it afterward; selected source pops before reaching its shared retirement
label. The logical values are not always constants: some are the just-written
y coordinate, including NaN in an admitted fixture.

The target cleanup starts4980E4 and49B8E7 are observed:
`add dword ptr [esi+330h],-1; fstp st(0)`, followed by the ordinary epilogue.
Their RETs have respective action memberships812/821/822 and855/869/903/904
under the complete reviewed switch graph.821 also has a separate decrement
then-pop at499CB2. Static memberships assume normal returns; they do not prove
every syntactic route feasible.

| Action | Different sampled inputs |
| --- | ---: |
|821|1|
|822|3|
|855|2|
|869|3|
|903|6|
|904|7|

`scripts/audit-reimu-object-retirement-fpu.py` preserves the existing real
helper execution and opaque entry stops. It compares final outputs, ordered
object/owner/parameter writes, and logical live x87 values/tags at root-owned
state330 writes. Physical TOP and exception flags are excluded from the
write-time diagnostic; existing native return checks still require balanced
x87/stack and preserved nonvolatile registers.

## Source controls and limits

Replacing only817's two target-local empty-x87 exits with decrement/return
keeps call memberships equal, but leaves diagnostic RET distance25 and the
full canonical mismatch. It is not selected.

The coherent floating-cleanup control uses ordinary decrement/return at812's
completed sector loop,821's owner termination conditions and822's channel15
gate. For855/869/903/904, the first three bounds tests use a local return;
the last y test retains its ordinary shared exit. No fake values, assembly,
forced stack slots, ABI changes or compiler flags are introduced.

This control removes all22 sampled write-time x87 differences, with zero
output and ordered-write differences. It is still nonexact: code prefix45388,
canonical payload46256/SHA256
ead82cca761957880bab04e8a8f5f75a4bc5c83918feb93abdd28b1d4611fcfc,
67 RETs and changed complete call-membership partitions. In particular, the
source CFG's three World/wave pairs move from906-only to905-only reachability,
and one advance call merges817 with860/861. This is static CFG evidence,
not a demonstrated wrong gameplay output. The real4963A0 stays66/66 exact.

The early-cleanup subgroup alone emits46288 bytes/69 RETs;822's channel gate
alone emits46296/68 RETs. Both remain nonexact+31 and change call partitions.
Equal RET counts therefore do not establish exactness. No control replaces
the current selected source. These results exclude the tested shapes under
their source/profile, not every source or LTCG context.

A separate deterministic12000-input cross-fixture diagnostic mutates one
scalar input per existing case, including integer extrema, subnormals and
NaN. It records zero final-output/write differences and zero execution errors,
input hashb5a08e794decc14be673bc69b1e76ee5d54fee872f509924c3032100e2bdb740.
Its private receipt is additional finite evidence, not a replacement for the
full133192 selected checkpoint or proof of arbitrary aliases/resources.

## Reproduction

```bash
python3 scripts/audit-reimu-object-retirement-fpu.py \
  build/match-units/GptWeb_ReimuObjectActionState.obj \
  --output build/reimu-object-return-sharing-20261020/selected-retirement.json
```

Expected diagnostic exit1:3600 inputs, zero output/write differences and22
retirement-state differences. Default stride37 yields input hash
e90a5943bb6d191b71e759265ca9a6fbceff9bc5317da6350aa49a70577b032b.
The private complete-cleanup control is the positive: same inputs and zero
differences in all three categories, expected exit0. Input pins agree before
and after; the audit does not independently verify build provenance.

Receipts and frozen control CPP/COFF files reside in
`build/reimu-object-return-sharing-20261020/`. Private recipes are
`fpu-returns.py`, `local-817.py`, `cross-fixtures.py` and `write-fpu.py` in
the corresponding `.analysis/` directory; the fresh baseline is raw COFF
9d0cf6aba4ed041369bfb47d092ad4033b959a36758baa020b419acac188609e.
The control's source-based complete comparator and call/RET census must be
read alongside its successful native write-state diagnostic. No partial
exact credit or aggregate cold replay is claimed.

The next source-recovery requirement is joint: preserve the target's floating
cleanup placement and its complete call sharing. The passing final-output and
helper-entry checks alone cannot distinguish that remaining lifetime issue.
