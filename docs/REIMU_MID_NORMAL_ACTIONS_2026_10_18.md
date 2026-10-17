# Reimu: first middle-table action group

## Target observations and source scope

Only original Japanese TH10.5 v1.06a is used, executable SHA256
`56350024879199861579c11b0e1c67b9590e10a8d40cd5996b109deec9afca7e`.
The parent is `Reimu_dispatch_action_state_vslot28 @478FA0`,81550 bytes,
ending48CE2E, SHA256
`dbf6f375a809fea91cbbccf0f8cff2196f40cba11458c98e475a290b623053e6`.
Its ledger/source selection remains unclassified/declaration-only. There is
no new implemented entry, exact unit or authored-byte credit.

The new `ReimuActionStateDispatch.cpp` includes the existing entry/low case
fragments and `ReimuActionStateMidNormalCases.hpp` in one ordinary method.
It handles actions301..310 and320..322, sends311..319 to the actual common
method, and returns pending for actions>322 after entry processing. The old
low-only method remains a regression adapter. Neither bool method is an
original boundary or the original void-root ABI.

The13 physical bodies form `[47CC8E,47DB64)`:3798 bytes/1011 instructions,
SHA256 `b79fee4e23bb94b8cccbfac521372e89506fb7521773b29d7f50f3ab03fa873c`.
These are observed source regions, not standalone callable boundaries.

|Action|Entry|Next physical entry|
|---|---|---|
|301|47CC8E|47CD70|
|302|47CD70|47D02B|
|303|47D02B|47D14A|
|304|47D14A|47D441|
|305|47D441|47D505|
|306|47D505|47D60F|
|307|47D60F|47D6FC|
|308|47D6FC|47D7CF|
|309|47D7CF|47D857|
|310|47D857|47D96A|
|320|47D96A|47D9E1|
|321|47D9E1|47DA6D|
|322|47DA6D|47DB64|

The root's prior EDX=0, ECX=1 and EBP=7 definitions explain reused constants;
these are not additional fields or implicit helper results.301 clears its
velocity flag only after a strictly negative stored velocity, preserving
the zero and unordered cases.303 reads the same byte as signed, subtracts
the double representation of0.6f and checks separate live timer/frame gates
for events at3/5/7/9.304 has conditional landing calls, two distinct gravity/
landing branches, and an immediate shared next-block/RET at4852F6 when
sequence5's signed DWORD counter reaches12. Its sequence3 completion reuses
479486.306..309 share existing set10/height/zero-motion exits, while306's
counter>12 check precedes advancement and308's counter>10 check follows it.
310 preserves signed WORD wrap, signed remainder15, angle updates and its
early landing next-block return.320/321 reuse the event/flag-clear exit at
47CC49. These source choices are inferences from the canonical instructions.

The private prefix exposes only observed DWORD+6BC and BYTE+750, with offset
assertions; the complete class layout remains unknown. A typed pointer
overload of the existing real object wrapper carries three float parameters.
The target initializes them to0/0/1 for302,0/0/3 for306 and0/0/5 for308.
There are no invented helper bodies or fabricated callback results.

## Focused build and native comparison

```bash
scripts/compile-unit.sh src/characters/ReimuActionStateDispatch.cpp build/reimu-mid-normal/ReimuActionStateDispatch.obj
python3 scripts/audit-reimu-mid-normal-actions.py build/reimu-mid-normal/ReimuActionStateDispatch.obj
```

VC8 SP1 `/O2 /GS- /GR /EHsc /MT`, default FP, no injected compiler environment,
produces14878 staging text bytes. The manual compiler/source/header/object
receipt is `build/reimu-mid-normal/build-receipt.json`; the oracle separately
pins its object and support files and does not claim compilation provenance.
Object SHA256 is
`057294a8359523333f3a3c8c035cc58cde6fa704403e547f24621ba4fbf4d244`.
The object has the partial bool ABI and is not canonically equal to the parent.

Final focused native result: **0/5729 differences**, report
`build/reimu-mid-normal/native-final.json`, input SHA256
`d56e546164c6f775248597e292c066250071455bd835994833388fd703016247`.

