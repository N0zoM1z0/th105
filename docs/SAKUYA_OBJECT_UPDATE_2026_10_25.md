# SakuyaObject complete update: 2026-10-25

`SakuyaObject_update_action_state @ 0x004E0D30` now has a manual complete-body
source hypothesis. The current comparison first differs at `0x004E0D55`,
the primary default-branch destination. The selected source restores action
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

The selected 29,212-byte candidate replays all 737 relocations. Its full
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

The selected build has 15 frame-advance call sites compared with 17 in
the target. The native 812/815/855 group already uses one physical call
in the current build. The two remaining merges are 816 into the 803
group and 930 into 920. The pinned `c2.dll` has all four relevant call
records at `0x10C077B1`. After `0x10B2C950` returns to `0x10C077B6`,
the 816 and 930 call records are gone. The traced object reproduces
the prior complete candidate. Reversing the two post-advance tests
splits 920 and 930 at the cost of reversing the native comparison order.
Duplicating the post-call test splits the calls and leaves duplicate code.

Action 920 reads `g_match_identifier` at `0x006FA894`, the same DWORD
written at `0x0047096A` in the exact battle setup. Writing the case groups
in the order 2/3, 1, 0 restores the native stub order and the relative
destinations of the four table words. The zero argument still comes from
EBX in the build and EBP in the target. This source change by itself
changes only 13 relocated bytes in the stubs and table.

Changing the signed owner byte guard in 816 from `< 2` to `<= 1` gives
the native `CMP BYTE PTR [EDX+0x609], 1` and `JG`. It also changes the
earlier 811 action with its source held fixed. VC8 puts 2 in EBX and zero
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

Actions 859 and 901 also fade these fields. The target has four guards.
The low-channel branch from 901 sequence 4 goes to the 859 sequence 5/6
tail, and 901 sequence 5/6 goes to the 859 sequence 4 tail. A scratch
build with both destinations written explicitly still merges the two
901 paths in VC8. Keep those tails in the full-root allocation and
sharing investigation.

## Actions 920 and 930 before frame advance

In 920 the signed owner timer at `+0x7A4` branches to the oriented-motion
block on `JLE` at `0x004E7554`. The positive-first source puts that block
after the positive path, as in the target. Both action 920 and 930 fade
checks now emit `CMP AL, 10` and `JBE`. In 930, separate source arms for
sequences 0 and 1 produce the target's three successive SUB tests.
VC8 merges the arms into the same zero push and shared
`advance_state_six_counter_conditional` call. Grouping the two labels on
one source statement emits a range test instead.

The 187 instructions in 930 through the bounds checks now agree after
rebasing branches and calls. The branches reach the same local blocks
and shared retire tail, and the calls retain their target addresses.
The candidate still jumps to 920's frame call where the target calls
directly. In 920 the zero value stays in EBX and 30 in EBP, with the
opposite register roles in the target. The target loads 30 before the
contact branch and uses it for all four random calls in 920.

The current envelope is 29,192 bytes with 737 relocations, SHA256
`a27d44ed13dcc44e965567ad59174e6655b7afe3a94bf31be99f6025df4f70a2`.
The target envelope is 29,476 bytes. The first difference is at the
primary default branch, `0x004E0D55`. Both 803 alpha paths and the
200-byte primary remap still agree.
