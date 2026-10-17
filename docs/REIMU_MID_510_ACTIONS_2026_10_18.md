# Reimu:510..513 middle family

## Target and source observations

Target is original Japanese TH10.5 v1.06a, SHA256
`56350024879199861579c11b0e1c67b9590e10a8d40cd5996b109deec9afca7e`.
Parent `Reimu_dispatch_action_state_vslot28 @478FA0` remains81550 bytes,
ending48CE2E, SHA256
`dbf6f375a809fea91cbbccf0f8cff2196f40cba11458c98e475a290b623053e6`.
Its candidate/origin/name/source selection were rechecked: authored,
unclassified/declaration-only. No implementation or exact entry is added.

The four physical bodies are `[483375,484F96)`:7201 bytes/1700 instructions,
SHA256 `8aa87ea6f50a35365e2bae72a83c6806edd0fe30ed833f0285fe6a32e2d6f2d8`.
Canonical primary-table indices/destinations and every body hash are checked.

|Action|Entry|Next physical entry|
|---|---|---|
|510|483375|483A4A|
|511|483A4A|484101|
|512|484101|484835|
|513|484835|484F96|

These bodies share the preceding500 family's charge/landing/completion rules.
`ReimuActionStateMid500Cases.hpp` now includes all twelve cases, with explicit
510-family differences: BYTE+17C=8, wave index20, object812, and the angles
below. The same monolithic entry/low/middle method admits<=513, uses real
common4740C0 for gaps and returns pending for>513. It remains a staged bool
interface, not the original complete void-root ABI.

|WORD+736 level|Ordered812 angles; speed15 and third float0|
|---|---|
|0|30,0,-30|
|1|45,15,-15,-45|
|2|60,30,0,-30,-60|

Separate live level tests are preserved after each group. Every request
reinitializes three floats and re-reads position/facing. Ground510/511 use
x+signed-facing114,y+96 and frame2; aerial512/513 use x+signed-facing50,y+108
and frame1. All fire at sequence2/timer0 before advancing animation, consume
200/floor120, publish state1, add scaled50, then dispatch wave20 before the
level tests. Input selection remains full DWORD+6C0 for510/512 and+6C4 for
511/513, active when signed sequence<=1; direction is a raw unsigned byte.

Aerial sequence<5 crossing reuses4824FA zero/height/set5/RET; sequence4 first
publishes/subtracts0.6f. Aerial sequence5 node entry reuses48748C set9/RET.
The >20/>60 charge sequence and signed(level+1)*10 tail reuse481D78/481DA1,
and effect argument completion joins481D6C. No new helper ABI or class field
is invented. The compact C++ angle loops are a source hypothesis: the target
has physically expanded request sites. Original source spelling, compiler
unrolling/sharing and complete TU provenance remain unproved; this source
shape is not an instruction-equality claim.

## Focused build and execution

```bash
scripts/compile-unit.sh src/characters/ReimuActionStateDispatch.cpp build/reimu-mid-510/ReimuActionStateDispatch.obj
python3 scripts/audit-reimu-mid-510-actions.py build/reimu-mid-510/ReimuActionStateDispatch.obj
```

Before editing, a fresh previous-source build passes0/72 under its existing
oracle (`baseline-smoke.json`). Pinned VC8 SP1 `/O2 /GS- /GR /EHsc /MT`,
default FP/no injected compiler environment, now produces23861 staged text
bytes. Object SHA256
`9118a5126112e985c30d24277c191a2450920a854f19f302a78276a8d8a8bee0`;
manual compiler/source/header/object receipt:
`build/reimu-mid-510/build-receipt.json`. The oracle separately pins its
object/support inputs and does not itself attest compilation provenance.

**0/2493 differences**, report `build/reimu-mid-510/native.json`, input SHA256
`5d5403bfc1b43467544ac0239d045525587e86008f06b7d516def3a4b15eafd1`:

|Cohort|Cases|
|---|---:|
|Sequence/landing/completion/NaN motion profiles|336|
|First requests, signed levels/facing and scaled phases|600|
|Charge boundaries, latches and distinct full-width input pairs|864|
|Signed level arithmetic and strict tail cutoffs|288|
|12 required original branch sites, both x87 precisions|24|
|Earlier500/shot/projectile/middle/low/entry/common-return paths|373|
|509 default transfer|1|
|Later source handoffs|7|

1844 cases reach native RET;399 stop at actual object465190 entry,232 at
effect435240,7 at common4740C0 and1 at set669. Another10 compare original
pending state at47CC5F with a genuine source false return.5407 original-root
and2945 staging instruction addresses are sampled.636 scaled-counter and
627 wave calls execute actual native helpers, including real zero-handle
sound dispatch; no result is substituted.

The inherited engine compares4096 actor bytes, ordered helper/receiver/
argument traces, physical conversion inputs, world scalar, MT state and
control word. Returns require stack delta4, preserved callee-saved registers
and x87 TOP=0.812 requests require an aligned live stack pointer, count3,
the advertised object ID, BYTE+17C=8, and all12 pointed bytes. Initial17C is73.
Input profiles are reused without mutating imported modules or presetting
candidate outputs.

Only each volley's first actual request entry is reached. Later angle
iterations, subsequent groups after returning opaque calls and post-effect/
manager continuations remain dynamically unproved. Their value/order has
raw instruction evidence. No full-volley, whole-game or canonical-exact
equivalence is claimed.

Compiled wrong-source controls fail:

- Replace wave20 with wave4:4/36 smoke cases differ in the real call trace.
- Replace the510-family flag8 with4:36/36 smoke cases differ.
- Replace level0's first angle30 with20:2/36 smoke cases differ.

Reports `wrong-wave.json`, `wrong-flag.json`, `wrong-angle.json` are in the
same build directory. Controls are ordinary modified C++/VC8 with a private
include directory, with no target-byte/helper-result patch. Rejected sources
and objects are removed after inspection.

## Preservation, analysis and next work

Fresh old500 replay passes0/72 in the expanded method. All six older adapters
rebuild with identical non-debug code/data and relocation offset/type/symbol/
value/section identities, sizes530,771,1562,4017,4409,11271; receipt
`build/reimu-mid-510/preserved-stages.json`. Old focused smokes pass0/9,0/88,
0/64,0/99,0/150,0/59. Full historical matrices are not repeated. No accepted
unit uses this private header, and no accepted source/profile/relocation
ledger or exact total changes; no aggregate cold replay is claimed.

One direct Ghidra read-only clone attests executable identity, entry68B9D2,
base400000, Windows x86, mapped.text and full-root hash, then reads back all
four entries/shared exits. Marker `REIMU_MID_510_READBACK_PASSED` is in
`build/reimu-mid-510/ghidra.log`. All9 primary DB file hashes are unchanged,
and the clone is deleted. The wrong-target IDA preflight supplies no semantics.
Superseded objects, rejected controls and Python caches are cleaned after gates.

The supplied read-only animation, flat surface, zero wave/texture/event
handles, inactive secondary-event cycle and masked PC53/PC64 bound this proof.
Other runtime/backend contexts and complete floating-exception behavior
remain unknown. Next continue520..550 and high actions, then actual returning
world contexts. Full void ABI, CFG/relocations, truthful VC8/LTCG/TU provenance
and all81550 canonical bytes remain the parent's exact acceptance requirements.