|Cohort|Cases|
|---|---:|
|Motion, sequences0..6, landing and airborne contexts|1274|
|Friction: signed byte values, exact thresholds, +/-zero, NaN|864|
|Frame/event gates including7/9/12; held/latch inputs|1040|
|Node starts and signed-facing extremes|910|
|310 state/counter/WORD-wrap/remainder cases|756|
|Real directional transitions|252|
|311..319 actual common-method entry|36|
|Later handoff versus entry gates|32|
|29 required original branch sites, both x87 precision settings|58|
|Six actual request paths, coordinates and facing extremes|420|
|Old-path smoke plus28 genuine common-function returns in new method|87|

5211 cases reach native RET;151 stop at real effect435240 entry,313 at real
object465190 entry,42 at real common4740C0 entry and1 at real set669 entry.
Another11 compare pending later-source state at original47CC5F with the
candidate's genuine false return. The pending frames are not claimed to be
interchangeable machine-stack continuations.1961 original-root and1575
candidate instruction addresses are sampled.

The inherited engine executes unchanged native animation, action/sequence
setters and character finalizers, surface helpers, real MT and orientation
initialization. It compares all4096 actor bytes, ordered receiver/argument
traces, physical conversion inputs, control word, world scalar and MT state.
Genuine returns require stack delta4, preserved callee-saved registers and
x87 TOP=0. No full x87 tag/exception or whole-game proof is claimed.

At actual object848 entry, the oracle validates a live supplied-stack pointer
and count3, reads all12 payload bytes, and compares their contents alongside
the other arguments. Each side owns a different stack layout, so numeric
pointer equality is not required. It stops before the real wrapper executes;
returning manager/effect contexts and subsequent operations remain unproved.

Initial ground-action fixtures at y=100 could change action/sequence in the
real landing helper before the intended event branch. Sensitivity controls
exposed this coverage gap. Ground contexts now use y=0, retain explicit
airborne cases, and require29 observed native branch PCs. These include both
302 spawn sites,304's shared cutoff/RET, all four303 events and the remaining
launch/landing/counter gates. Inputs are not preset to candidate outputs.

Three compiled wrong-source controls are rejected:

- Changing302's first pointed payload from0/0/1 to0/0/2 fails1/104 smoke.
- Changing301's strict negative clamp to<=0 fails6/864 friction cases.
- Changing304's shared counter>=12 exit to>12 fails2/1274 motion cases.

Control reports are `wrong-payload.json`, `wrong-zero.json` and
`wrong-shared-exit.json` under the same build directory. The controls use
ordinary modified C++ and the same compiler profile, adding only a private
include directory; their source/objects are removed after inspection.

## Preservation, analysis safety and remaining work

All six previous staging objects are freshly rebuilt. Their non-debug code/
data sections and every relocation's offset/type/symbol/value/section identity
remain identical to the prior checkpoint. Sizes remain530,771,1562,4017,4409,
11271; receipt `build/reimu-mid-normal/preserved-stages.json`. Debug/file/
timestamp metadata is excluded only from this preservation check. Canonical
acceptance rules are unchanged. Old focused replays pass0/9 entry,0/88 low,
0/64 recovery,0/99 movement,0/150 late-low and0/59 low dispatch. Their full
historical matrices are not repeated, and no accepted unit uses this header.

The read-only fixture supports fourteen frames/seven sequences/64 keys with
computed nonoverlapping spans. Its default six-frame output stays byte-equal
to the previous implementation for48 combinations of key count/frame/profile.
Nineteen structural tests include the highest frame of every64-key sequence.
Native fixtures still use supplied animation, flat surface, zero texture/
event handles, inactive secondary-event cycle and masked x87 PC53/PC64.
Returning world requests, other contexts and immediate floating exceptions
remain unknown; successful sampling is not exhaustive equivalence.

One direct Ghidra read-only clone attests executable identity, entry68B9D2,
base400000, Windows x86 language, mapped.text and full-root bytes. It reads
back all13 entries plus the mid selector, shared advance tail and default;
`REIMU_MID_NORMAL_READBACK_PASSED` is in `build/reimu-mid-normal/ghidra.log`.
The rejected unrelated IDA session supplies no semantics. All9 primary DB
files remain hash-identical, and the disposable clone is deleted. Superseded
objects, rejected control products and Python caches are cleaned after gates.

Next continue the same parent at actions400 onward, then finish the remaining
middle/high source and actual returning world contexts. The acceptance work
still requires the complete void-root ABI, full CFG/relocations and truthful
VC8/LTCG/TU provenance before comparing all81550 bytes. Exact progress is
unchanged by this staged source checkpoint.
