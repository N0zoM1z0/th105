# ReimuObject821 owner exits and shared retirement

Three separate821 owner guards recover the target's shared812/821/822
retirement tail for the first two conditions, while the final owner-sequence
condition keeps a private exit. The complete496540 root is still **nonexact
at49655F/+31**. No exact function, window or partial-byte credit is added;
the same-TU4963A0 helper remains66/66 exact.

## Target observations and source hypothesis

Only original Japanese1.06a is used, SHA256
`56350024879199861579c11b0e1c67b9590e10a8d40cd5996b109deec9afca7e`.
Fresh target/tracking checks pass; IDA still rejects10350095... . No IDA
semantics, Ghidra process or database/target-byte write is used.
The unchanged provisional main candidate is39853 bytes; full ownership is
46128 bytes plus10 alignment bytes in the46138-byte comparison. The target
has10670 instructions,22 switches,433 calls and68 RETs.

For821 sequence3, the raw target retires as follows:

| Condition | Guard instruction | Retirement write | Root RET |
| --- | --- | --- | --- |
|Owner action is neither530 nor531|499C8D|4980E4|4980F7|
|Owner sequence3 and frame at least4|499CA7|4980E4|4980F7|
|Owner sequence at least4|499CB0 fallthrough|499CB2|499CC5|

Owner sequence/frame comparisons use signed words. All three tails decrement
state330 before popping the live x87 value. Each write-through-RET span has
the same20 bytes. The first physical span also has812/822 normal-return
reachability; the latter is821-only. Static membership is conditional on
normal opaque returns, not a claim of executing812's completed World loop.

The preceding source joins all three conditions into one OR expression and
one local retirement. VC8 sends all three to one821-private tail. Splitting
the existing action, frame and sequence conditions into three ordinary guards
restores the first-two shared tail naturally. Reads, signed comparisons,
short-circuit order, decrement and return behavior are retained; no fabricated
return, helper, local, padding, assembly, type or ABI substitution is used.
This is a supported source-shape hypothesis, not proof of original spelling.

Whole-root RET-membership distance improves29->27 while the number of source
RETs stays71. The only changed RET membership is812/822 becoming812/821/822.
Call memberships stay at distance9: source817 still shares advance4351C0 with
860/861; source906 still shares three final-World/wave pairs kept private by
the target. These distances, source size and owner identity are diagnostics.

## Native evidence and audit scope

The new `audit-reimu-object-821-owner-exits.py` executes original target and
relocated source instructions. It records each actual retirement write and
root RET, with ordered writes and logical live-x87 values. It does not return
opaque helpers or infer return identity from output equality.

The6720-input matrix covers sequence3 and sequence4 controls, signed owner
word extremes, guard boundaries, five heading values (including NaN and both
infinities) and control words027F/037F. The common native fixture now accepts
an optional heading, retaining its37.25 default. The new audit reads back
its actual bits at root entry and rejects an unapplied heading input. A streamed
check confirms all133192 existing case IDs/hashf46a849f contain no explicit
heading and retain the same default; this is input identity, not output replay.

| Class | Inputs |
| --- | ---: |
|Owner action guard|2520|
|Owner frame guard|60|
|Owner sequence guard|240|
|Sequence3 continuation|540|
|Sequence4 control|3360|

Input SHA256 is
`71ff360c02f345af200d36fe15997a093bd83b4317edd6f0b09e09d2a3db8195`.
The selected control passes with zero output, ordered-write and retirement-x87
differences; first-two sharing and all three20-byte tails agree. The frozen
predecessor has the same zero numerical differences and tail bytes but is
**rejected** because all three guards share one physical tail. This negative
control prevents a finite output pass from hiding the structural defect.

The formally compiled source repeats that6720-input pass:16.78 seconds wall
at CPU0/nice10, peak RSS139136KiB. Additional focused checks pass:

* All256 existing `owner-821-follow` inputs: zero output, ordered-write and
  retirement differences, input hashd8fe09ab. These retain the default37.25
  heading and existing hold/sequence controls.
* The3600-input whole-root stride37 sample and the same3600-input helper-entry
  sample: zero output/write/retirement or helper-live-x87 differences, input
  hashe90a5943. Helper4359F0 remains unvisited. Typed-store coverage is incomplete;
  902's static float spill/reload and822's post-opaque pair remain checked, with
  zero executions of the latter.
* Scoped905/907/908: all12 actual first prefixes and conditional normal-return
  selector call graphs agree. The default still rejects906's partition.
* The World-sharing report still rejects99 target versus96 source sites.
  Its540 actual903 prefixes, four/joint conditional call graphs,180 retiring
  prefixes and18-byte shared post-call tail continue to agree.
* Sixteen actual first-World prefixes retain the12 matched906..908 packet
  offsets and905's four remaining mismatches.

The header/flags/relocations and every accepted unit outside this mixed
root/helper unit are unchanged; no unrelated exact-unit replay is needed.
No aggregate or prior full-matrix result is reissued. These checks do not
prove arbitrary aliases, resource states, unmasked exceptions, physical
TOP/flags, opaque continuations or whole-root equality.

