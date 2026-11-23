# SakuyaObject complete update: 2026-10-25

`SakuyaObject_update_action_state @ 0x004E0D30` now has a manual complete-body
source hypothesis. The first differing field at `0x004E0D55` points to
`0x004E7E55` in the rebuild and `0x004E7E50` in the target. The
default frame call and its seven epilogue instructions agree after
rebasing. The selected source restores action
803's alpha continuations and the 920 match-ID switch layout. See
[the action 803 comparison](#action-803-keeps-two-alpha-calls) and
[the frame-path comparison](#frame-calls-and-cross-case-registers).

## Observed target and complete boundary

The executable is original Japanese 1.06a, SHA256
`56350024879199861579c11b0e1c67b9590e10a8d40cd5996b109deec9afca7e`.
IDA preflight rejects the GUI's different executable. All analysis reads use
the hash-attested PE or the independently attested optional database below.

RTTI-backed roster evidence and raw primary slot 28 cell 6C48B4 bind SakuyaObject
vtable 6C488C to 4E0D30. Its separate slot 3C cell 6C48C8 points to 4E8060, the
previously reviewed initializer. No initializer implementation is changed here.

The callable range is `[4E0D30,4E7E69)`,28985 bytes, SHA256
`592df4424de962d219caa2e73d62ab420ed0d0438ba009b20b94f4b9df51ca94`.
Raw traversal closes all 6774 decoded instructions/all28985 bytes,47 RET 0s,
232 direct calls to 20 entries and 48 indirect calls. Every branch and table
destination stays within the callable range. There is no external direct tail
jump or unreviewed unreachable callable instruction.

The prologue aligns ESP to eight bytes, allocates 0xD0 bytes, saves EBX/EBP/ESI/
EDI below that frame and retains ECX in ESI. No GS/EH frame is present. The
source uses a pointer-only virtual view and typed offsets; never instantiate
or embed this as a recovered complete allocation. Original nominal return
type, full class layout and original translation unit remain unknown.

Complete `[4E0D30,4E8054)` is 29476 bytes, SHA256
`453a7abb8a48642f5852078059893f8611d26b07c77ae67d8747c4fadcd42ce3`.
Its 491 noncallable bytes partition as:

| Address | Contents |
| --- | --- |
| 4E7E69 | three-byte LEA ECX,[ECX] alignment |
| 4E7E6C |33 DWORD destinations |
| 4E7EF0 |200-byte remap for actions 800..999 |
| 4E7FB8 |5 DWORD destinations |
| 4E7FCC |5 DWORD destinations |
| 4E7FE0 |7 DWORD destinations |
| 4E7FFC |9 DWORD destinations |
| 4E8020 |4 DWORD destinations |
| 4E8030 |9 DWORD destinations |

All 72 destination DWORDs/288 bytes and 200 remap bytes participate. Twelve INT3
bytes separate this payload from 4E8060; none is included. Metadata/alignment
receive no callable-byte credit.

The switch checker traverses all 28,985 callable bytes with the expected
relocation sites. It rejects a change to another valid index at `0x004E7FB7`
and the removal of one table-word relocation in separate controls.

The 32 explicit primary actions are 800..805,810..813,815..818,849..859,
900,901,920,930,980,998,999. All other remap entries reach the default frame
continuation. Nested state switches belong to 803,815,859,901 and 999;920 also
switches on the existing match-identifier global.

## Optional analysis hypothesis and manual source

A single direct Ghidra headless process ran readonly/noanalysis, CPU 0/nice10,
one CPU and 384MiB heap. It attested the imported executable SHA256, PE image
base/entry, language/compiler and all mapped section bytes before inspecting
this root. The temporary bounded body and declaration-only callee ABI views
were read back. The root entry was removed, the transaction rolled back, and
root metadata read back again. All nine primary project-file hashes agree
before/after; the process terminated 0 with its attestation sentinel.

The private 3119-line decompiler output is a control-flow/type hypothesis, not
selected source. The manually written source expresses 32 complete actions with
numeric states, typed offset reads/writes, consumed local parameter packets and
real declaration-only calls. Target instructions determine widths, physical
edges, helper contracts, scalar rounding and publication order. No decompiler
temporary-name translation or copied output is used as the implementation.

The source hypothesis does not assert full execution equivalence.

## Callee and scalar evidence

Working call views receive no new callee implementation/exact credit. Existing
ledgers supply the independently reviewed providers; call sites still constrain
their use here:

| Target | Physical calls | Working role |
| --- | ---: | --- |
|5575C0|12|three-int effect emission, AL result|
|435160|27|receiver+4, oriented components, two floats|
|45C030|40|owner wave handle, one unsigned index|
|4067D0|34|cdecl random roll, one limit|
|496420|13|secondary animation, int/float/three ints|
|4963F0|13|secondary renderer release|
|4351C0|17|frame continuation, AL result|
|4963A0|9|six-counter continuation, one int/AL result|
|4FCA60|6|parented spawn, seven stack words|
|496370|3|secondary alpha, byte in four-byte stack slot|
|435D60|3|stage height, ECX receiver/ST0 result|
|406540|23|cdecl atan2, two floats/ST0 result|
|4E0BF0|2|heading adjustment, three floats|
|465190|3|Fighter-owned spawn, seven stack words|
|4063D0 /406360|6 each|quantized cosine/sine, float argument/double ST0 result|
|64CCB0|8|unparented spawn, seven stack words|
|406580 /478DD0|4 /2|square/square-root scalar helpers, ST0 result|
|53CBC0|1|ping-pong movement and periodic spawn|

Examples of independently inspected source distinctions:

- The RNG provider retains its accepted int declaration, while these callers
  explicitly reinterpret the result as unsigned before conversion: FILD plus
  a conditional 2^32 addition is observed. The unsigned `roll(16)-8` conversion
  is preserved too. It must not be replaced with a signed random range.
- The 800-family speed products visibly store/reload a float before adding
  the wider 5/6 constants. Twenty-one corresponding random-speed expressions
  now retain that consumed single-precision boundary. Float-promoted qword
  operands such as 0.01/0.1/0.05 use the target's extended float values.
- The 805 and 810 trigonometric consumers use ST0 without an intermediate float store.
  Raw 810 spills the captured facing value as a qword across the trig call.
  Its duplicated owner-valid/owner-invalid orbit paths remain independent
  call sites; all six sine and six cosine calls survive. Captured owner
  pointers and vertical coordinates respect their observed call epochs.
- The 859/901 distance paths capture the radius-times90 product as a float
  before calls, retain the first squared result in a qword across the second
  square call, then round the sum for the square-root argument. These real
  consumed wider values restore ordinary eight-byte stack alignment.
- Six real three-float spawn packets occur in 802,804,805 twice,817 and 818.
  Giving each its observed independent local lifetime replaces one shared
 16-byte packet with six 12-byte packets: the 56-byte difference explains the
  measured frame change 0x98 to 0xD0 exactly. Each packet is passed to a real
  parented/owned spawn. The remaining packets also have real call consumers.
- Several bounds paths use ordered conjunction rejection; other paths use
  explicit outside comparisons. These differ for unordered inputs and remain
  separate. The 803 transparency conversion saves the x87 control word, sets
  truncation bits 0xC00, executes FISTP and restores the control word. Source
  byte conversions and captured scalar values retain this contract.
- 849 performs two horizontal updates and two quarter-scaled vertical updates
  in its phase 2 path. They remain separate operations.998 performs its three
  distinct parent-action position checks.999 retains independent parent
  coordinate publication, repeated stage-height calls and post-frame velocity/
  gravity publications. These repeated operations are not deduplicated.

Four separately declared float cells 6FBD1C/20/24/28 are provisional boundary
views. Their address aliases attest loader-zero storage, not runtime constant
values or a complete global owner. The existing 6FA894 match-identifier binding
is reused unchanged.

## Early whole-function comparison and controls

Every successful comparison below replays the complete emitted symbol and all
relocations. No code, jump table, remap or alignment bytes are masked.

| Complete source/control | Full bytes | SHA256 prefix | Evidence/result |
| --- | ---: | --- | --- |
| First manual body |—|—|ordinary random conversion helper remained out of line; unsupported target edge stopped replay|
| Expand the real random conversion expression |29312|f7a99fa9|first complete canonical comparison; unaligned 0x8C frame,50 RETs/16 frame calls|
| Preserve observed double captures/results |29200|29d991de|eight-byte alignment restored;0x98 frame,52 RETs/17 frame calls|
| Restore six independently consumed packets |29264|ba67850d|target 0xD0 frame restored exactly|
| Restore random-product float boundaries |29408|f82af9da|21 rounded products retained; first+37 remains|
| Capture 803 alpha before byte conversion |29408|3e0aa7a9|selected complete source; scalar allocation changes, but alpha calls remain 2/3|

All seven destination-table dimensions 33/5/5/7/9/4/9 and the full 200-byte primary
remap agree. All 48 virtual calls and 19 of 20 direct-callee counts agree. The
selected source has 52 RETs against 47 and two secondary-alpha calls against
three. There is no byte-neutral repeat grid, compiler-profile change, behavior
matrix, assembly, copied byte array, padding, inert local or fake return.

All 738 selected section relocations replay. Formal and independent cold
objects reproduce the same 29408-byte canonical hash and 27397 differences.
The physical comparison remains broadly different; matching frame/counts are
diagnostics only. No `matches.csv` row or exact-byte credit is added.

A generated-COFF-only negative changes the final default-remap entry for source
action 997, at generated address 4E7F71/+29249, from valid index 32 to valid 0.
That byte originally agreed with the aligned target byte. Parsing succeeds,
but full differences rise to 27398, SHA256
`e424044cb987942ef1e2e8524a110d3d13ac4222fb3e4b59e8e94c70c701370b`.
The canonical PE and selected object are unchanged. Five synthetic controls
exercise all seven tables/200 indices, an invalid final remap index, a metadata
destination, a truncated final table and an external CFG tail.

## Reproduction and continuation

Use locked repository Python and serial CPU 0/nice10 jobs. The retained nonexact
comparison commands intentionally return 1:

```sh
taskset -c 0 nice -n 10 scripts/repo-python scripts/build.py --unit exact-first-sakuya-object-update --compare --json
TH105_ENABLE_GS=0 TH105_FP_MODE=default TH105_INLINE_MODE=default \
  taskset -c 0 nice -n 10 scripts/compile-unit.sh src/characters/SakuyaObjectUpdate.cpp build/sakuya-object-update-cold.obj
```

Only the local source/interface/unit,79 exclusively named literal aliases and
four boundary-address aliases are added. No accepted unit references these
aliases. Previous source/layout/header/compiler/bindings remain unchanged.
Accepted graph remains 524 units/1412 functions/381108 callable authored bytes;
the prior Remilia checkpoint is still the latest aggregate cold receipt. No
new aggregate cold replay is claimed. Ledger validation records mapped 1578,
source-present1559 and 598 configured units/1566 functions;1484 floating target
references pass.

## Follow-up: physical sharing and closed controls

The baseline formal replay retains the selected full 29408-byte hash above and 27397
differences. These are complete canonical comparisons with relocation replay;
shorter output or fewer differing byte positions does not establish a better
reconstruction.

Static traversal from each primary case entry distinguishes physical call
sites, rather than only their total count. It follows both conditional edges
and every nested switch destination, so it overapproximates feasible execution.
It is neither a runtime matrix nor a proof of execution equivalence. Some
cases share tails; their reachable-return counts must not be summed.

For frame helper 4351C0, target 812/815/855 reach the same physical call 4E319E.
The selected source shares 812/855 at 4E31B2 but leaves 815 at 4E3A07. Conversely,
target 816 owns 4E3FC8, while the selected source folds 816 into 4E1DAD, shared with
803/811/813/850/852/856/857/858/859/900/901/980/998. The corresponding target
group uses 4E1D99 without 816. Thus the matching total 17 frame calls compensates
for two different sharing decisions; it does not establish the target graph.

Target 803 owns two alpha-helper calls 4E18CD/4E1BD8. Its generated second path
instead joins the first call at 4E18DA through the receiver reload at 4E18D8.
Raw target 0/1 loads that receiver before FNSTCW;3/4 loads it after the argument
push but before FLDCW. These observations identify allocation/sharing epochs,
without proving the original source expression or nominal helper prototype.

Fresh raw provider 496370 is 35 bytes, SHA256
`6f202f689fce83ecace5dbfc88c86b7beb43987372f2320c272cb9f47f9072f1`.
It reads only the low byte of the four-byte argument slot, composes the alpha
word and tails 42FD80, or returns with RET4 when its renderer is absent. This
supports a local word-carrier diagnostic with explicit caller byte casts;
it does not recover an original nominal int parameter or justify changing the
selected declaration/shared provider.

| Isolated question / receipt basename | Full bytes | SHA256 prefix | Differences / observation |
| --- | ---: | --- | --- |
|803 zero on left of comparison: `zero-left803`|29416|cfd9d773|27270;52 RETs, alpha 2|
|803 consume assigned alpha directly: `consumed-alpha803`|29408|f82af9da|27397; identical to prior random-product candidate|
|803 local low-byte word carrier: `word-carrier803`|29412|60311bf6|27279;52 RETs, alpha 2|
|815 explicitly joins 812 frame tail: `shared-frame815`|29040|ffc4bfc5|27562;48 RETs,16 frame calls, alpha 2|
|816 early-return spelling on previous control: `early-return816`|29040|ffc4bfc5|byte-identical to previous control|
|800 inclusive 2/4/6 relation forms: `inclusive-phase800`|29404|7aafbb15|27218;52 RETs,17 frame calls, alpha 2|
|800 consumed next-Y capture: `captured-position800`|29408|3e0aa7a9|byte-identical to selected source|

Each basename has a full JSON hash/comparison, canonical binary, disassembly,
relocation bindings, object and compiler log. The explicit 815 join answers a
real target edge but triggers broader tail factoring and loses a frame call;
it is unselected. None of the controls restores three alpha calls or 47 returns.
The consumed-alpha, early-return and next-Y questions have repeated complete
outputs and are closed absent new independent evidence. Inclusive comparisons
do not justify adding a constant local to force EBX. No flag grid or runtime
matrix was run.

No implementation/header, accepted unit, literal binding, exact ledger or
aggregate total changes in this follow-up. Keep the selected 29408/3e0aa7a9
source and its mandatory nonexact status. Park 4E0D30 and independently review
another source-missing large Object root;5F9420 is a provisional 27874-byte
KomachiObject slot 28 candidate, requiring its own fresh attestation and complete
boundary/ABI review. Remaining Sakuya unknowns include full execution
equivalence, precise expression/return sharing, original nominal owner/return
type and original TU/compiler context. No new aggregate cold replay is claimed.

## Action 999 landing sum, 2026-11-04

Native `0x004E7CD4..0x004E7CF6` stores the updated vertical speed as a
float, reloads it, adds the position, and retains the sum as a QWORD across
the surface query. The previous `float next_y` rounded the sum before that
query. It now retains the sum as `double`. The fresh VC8 object at
`0x6F58..0x6F7A` reproduces that local float store, QWORD sum and ordered
comparison sequence. This is not a claim of whole-function exactness or
unmasked-exception equivalence.

The 28,985-byte callable remains nonexact from +37; the candidate section
tail is 29,400 bytes. No exact credit is added.

## Action 859 ordered scale clamp, 2026-11-04

At `0x004E63CA..0x004E63F8`, native stores the scale as float and clamps
it at one only when the comparison is ordered and at least one. The status
mask is 1, so unordered values skip the clamp. The previous negated `< 1`
also clamped NaN. The source now uses `>= 1.0f`; fresh VC8 emits the same local
mask and skip branch at `0x56F9..0x5701`. This does not establish whole-root
or unmasked-exception equivalence.

The 28,985-byte callable remains nonexact from +37; the candidate section
tail is 29,396 bytes. No exact credit is added.

## Actions 920 and 930 bounds, 2026-11-05

Raw target branches at `0x4E7760..0x4E77AC` and `0x4E7AAE..0x4E7B04` retire on ordered comparisons outside the X/Y bounds. In particular, unordered coordinates pass these checks. The source previously included unordered values through a negated lower-bound test in action 920 and negated in-range tests in action 930. Both now use the observed ordered outside comparisons. The focused build preserves the lower-Y branch forms at candidate `0x6A05..0x6A10` and `0x6D5E..0x6D6F`. The full root remains non-exact: 28985-byte target, 29396-byte candidate section tail, first mismatch +37. No exact credit is claimed.

## Actions 800–818 bounds, 2026-11-05

Six further outside checks in actions 800, 801, 802, 804, 817 and 818 use ordered comparisons in the target, rather than negated in-range comparisons. Target evidence includes `0x4E10DD..0x4E1127`, `0x4E1370..0x4E13BA`, `0x4E1678..0x4E16C2`, `0x4E2072..0x4E20C8`, `0x4E433A..0x4E4384` and `0x4E46E2..0x4E472A`. Their source now uses the existing ordered-outside expression, preserving the target behavior for unordered coordinates. Focused compilation confirms the branch form, including `test ah, 0x05; jnp` at candidate `0x3EA..0x3F5`. Full root comparison remains non-exact (28985 target bytes, 29396-byte candidate section tail, first mismatch +37); no exact credit is claimed.

## Direct random velocity additions, 2026-11-05

The native RNG(40) velocity paths multiply by the double-promoted `0.1f` and add 6 before storing the float, including `0x4E19B8..0x4E19C4` and eight further physical paths. The native RNG(30) heading-speed path similarly adds 3 before its final float store (`0x4E7627..0x4E7641`). The previous source rounded the product to float first in all ten source paths. It now preserves the target's direct arithmetic, while retaining the distinct six RNG(30)-plus-5 paths whose native product really is rounded first. Fresh VC8 emits ten direct additions and six intermediate stores, matching those target physical counts; the complete 28,985-byte callable remains nonexact at +37 (candidate section tail 29,344), with no exact-byte credit.

For the plus-3 path, normal RNG result 21 gives approximately 5.0999999046 with the native/direct order versus 5.1000003815 with the former intermediate float rounding. For RNG(40) plus 6, no final-float difference was found over the normal 0..39 range. This is a local arithmetic comparison, not a claim of complete gameplay validation.

## Seven phase dispatches (2026-11-06)

Native phase dispatches at `0x4E1177`, `0x4E140E`, `0x4E3FF4`, `0x4E43D4`, `0x4E4843`, `0x4E738E` and `0x4E77ED` sign-extend the phase and use switch-style grouped or three-arm branching. The equivalent if/else chains in actions 801, 802, 817, 818, 849, 920 and 930 now use ordinary switches, restoring the local signed phase loads and branch families in the focused VC8 output. Case and default behavior is preserved; register allocation and the complete function still differ. The section tail is 29328 bytes, first mismatch +37; no exact credit is claimed.

### Timer gate thresholds

Four original timer gates at `0x4E4EE9`, `0x4E51C4`, `0x4E5487`, and `0x4E54E9` use thresholds 15, 180, 120, and 40. Equivalent `>=` source forms recover the local signed comparisons and branches while preserving integer behavior. The complete function remains non-exact; the candidate section is 29,328 bytes.

The repeated five-frame color-fade gate, including original `0x4E3999`, now uses an equivalent `>= 5` form. The candidate recovers the native threshold and signed branch family, though shared-tail folding and branch length differ. Its section is 29,228 bytes; the complete function remains non-exact.

Three repeated early-frame scale gates at `0x4E38F7`, `0x4E6779`, and `0x4E70FA` use the equivalent `<= 3` form. Fresh compilation recovers the signed compare and branch family, with some branch distances still different. The complete function remains non-exact.

The two 20-frame gates at `0x4E4434` and `0x4E4656` now use equivalent native threshold forms and recover the local signed comparisons and branches. The complete candidate remains non-exact.

## Shared tails and real runtime providers (2026-11-09)

Sakuya now calls the existing CharacterObjectRuntime motion, frame-advance and
six-state implementations. The three undefined aliases and empty motion-view
class are removed. A complete native CFG check proves all 53 receivers: the
27 motion calls use owner+4, while 17 frame calls and nine six-state calls use
the owner itself. The shared provider header and implementations are unchanged.

The accompanying tail review covers all 32 primary actions and verifies that
all 37 physical writes to life counter `+0x330` decrement it by one, including
register-carried constants across shared tails. The existing source correctly
preserves these reviewed reset-counter conditions:

- 804 checks sequence 1 and then 2; 805 checks sequence 3.
- 812, 815 and 855 enter the `0x4E31B0` tail with its sequence comparison
  resolved to 1.
- 849 checks sequence 1 and then 2. Its last jump enters the shared conditional
  branch after its own comparison, so the preceding sequence-1 comparison at
  `0x4E31D9` is not executed on that edge.

Action 810 also contains a redundant original condition that must not be
rewritten as a parent-state test. `0x4E24F0` loads the object's sequence into
CX; `0x4E24FD` compares it with 1, and `0x4E2523` later compares that unchanged
CX with BX=2. Only the intervening action checks read the parent. The source's
own-sequence condition therefore reflects the original instructions. This
review found no additional retirement bug.

Fresh full payload comparison remains 29,228/native29,476 bytes, first mismatch
+37, with unchanged canonical SHA-256
`116e0ac5d4587b9b1c4fbe1731b5088b81a1f6bec5df01e30e115452edfb9469`.
All 83 non-debug COFF sections retain their bytes, attributes and relocation
roles after the three external-symbol substitutions, without local-label
changes. The three provider units replay motion 57, frame 62, six-state66 and
co-emitted phase 73 exact; their existing Reimu parent remains unchanged and
nonexact. No new authored exact credit or source-origin pin change.

The actual source closure is this one update unit. Tracking validation, scoped CI
and diff checks pass. Unrelated input migration and Alice edits remain untouched.

## Action 803 keeps two alpha calls

In the target, sequences 0/1 call the alpha helper at `0x004E18CD` and
sequences 3/4 call it at `0x004E1BD8`. Both jump to the frame-index-1
update at `0x004E19D4`, physically before sequence 2. Sequence 2
continues directly to movement. The preceding build folded both alpha
paths into a single call, then fell through to the frame-index test.

Writing the frame-index-1 update in both switch arms lets VC8 share that
update while retaining both calls. Their full argument-setup sequences now
agree, including when ECX is restored and where the x87 control word is
restored. Both continuations reach the same code before the sequence 2
entry, and sequence 2 bypasses it. A named jump to a single copy of the
update still folds the calls. Exposing the real alpha method body to both
paths preserves the original candidate's bytes and its shared call. The
TH075 update uses a different action 803 sequence and motion path.

The pinned SP1 back end has both call records at `c2.dll:0x10C077B1` in
both builds. At `0x10C077B6`, after `0x10B2C950` returns, the original
candidate has lost the sequences 3/4 call record. The duplicated-update
build retains both records. Read-only traced builds reproduce the
complete ordinary outputs.

Sequence 2 branches to the frame exit's retirement at `0x004E1DA6`
when alpha is below 20. Eligible objects join the subtraction at
`0x004E1D5C`. Targeting the existing retirement from sequence 2
restores the native JB and removes a duplicate return. Updating
`field_374` in place before the byte conversion in both frame-zero
arms also restores the rounding spill and reload before FNSTCW at
`0x004E1B63`. All 387 reachable instructions agree after rebasing.

Changing only the second conversion restores its local instructions
but reverses the scale-add loads in 813, 815, 859 and 901. The two
identical in-place updates retain the earlier code in all four
actions and keep both alpha calls. The complete replay is 29,484 bytes
with 742 relocations and still first differs at `0x004E0D55`.

That earlier 29,212-byte candidate replays all 737 relocations. Its full
SHA256 is `922e46fce0ffbb6b11083754bf33dc3a245f42372cfd0c6d9b5534b75d15874f`.
Using checked members for position, velocity, alpha, action, sequence,
frame index and the float at `+0x374` reproduces those complete bytes.
The target has 47 returns and 17 frame-advance calls. The build has 51
and 15, respectively, so the outer sharing still needs work.

The strict unit now includes all seven tables. The native structural
check closes all 28,985 code bytes, 72 destination words, 200 remap bytes
and three alignment bytes. It recognizes the `PUSH EDI` at `0x004E0D52`
and the `MOV EDI, 1` at `0x004E34B9` and `0x004E7C64` between the switch
CMP and JA. A separate byte change in each table, the last remap byte
and the alignment is rejected at the changed address.

## Frame calls and cross-case registers

The earlier unsigned-byte build had 15 frame-advance call sites compared
with 17 in the target. It reproduced the native 812/815/855 group and
merged 816 into the 803 group and 930 into 920. The pinned `c2.dll` has
all four relevant call records at `0x10C077B1`. After `0x10B2C950` returns to `0x10C077B6`,
the 816 and 930 call records are gone. The traced object reproduces
the prior complete candidate. Reversing the two post-advance tests
splits 920 and 930 at the cost of reversing the native comparison order.
Duplicating the post-call test splits the calls and leaves duplicate code.

Action 920 reads `g_match_identifier` at `0x006FA894`, the same DWORD
written at `0x0047096A` in the exact battle setup. Writing the case groups
in the order 2/3, 1, 0 restores the native stub order and the relative
destinations of the four table words. The zero argument came from EBX
in that build and EBP in the target. This source change by itself
changes only 13 relocated bytes in the stubs and table.

Changing the signed owner byte guard in 816 from `< 2` to `<= 1` gives
the native `CMP BYTE PTR [EDX+0x609], 1` and `JG`. In the unsigned-byte
build it also changed the earlier 811 action with its source held fixed.
VC8 put 2 in EBX and zero
in EDI, matching the target. With branch destinations normalized, all
13 instructions starting at that register setup agree, including the
two stack arguments. A read-only trace shows the assignments already
differ at `c2.dll:0x10C0743C`, before the allocator routine `0x10BDA210`
used in the Object initializer's investigation. They persist at
`0x10C07442`. Checked members for the frame counter, phase state and
lifetime preserve the complete relocated output of the same C++ with
offset accesses.

The earlier decision happens inside `0x10B0CF40`, called from
`0x10C073EE` in the pinned VC8 SP1 `c2.dll`. In both full-root builds
the second zero argument in 811 still refers to the same unallocated
virtual group at `0x10C073E7`. A hardware watchpoint catches the operand
being relinked at `0x10B130F6`; the new group IDs are `0x376` for
`< 2` and `0x3A4` for `<= 1`. Both groups then have 10 uses and
score 3 at `+0x40`.

In `0x10B14B70`, VC8 scans the register class's order and takes the
lowest-cost eligible entry, keeping the first on a tie. The order list
for this class is at `0x10CE59A0`, the group points to the eligible set
through `+0x20`, and the costs are in the DWORD array at `0x10D14F10`.
At `0x10B14D84`, the `< 2` build permits EBX and EBP at cost zero.
The `<= 1` build also permits EDI, which precedes EBX and ties it at
zero. EBP has cost 3100. The store at `0x10B14E2A` records the choice
in the group, and `0x10B17A46` copies the selected register into the
811 operand. EDI starts eligible in both builds. In the `< 2` build,
group `0x3B0` gets EDI first for the value 2 used in 811's sequence and
frame comparisons. The update at `0x10B1555F` clears EDI from the zero
argument's group. That bit survives until selection in the `<= 1`
build. Each traced object reproduces its uninstrumented build after all
737 relocations.

The order reverses when the allocator splits and requeues whole-function
groups. At `0x10B0D22F`, both builds put the unsplit 2 and zero groups
in queue positions 253 and 255, respectively. The insertion routine at
`0x10B11970` orders the linked list by signed priority at `+0x0C`
and then the unsigned key at `+0x44`. The first split request at
`0x10B0D27D` follows an EBX allocation to group `0x1D`, whose defining
instruction is tagged to the right-wall rebound in 816. With `< 2`,
the pruning call at `0x10B0D480` removes EBX, the last eligible
register for both groups. The request includes both constants, and
the 811 fragments reenter one queue. The 2 fragment's priority of −10
puts it ahead of zero at −28. With `<= 1`, the unsplit 2 group still has
EBP after that call, so only zero is split in the first round. The 2
group splits in the third round, after zero has already taken EDI. The
two fragments keep the same priorities across both builds. The next
point to trace is where the `< 2` build removes EBP from the unsplit 2
group.

TH075's Sakuya action 817 and TH105 action 998 use the same owner-action
ranges to position the child.
TH105 reads its own facing and multiplies it by 57 on all three paths
at `0x004E7B72`, `0x004E7BB7` and `0x004E7BF2`. TH075 copies the owner's
facing and uses three different offsets.

## Shared channel fade in action 815

Sequences 2 and 3/4 enter the same fade at `0x004E3999`. A signed time
counter of at least 5 enables the update. The two unsigned byte tests
compare with 10. The normal path subtracts 10 from both channels, and
the saturation path clears them before testing alpha. All three sequences
reach the same 17 instructions with matching encodings after rebasing
the common retire and frame-continuation branches. The two channel
members and the time counter now have compile-time offset checks.
Replacing their offset macros with members is byte-neutral across the
full rebuilt function.

## Fade tail folding in actions 859 and 901

The four native guards load channel 111 and compare it with 10. In
859, sequence 4 branches to `0x004E67C6` and sequences 5/6 branch
to `0x004E688D`. Both branches are short. In 901, sequence 4 branches
back to `0x004E688D` and sequences 5/6 to `0x004E67C6`. Those
branches are near. Each saturation tail clears channel 111 before 110,
then branches to the common retirement block when alpha is below 10.
Otherwise it subtracts 10 from alpha and jumps to the common frame
continuation.

In the earlier source, VC8 SP1's `c2.dll` keeps all four guards through
register allocation and into the late pass at `0x10B2C950`. A hardware
watch on each guard's predecessor links caught the 859 sequence 4 record
being unlinked under `0x10B2E1B0`, then the 901 sequences 5/6 record
under `0x10B306C0`. The two remaining guards are the ones for 859
sequences 5/6 and 901 sequence 4. Both read-only trace builds replay
to the same complete bytes as the untraced control.

In a full-root control, using `>= 10` for the four channel updates,
writing the two shared low-channel destinations explicitly, and
placing the successful alpha update first in one low-channel path
reproduces all four guards and their cross-action destinations. In
that control, each alpha check is already ordered after its 901
guard at `0x10C06F03`, as a compare record with opcode `0x2B6`.
The order survives the call to `0x10BA2E00`, the early branch
simplification loop at `0x10C06F60`, and the remaining passes through
emission. Moving both shared labels to 901 brought one tail back
to 859 but made its channel test branch to another sequence's
subtraction block.

The first native tail has another predecessor. At `0x004E7C52`,
998 sequence 1 jumps to the alpha load at `0x004E67D4`, after both
channel clears. The second alpha load at `0x004E689B` has only the
preceding clears as its incoming path. Following these edges across
the whole root explains why the two identical tails have different
roles.

The current source shares the channel clears between 859 sequence 4
and 901 sequences 5/6, and shares their alpha test with 998 sequence
1. VC8 now keeps all four guards and both low-channel destinations.
The full paths from 859 sequence 5 and 901 sequence 4 agree after
rebasing all branch destinations, for 62 and 60 instructions,
respectively. Sequence 6 uses the same switch entry as 5. The other
pair's clears land in 901 and jump to the alpha test in 998. The
generated test uses JAE to share the subtraction with the second
tail. Recovering the first contiguous native tail means keeping the
998 entry on the alpha test without letting 998 own that test.

On the four-guard build, the channel 111 clear is still in 859 at
`0x10B26CA8`, immediately before `0x10B281E0`. The same `0x28D`
record follows the 901 sequence 5 guard at the return site
`0x10B26CAE`. The 998 alpha check already has its own block at both
points. A hardware watch on the clear block's predecessor link
catches the store at `0x10B282A8`. It changes the predecessor to
the unconditional branch tagged to 901's `goto clear_channels_859_four`.
That block order appears in the final output. A control with the alpha
predicate written success-first in both source locations recovers all 81
reachable instructions from 998. It keeps the first fade tail in
901 and changes the second fade tail's alpha branch to JAE.

Sequence 7 of 901 uses `CMP AL, 10` and `JBE` at `0x004E7301`.
Spelling the alpha test as `<= 10` aligns all 139 reachable
instructions after rebasing control-flow edges. It changes two bytes
in the full replay. Separate comparisons with offset reads and checked
float members at `+0x11C` and `+0x120` produce identical full
outputs, including the parent scale reads. The checked float at
`+0x370` likewise reproduces the complete current output while
replacing the offset accesses used by these scale updates.
Comparing all 200 primary dispatch entries with the previous build
after rebasing puts the instruction changes in 859, 901, and 998.

## Parent updates in actions 859 and 901

The native 901 sequence entries 1, 2 and 3 compute the angle adjustment
on the x87 stack and jump to the angle store in 859 sequences 3, 1
and 2, respectively. The three jumps are at `0x004E708C`,
`0x004E709D` and `0x004E70AE`. The earlier build repeated the
sequence 1 parent copy in 901. Ending the frame directly in both
859 sequence 3 and 901 sequence 1 makes VC8 retain the 859 copy and
recover all three cross-action jumps. Ending the frame in either
arm alone leaves the copy in 901. Sharing an explicit angle temporary
keeps the copy in 901 as well.

The direct exits remove 84 bytes, but the shared parent-copy tail
branches past the native `MOV ECX, ESI`. In that build, the two
sequence-specific call records still have their own receiver moves at
`0x10C073F3`, after register allocation. At `0x10C077B1` both call
records remain and both moves are gone. The ordinary exit from the
901 switch retains its move.

Sending 859 sequence 3 to the exit after the 901 sequence switch and
letting 901 sequence 1 break to that same exit gives the two paths one
source frame call. The shared parent copy now branches to the ECX
reload before the frame call. Moving the source exit to 859 instead
places the shared parent copy in 901. The selected parent repair
changes one byte of the branch displacement across the full replay.
All three parent paths in 901 and their partners in 859 now agree
through the frame exit after rebasing. The checked float member at
`+0x12C` still accounts for the angle stores.

## Inclusive alpha guards in 800, 801, 812 and 813

The six native ten-step fades use `CMP AL, 10` and `JBE` at
`0x004E0ED1`, `0x004E1092`, `0x004E1325`, `0x004E309C`,
`0x004E33B0` and `0x004E342B`. Writing the inclusive comparison
reproduces the six instruction pairs and changes twelve bytes in the
full replay. The complete reachable paths in 800, 801 and 812 agree
after rebasing, with 265, 180 and 194 instructions respectively.

## Signed bounds in action 813

Within the `sequence <= 5` path, the native add branches compare
the three signed fields to BX holding 5. The subtract branches
compare them to AX holding 4. Writing the bounds as `< 5` and
`> 4` puts the load of 4 after the first add branch, at the
position corresponding to `0x004E3271`. Either change alone
leaves a difference in the placement or use of EAX.

All 170 reachable instructions in 813 now agree after rebasing.
This change leaves the other primary dispatch entries equivalent
under the same comparison. The signed short members at
`+0x364..+0x36C` and float members at `+0x124` and `+0x128`
also appear in the Sakuya action initializer. Compile-time checks
fix their offsets in the update view. The typed and offset-based
builds with the corrected bounds reproduce the same full output.

## Frame cutoff and fade in action 815

The native sequence 0 frame cutoff compares with DI holding 1 at
`0x004E34EF`. The inclusive source comparison restores that
instruction and its signed JG. The two arms next differ in the
x87 load order at `0x004E3502` and `0x004E37ED`.

Four more ten-step alpha guards compare with 10 and branch on
JBE in the target. They are at `0x004E162B`, `0x004E2431`,
`0x004E3805` and `0x004E42EF` in 802, 805, 815 and 817.
The first, second and fourth rebuild with their native comparisons.
The 815 frame 2/3 guard now has its own branch, while the later
saturation tail keeps its separate comparison. VC8 emits JA to
their shared subtraction and leaves retirement in the fallthrough
path. A goto to the local retirement block reproduces those same
bytes. Using the retirement block in 803 changes frame-call ownership.

## Action 810 comparisons and constant placement in later actions

The native 810 entry uses the signed sequence cutoff `<= 1`.
Its three owner-action tests exclude values below 500 and above
503, and the sequence checks in those blocks compare with 2.
The first block uses the object's own sequence. The two orbit
blocks use the owner's sequence. The candidate still lacks the
native `MOV EBX, 2` between the first compare and branch.

Changing only the 810 comparisons moves the load of 2 to the
native positions in 857, 859 sequence 0 and 901 sequence 0. The
same control assigns the value 3 in 818 to EBX as in the target
and moves an EBP load earlier in 805, where the prefix still differs.
With those register choices, the inclusive alpha tests are the
remaining differences in the reachable paths of 818, 857, and
the two sequence 0 paths. Their native compares are at
`0x004E4697`, `0x004E5B21`, `0x004E5C5E`, `0x004E650B` and
`0x004E6FFB`. The selected rebuild matches those paths after
rebasing, with 308, 237, 169 and 173 instructions respectively.
The 859/901 parent-copy paths and all 17 frame-call owner groups
remain aligned.

The ground-bounce code in 811, 856, 858 and 900 has the same
source expression for the vertical sum. The target loads Y and
adds the rounded speed in ST(1) on all four paths. The current
build does so in 858. In the other three paths it duplicates
the speed on the x87 stack and adds Y from memory. Swapping the
addition operands or capturing Y after the speed store in 900
retains the memory add. Capturing Y before that store restores
the add from ST(1) with an extra spill and reload.

At `0x10C06F03` the first of the two moves feeding the sum in
858 already reads Y from object memory. In 900 it reads the rounded
speed temporary. A hardware watch on the first operand pointer
catches both assignments at `0x10BF388B` under the early pass
called at `0x10C06D34` (`0x10BAF600`). Later, across the call
at `0x10C065FF`, VC8 removes the second speed load in 858 and
folds the second Y load into the add in 900. All three read-only
trace builds replay to the same bytes as the ordinary control.

The watchpoint also reaches the operand materialization call at
`c2.dll:0x10BB6149` in both actions. The caller's operand at
`[ESP+0x14]` has already diverged there. It is the object-memory
descriptor (`0x27C`) in 858 and the speed temporary descriptor
(`0x27A`) in 900. Changing the position access back to an offset
or a float reference leaves the full build identical. Forcing the
landing sum into a float local changes the rounding and adds a spill.
Keeping the rounded speed in an explicit float local changes the
scratch slot and keeps the memory add. Omitting action 858 in a
scratch build also keeps the 900 memory add.
The 384 reachable instructions in action 900 pair one to one after
rebasing. Only the load and add at `0x004E6D83` and `0x004E6D89`
have different encodings once the pairing allows those two operations.

### The entry Y bounds affect the landing sum

The two moves are still in speed-first order on entry to the
`0x10C06D34` call. On return at `0x10C06D39`, 858 has moved the
Y load ahead of the speed load. A watch on the Y operand's flags word
at `+0x10` records `0x10B2692A` copying `0x1020231` from a child
definition in 858. In 900, `0x10B26962` stores `0x10008` from
`0x10BB6670`. The traces produce the same relocated bytes as the
ordinary build.

Keeping the state check and both X bounds but omitting both Y bounds
in a scratch build changes the later 900 landing sum to the native
`FLD [ESI+0xF0]; FADD ST(1)`. Leaving either Y bound in the entry
guard preserves the memory add. The state check, X limits and later
ceiling and floor rebounds can each be removed without fixing the
memory add when the entry Y limits remain. Splitting the guard or
changing the float literal spelling keeps the full output identical.
A local Y copy introduces a spill in the bounds check and still
leaves the memory add. The native entry performs both Y comparisons,
so the remaining question is why those earlier loads yield different
operand definitions in the original compiler context.

Removing the complete entry guard also changes the 900 trace to the
858 path at `0x10B2692A`. Both copy `0x1020231` from an address
definition with opcode `0x2A5` in that control. The ordinary build
of the same scratch source reproduces the traced object's bytes.

## Action 850 heading and typed receiver fields

Native action 850 reloads the parameter pointer at `0x004E4BA3`
after the heading call at `0x004E4B9E`. The former source captured
that pointer before the call and kept it in EDI. Computing
the heading first gives the target's EAX load and the rounded float
used for both stores. The first child reloads the heading written to
the parameter array. All 235 instructions reachable from action 850
now agree after rebasing branches, with the same calls and shared
destinations. The other primary action paths retain their previous
code and edges.

The receiver now names the signed facing byte at `+0x104`, the target
pointer at `+0x170`, and the update delay word at `+0x186`. The
motion expressions sign-extend facing and the spawn calls still
zero-extend it. The owner position and action reads use existing
checked members. Separate VC8 controls for the facing, target and
owner changes reproduced the complete previous candidate byte for byte.

The update view also exposes gravity at `+0x100` and the spawn byte at
`+0x33C`, which use float and byte accesses respectively in 999 and
810. The typed control reproduces the complete preceding build. Action
999's landing calculation keeps its QWORD sum across the surface query.

## Action 853 retirement is shared with action 805 in the rebuild

The target routes seven exits from sequences 2, 4, 5, 6 and 7 to the
decrement at `0x004E53AD`, which adds EDI holding -1. The frame call
can fall through to the same decrement. The preceding build used the
same register for its 805 retirement, so all seven branches jumped to
that earlier copy. The native 805 retirement at `0x004E24E2` uses EBP.

The sequence 7 alpha cutoff already used the native short JBE to the
local frame retirement. The sequence 2 timeout and both parent checks
in sequences 4 and 5 now reach that retirement too. Only sequence 6's
alpha guard still reaches the 805 copy. All 298 native instructions
pair after rebasing, with eight extra instructions from that copy.
The five branch displacements account for all 20 changed bytes.
All 17 frame-call sites retain their owners.

Routing all six earlier branches to the same source label removes the
853 frame call and its EDI setup. An explicit 805 alpha exit into 804
with a local alpha byte instead restores all seven 853 branches and
keeps the 17 frame calls. It also changes the register and tail shape
in 816's last two parent exits. The selected six local branches preserve
816's previous instruction encodings and change only 853's destinations.

In the selected build, the child-spawn decrement and the frame decrement
both resolve to group `0x361`, which gets EDI. In the all-jump control,
the first split of the whole-function -1 group follows EBX assignment
to the 901 phase guard's constant 5. Both 853 uses enter group `0x360`.
The next relevant split at `0x10B0D27D` follows group `0x381`, whose
constant-1 definition is tagged to the child-spawn loop. The child
decrement briefly resolves to `0x1E`; the frame lookup already has an
empty intersection. Both decrements become immediate -1 by the end
of the split. `0x10C073F3` still has the frame call. It survives until
`0x10C077B1` and disappears when `0x10B2C950` returns at `0x10C077B6`.
The traced objects reproduce both ordinary builds in full.
Changing the child loop to a float `for` loop or narrowing the spawn
facing or layer formal leaves the all-jump replay identical.

The selected source spells out the action's child packet, homing update
and sequence 6 lifetime check. All 29,480 relocated bytes and all 742
relocation records agree with the previous source.

At `c2.dll:0x10C077B1` the 853 alpha branches still have separate
label references. After `0x10B2C950` returns to `0x10C077B6`, both
reference the same label (`+0x18` in the `0x284` operand). In a
control that redirects the 816 parent-frame exit through the 805
decrement, 853's source stays identical and all seven branches use
the 853 frame retirement. That control adds a second -1 load in
816 and sends its parent-frame exit to the 803 retirement.
Both read-only traces reproduced the ordinary builds.

Changing the 805 starting frame test from `< 2` to `<= 1` also
restores all 298 instructions and their sharing in 853. It gives the
805 decrement EBX and changes the native frame compare. Explicit
casts, separate guards and reordered operands that retain the bound
of 2 do not remove the 805 register group for that literal.

### The 805 literal groups before folding

The frame CMP still has an encoding operand of kind `0x275` with value
2 at `0x10C06590`. The early pass at `0x10C26030` visits its operands.
`0x10B56700` interns constants by kind and value, then builds a symbolic
operand. The write at `0x10BF2BF7` removes the literal from the CMP's
first operand chain, and the replacement is already linked at
`0x10C073E7`, before register allocation begins.

The allocator relinks that symbolic operand to the group at
`0x10B130F6`. It writes EBP to the group at `0x10B14E2A` and writes
the 16-bit BP descriptor into the operand at `0x10B17A46`. In the
`<= 1` control, the same stores select EBX and BX for the separate
three-use group for 1.

The final sequence test in 804 is a control for the immediate form.
It starts as the same immediate 2 and shares 805's symbolic group at
`0x10C073E7`. The allocator moves the two uses into different groups.
For 804, `0x10B599B0` restores the literal while splitting uses,
before physical register selection. Its call at `0x10B12FDD` follows
the failed intersection of two sparse sets at `0x10B12F4D`.

Before the 853 exit edit, the lookup associated with `0x10B130F6`
returns `0x39A` for 804 and `0x3A1` for 805. Both IDs are in the
original group for 2. The 804 block's entry set at `+0x48` is
`{0x3, 0x38, 0x39A}`. When `0x10B599B0` restores the immediate,
the entry set is `{0x38, 0x363}` and the two lookup input sets are
empty. The 805 block's entry set is `{0x38, 0x3A1}` and its lookup
keeps the single matching ID. The two traced builds reproduce the
complete ordinary object after relocation replay.

At `c2.dll:0x10B14D84`, the `< 2` build gives the group containing
`select_sequence(2)` and the cutoff five uses and score 2. The `<= 1` control
gives it four uses and score 1. Both select EBP at cost zero, with
EBX eligible at cost 6800. The group for the second spawn's -1
argument has five uses in both builds. It has only EDI available
in the baseline and only EBX in the control. The assignment at
`0x10B14E2A` records those choices. Both ordinary builds agree with
their traced versions after complete relocation replay.

The frame compare already has BP in its encoding operand chain at
`0x10C073F3`, after `0x10B0CF40` returns and before `0x10BDA210`
and tail folding. For this CMP the encoder loads the first operand
from `CMP+0x28` and follows its link at `0x10C210F1`. The first
linked descriptor points to BP (`0x10D0A4B0`) in the `< 2` build
and to BX (`0x10D0A3F0`) in the `<= 1` control. The bookkeeping
record at `CMP+0x2C` survives with its literal descriptor in both
builds. The two paths emit `66 39 AE 40 01 00 00` and
`66 39 9E 40 01 00 00` at the return to `0x10C56EC2`. Both
traces run without `/FAcs`. The target uses immediate 2 in all five
positions and loads EBP with -1 before the first sequence body.

Reading the cutoff through a local or an inlined helper keeps the
same full candidate. `frame + 1 <= 2` still loads EBP with 2,
and `frame - 1 < 1` introduces a widened comparison and still
keeps the other six 853 branches on the 805 retirement tail.

Putting the phase reset before the alternate sequence advance in
805 sequence 1 restores the local signed JLE and the native virtual
call placement. In the same full build, 813, 815, 859 and 901 switch
their scale-add load order. Giving the phase test a local name,
changing the earlier 803 alpha assignments, and swapping the scale
sum's operands all retain that cross-case difference. The selected
source keeps the preceding 805 branch shape.

Writing out the motion step, bounds, and lifetime exits in 805
preserves the full relocated output.
A shared `const int` spawn layer and an explicit jump to the fade
test also reproduce the same bytes. Splitting the opening guard
through an owner-action local or flattening the phase reset perturbs
the scale-add operand order in 813, 815, 859 and 901.

## A typed helper for the 810 orbit

The four orbit paths use `advance_orbit()` with the existing
receiver fields. VC8 emits an out-of-line call with ordinary
`inline`. The forced-inline definition reproduces the complete
29,480-byte candidate and the locations, kinds and resolved targets
of all 742 relocations. Twenty private labels get new names during
inlining. The separate conversion of the random macro to a forced-inline
function changes the emitted bytes.

## Fighter fields used by the owner

Actions 816, 818, 900, 920 and 930 use the existing `Fighter` layout
for five owner reads through checked signed fields at `+0x174`,
`+0x48C` and `+0x609`. The full relocated candidate is equal before
and after the change, including the switch tables and remap.

## Actions 920 and 930 before frame advance

In 920 the signed owner timer at `+0x7A4` branches to the oriented-motion
block on `JLE` at `0x004E7554`. The positive-first source puts that block
after the positive path, as in the target. Both action 920 and 930 fade
checks now emit `CMP AL, 10` and `JBE`. In 930, separate source arms for
sequences 0 and 1 produce the target's three successive SUB tests.
VC8 merges the arms into the same zero push and shared
`advance_state_six_counter_conditional` call. Grouping the two labels on
one source statement emits a range test instead.

The 187 instructions in 930 through the bounds checks agreed after
rebasing branches and calls. The branches reach the same local blocks
and shared retire tail, and the calls retain their target addresses.
That build still jumped to 920's frame call where the target calls
directly. In 920 the zero value stayed in EBX and 30 in EBP. The target
loads 30 into EBX before the contact branch and uses it for all four
random calls in 920.

At `0x10C073E7`, the four random arguments and both timer tests in
920 refer to the same whole-function group for 30. The first split
of this group follows an EBX allocation to a range tagged to 858's
secondary-animation guard. The six 920 uses still share a fragment.
A later split request tagged to 853's child-spawn loop separates the
two contact arguments from the timer and remaining random arguments.
By `0x10C073F3`, the contact arguments are immediate 30 and the rest
use BP or EBP.

The first split request from 816's right-wall rebound puts the zero
operands for 920 and 930 into distinct fragments. Both get BX for
their frame-counter tests. At `0x10C077B1`, the two calls are still
present and their comparisons already use the same register. Only
the 920 call remains at `0x10C077B6`.

Omitting 816 in a scratch build gives 920 EBP for zero and one EBX
range for all four random calls. The frame-counter tests use BP in
920 and BX in 930 before the late pass, and both calls survive it.
Omitting 901 or 930 leaves the 920 constant placement unchanged.
Omitting only the right-wall arm or the frame call in 816 also leaves
the 920 choices unchanged. The traced objects replay their corresponding
ordinary objects in full.

## Action 854 saturation and typed object links

Action 854 compares the alpha byte with 220 at `0x004E53E8`. The
below-220 path adds 25 and the other path writes 255 in a shared tail.
Writing the non-saturating branch first reproduces all 44 reachable
instructions after rebasing branches, including the earlier shared
stores and return code.

The receiver view now has checked members for the parameter buffer at
`+0x340`, the word at `+0x344`, the fighter owner at `+0x348` and the
parent object at `+0x34C`. The Sakuya initializer uses the same
parameter buffer and word. The roster spawn code publishes the owner
and parent at these offsets. The update reads the parent's checked
position, velocity, frame index and alpha directly. The full relocated
output of the typed view agrees with the previous offset form.

## Signed phase byte restores frame-call ownership

The byte at `+0x184` is tested with signed comparisons in 816.
The unsigned decrement carrier produced one shared load of FF into BL
for the four wall rebounds. The signed member restores the target's
four `ADD BYTE PTR [ESI+0x184], 0xFF` instructions and the `OR EBP, -1`
used by the separate frame tail. Omitting just the four decrements
isolated their effect on 920 and 930. Explicit unsigned subtraction,
addition of FF and splitting the phase reset into two arms all replayed
the unsigned baseline. Changing just the four decrement lvalues to
signed in a control reproduced the complete selected output.

The read-only VC8 SP1 trace sees the byte-add constant operand change
from descriptor bits `0x20010001` to `0x10010001` at offset `+8` before
`0x10B0CF40`. At `0x10B14D84`, the signed build keeps all six uses of
30 in one group and selects EBX at cost zero. The 920 zero group then
has only EBP available. The 930 zero group has EBX and EBP at cost zero
and takes EBX. In the unsigned build, both zero groups chose EBX and
the timer fragment of 30 took EBP. Both traced builds replay their
corresponding ordinary objects in full.

The signed build reproduces all 17 physical frame-call sites with
their target action ownership. After rebasing calls and branches,
920 and 930 agree for all 288 and 221 reachable instructions,
respectively. Action 816 agrees for all 409 target instructions,
with its two identical retirement tails at `0x004E213C` and
`0x004E24E2` sharing one physical copy in the candidate. The 811
constant setup now differs again. VC8 puts 2 in EDI and zero in EBX.
Reverting the 816 owner cutoff to `< 2` leaves these registers swapped
and loses the native compare encoding.

The current envelope is 29,492 bytes with 742 relocations, SHA256
`cc919178c9c15f2cde245c0486a12d50a1a1a075aba053291f4403e264d2a40d`.
The target envelope is 29,476 bytes. The first difference is at the
primary default branch, `0x004E0D55`. Both 803 alpha paths and the
200-byte primary remap still agree.