## Complete compiler comparison and collateral changes

The selected source remains `ReimuObjectActionStateStaging.cpp`, unit
`gpt-web-reimu-object-action-state`, ordinary pinned VC8 SP1 O2/GS-off.
Headers, compiler profile, relocations, function ABI and ownership are unchanged.
The previous905 packet join, descending905..908 case order,12 first-packet
slots in906..908, local retirements and902 typed publications remain.

| Artifact | SHA256 |
| --- | --- |
|CPP|`c79f39751d0a830a4bcb031c6018246ded12cdc1336a65512f73925c64660b5d`|
|Header|`6f469e6886959fd41ee6976b3c784c3df0c2e753ad4729a536764a3c8cd28b4b`|
|Formal COFF|`d336497b21863f18cce457aa292c8e4f5778b71d86253ff813a4edaf7a22cb30`|
|Whole46160-byte canonical source section|`f903cc3239079239e0c0fff3b6a55f7713966e47053276d0c2cb38d4814346ce`|
|Fixed46138-byte compared prefix|`b8c885e697245515081bd657fcbee04fd8b9d589f4e085700ff6acdf0defdc0e`|

Source prefix45292 plus868 metadata bytes emits10449 decoded/10448 reachable
instructions,426 calls and71 RETs, retaining frame438h. Twenty-two extra
payload bytes are not near-exact evidence. First mismatch is still the default
jump displacement at49655F; same-TU4963A0 stays canonicalad12b782.

The source-to-source instruction/edge comparison finds28/43 physical owners
identical after edge/table-address normalization. Alignment and branch encoding
changes explain additional differences:853/901/904/907 loop padding,901's
jump over padding,902/907 short versus near conditional branches and removal
of the default NOP. A second diagnostic aligns byte-identical instructions,
checks every edge and all22 reviewed switch tables, and excludes only recorded
NOP forms. It leaves38/43 owners unchanged;821/901/902/907/908 remain different.
Neither diagnostic is target exactness or a permission to normalize acceptance.

There is a substantive additional908 instruction-form difference after its
first burst World/wave calls. Target4A076A loads state374 before converting
word366, then4A077F FADDP. The predecessor has that same form; the new source
converts word366 first and uses FADD from state374 memory. Both still perform
the float-field plus signed-word update, but the load/x87 form is unresolved.
This post-opaque continuation is unexecuted by the finite prefix audits.
A real, used post-wave heading snapshot compiles to the same complete new
body; that control is unselected. No finite test result certifies this window
or unmasked exception timing.

## Additional bounded controls

Before the821 guard investigation, two905 packet hypotheses were tested on
the frozen preceding295be3bc source, preserving descending mode order:

* Case-local905 packets with two actual spawns and wave per mode still emit
  six excess call sites, returning call-membership distance to15. Correct
  case order alone does not recover the target's shared consumer.
* A private `const float *` packet API, with actual unparented/parented source
  bodies and their genuine manager-call typedef, reproduces the complete
  baseline46152-byte canonical7c16e018 body unchanged. The new typed wrappers
  independently compare78/78 and77/77. Pointer element type is not uniquely
  proved by the existing wrapper bytes; no shared header or binding is changed.

The helper66 remains exact in both controls. These are completed private
compiler experiments, not new accepted units, unique declaration recovery or
an LTCG/standalone impossibility claim.

## Reproduction and retained artifacts

Artifacts/frozen inputs are in `build/reimu-object-905-lifetimes-20261021/`;
private recipes are under the corresponding `.analysis/` path. Canonical
comparison, formal build provenance and finite runtime scope are separate
receipts. Complete46160-byte native equality bridges the guard-control COFF
to the tested formal COFF and to the final metadata-only rebuild. The formal
receipt separately attests current source/compiler inputs. Older26342/133192
receipts remain historical source epochs and are not bridged to this body.

26 completed unselected/control files are compressed2029617->262971 bytes
with per-file SHA256 readback before removal. `compression-manifest.json`
marks the discarded initial ignored-heading receipt as invalid validation
evidence; the actual applied-heading checks above are separate receipts.
Baseline, selected and independent-guard control inputs remain loose.
Primary databases, canonical executable and compiler tools are retained.

```bash
# Expected exit1 for the whole root; helper must remain66/66.
taskset -c 0 nice -n 10 python3 scripts/build.py \
  --unit gpt-web-reimu-object-action-state --compare --json
taskset -c 0 nice -n 10 python3 scripts/audit-reimu-object-821-owner-exits.py \
  build/match-units/GptWeb_ReimuObjectActionState.obj \
  --output build/reimu-821-owner-exits.json
taskset -c 0 nice -n 10 python3 scripts/audit-reimu-object-retirement-fpu.py \
  build/match-units/GptWeb_ReimuObjectActionState.obj --stride 37 \
  --output build/reimu-821-root-sample.json
python3 scripts/validate-tracking.py --require-target
taskset -c 0 nice -n 10 python3 scripts/ci.py
git diff --check
```

905 packet placement,906/817 sharing, remaining returns,908's post-wave load
form, original source/TU and full canonical equality remain open.
