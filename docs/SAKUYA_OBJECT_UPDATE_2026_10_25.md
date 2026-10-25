# SakuyaObject complete update: 2026-10-25

`SakuyaObject_update_action_state @ 0x004E0D30` now has a manual complete-body
source hypothesis. It is **not exact**. Formal and independent cold ordinary
VC8 builds emit29408 bytes, SHA256
`3e0aa7a9293563dd879d253047218a3cf9140b6fce7bfb9b8ce30c515c35bc9c`,
against29476 target bytes. Full unmasked comparison reports27397 differing
bytes, first+37 in the primary default-branch destination. This is not a small
localized residual or a partial exact claim. Continue this bounded root from
the concrete frame, scalar-precision and call-sharing evidence below.

## Observed target and complete boundary

The executable is original Japanese1.06a, SHA256
`56350024879199861579c11b0e1c67b9590e10a8d40cd5996b109deec9afca7e`.
IDA preflight rejects the GUI's different executable. All analysis reads use
the hash-attested PE or the independently attested optional database below.
The raw audit is reproducible without an analysis GUI:

```sh
taskset -c 0 nice -n 10 scripts/repo-python scripts/audit-sakuya-object-update.py --target-only
```

RTTI-backed roster evidence and raw primary slot28 cell6C48B4 bind SakuyaObject
vtable6C488C to4E0D30. Its separate slot3C cell6C48C8 points to4E8060, the
previously reviewed initializer. No initializer implementation is changed here.

The callable range is `[4E0D30,4E7E69)`,28985 bytes, SHA256
`592df4424de962d219caa2e73d62ab420ed0d0438ba009b20b94f4b9df51ca94`.
Raw traversal closes all6774 decoded instructions/all28985 bytes,47 RET0s,
232 direct calls to20 entries and48 indirect calls. Every branch and table
destination stays within the callable range. There is no external direct tail
jump or unreviewed unreachable callable instruction.

The prologue aligns ESP to eight bytes, allocates0xD0 bytes, saves EBX/EBP/ESI/
EDI below that frame and retains ECX in ESI. No GS/EH frame is present. The
source uses a pointer-only virtual view and typed offsets; never instantiate
or embed this as a recovered complete allocation. Original nominal return
type, full class layout and original translation unit remain unknown.

Complete `[4E0D30,4E8054)` is29476 bytes, SHA256
`453a7abb8a48642f5852078059893f8611d26b07c77ae67d8747c4fadcd42ce3`.
Its491 noncallable bytes partition as:

| Address | Contents |
| --- | --- |
| 4E7E69 | three-byte LEA ECX,[ECX] alignment |
| 4E7E6C |33 DWORD destinations |
| 4E7EF0 |200-byte remap for actions800..999 |
| 4E7FB8 |5 DWORD destinations |
| 4E7FCC |5 DWORD destinations |
| 4E7FE0 |7 DWORD destinations |
| 4E7FFC |9 DWORD destinations |
| 4E8020 |4 DWORD destinations |
| 4E8030 |9 DWORD destinations |

All72 destination DWORDs/288 bytes and200 remap bytes participate. Twelve INT3
bytes separate this payload from4E8060; none is included. Metadata/alignment
receive no callable-byte credit.

The32 explicit primary actions are800..805,810..813,815..818,849..859,
900,901,920,930,980,998,999. All other remap entries reach the default frame
continuation. Nested state switches belong to803,815,859,901 and999;920 also
switches on the existing match-identifier global.

## Optional analysis hypothesis and manual source

A single direct Ghidra headless process ran readonly/noanalysis, CPU0/nice10,
one CPU and384MiB heap. It attested the imported executable SHA256, PE image
base/entry, language/compiler and all mapped section bytes before inspecting
this root. The temporary bounded body and declaration-only callee ABI views
were read back. The root entry was removed, the transaction rolled back, and
root metadata read back again. All nine primary project-file hashes agree
before/after; the process terminated0 with its attestation sentinel.

The private3119-line decompiler output is a control-flow/type hypothesis, not
selected source. The manually written source expresses32 complete actions with
numeric states, typed offset reads/writes, consumed local parameter packets and
real declaration-only calls. Target instructions determine widths, physical
edges, helper contracts, scalar rounding and publication order. No decompiler
temporary-name translation or copied output is used as the implementation.

Raw facts, disassembly, decompiler hypothesis, project hash receipts and trial
reports live under `build/exact-first-sakuya-object-update-20261025/`; private
source controls and the readonly driver are under the corresponding `.analysis/`
directory. The source hypothesis does not assert full execution equivalence.

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
  a conditional2^32 addition is observed. The unsigned `roll(16)-8` conversion
  is preserved too. It must not be replaced with a signed random range.
- The800-family speed products visibly store/reload a float before adding
  the wider5/6 constants. Twenty-one corresponding random-speed expressions
  now retain that consumed single-precision boundary. Float-promoted qword
  operands such as0.01/0.1/0.05 use the target's extended float values.
- The805 and810 trigonometric consumers use the full ST0 double result.
  Raw810 spills the captured facing value as a qword across the trig call.
  Its duplicated owner-valid/owner-invalid orbit paths remain independent
  call sites; all six sine and six cosine calls survive. Captured owner
  pointers and vertical coordinates respect their observed call epochs.
- The859/901 distance paths capture the radius-times90 product as a float
  before calls, retain the first squared result in a qword across the second
  square call, then round the sum for the square-root argument. These real
  consumed wider values restore ordinary eight-byte stack alignment.
- Six real three-float spawn packets occur in802,804,805 twice,817 and818.
  Giving each its observed independent local lifetime replaces one shared
 16-byte packet with six12-byte packets: the56-byte difference explains the
  measured frame change0x98 to0xD0 exactly. Each packet is passed to a real
  parented/owned spawn. The remaining packets also have real call consumers.
- Several bounds paths use ordered conjunction rejection; other paths use
  explicit outside comparisons. These differ for unordered inputs and remain
  separate. The803 transparency conversion saves the x87 control word, sets
  truncation bits0xC00, executes FISTP and restores the control word. Source
  byte conversions and captured scalar values retain this contract.
- 849 performs two horizontal updates and two quarter-scaled vertical updates
  in its phase2 path. They remain separate operations.998 performs its three
  distinct parent-action position checks.999 retains independent parent
  coordinate publication, repeated stage-height calls and post-frame velocity/
  gravity publications. These repeated operations are not deduplicated.

Four separately declared float cells6FBD1C/20/24/28 are provisional boundary
views. Their address aliases attest loader-zero storage, not runtime constant
values or a complete global owner. The existing6FA894 match-identifier binding
is reused unchanged.

## Early whole-function comparison and controls

Every successful comparison below replays the complete emitted symbol and all
relocations. No code, jump table, remap or alignment bytes are masked.

| Complete source/control | Full bytes | SHA256 prefix | Evidence/result |
| --- | ---: | --- | --- |
| First manual body |—|—|ordinary random conversion helper remained out of line; unsupported target edge stopped replay|
| Expand the real random conversion expression |29312|f7a99fa9|first complete canonical comparison; unaligned0x8C frame,50 RETs/16 frame calls|
| Preserve observed double captures/results |29200|29d991de|eight-byte alignment restored;0x98 frame,52 RETs/17 frame calls|
| Restore six independently consumed packets |29264|ba67850d|target0xD0 frame restored exactly|
| Restore random-product float boundaries |29408|f82af9da|21 rounded products retained; first+37 remains|
| Capture803 alpha before byte conversion |29408|3e0aa7a9|selected complete source; scalar allocation changes, but alpha calls remain2/3|

All seven destination-table dimensions33/5/5/7/9/4/9 and the full200-byte primary
remap agree. All48 virtual calls and19 of20 direct-callee counts agree. The
selected source has52 RETs against47 and two secondary-alpha calls against
three. There is no byte-neutral repeat grid, compiler-profile change, behavior
matrix, assembly, copied byte array, padding, inert local or fake return.

All738 selected section relocations replay. Formal and independent cold
objects reproduce the same29408-byte canonical hash and27397 differences.
The physical comparison remains broadly different; matching frame/counts are
diagnostics only. No `matches.csv` row or exact-byte credit is added.

A generated-COFF-only negative changes the final default-remap entry for source
action997, at generated address4E7F71/+29249, from valid index32 to valid0.
That byte originally agreed with the aligned target byte. Parsing succeeds,
but full differences rise to27398, SHA256
`e424044cb987942ef1e2e8524a110d3d13ac4222fb3e4b59e8e94c70c701370b`.
The canonical PE and selected object are unchanged. Five synthetic controls
exercise all seven tables/200 indices, an invalid final remap index, a metadata
destination, a truncated final table and an external CFG tail.

## Reproduction and continuation

Use locked repository Python and serial CPU0/nice10 jobs. The retained nonexact
comparison commands intentionally return1:

```sh
taskset -c 0 nice -n 10 scripts/repo-python scripts/build.py --unit exact-first-sakuya-object-update --compare --json
taskset -c 0 nice -n 10 scripts/repo-python scripts/audit-sakuya-object-update.py
TH105_ENABLE_GS=0 TH105_FP_MODE=default TH105_INLINE_MODE=default \
  taskset -c 0 nice -n 10 scripts/compile-unit.sh src/characters/SakuyaObjectUpdate.cpp build/sakuya-object-update-cold.obj
taskset -c 0 nice -n 10 scripts/repo-python scripts/audit-sakuya-object-update.py --object build/sakuya-object-update-cold.obj
```

Only the local source/interface/unit,79 exclusively named literal aliases and
four boundary-address aliases are added. No accepted unit references these
aliases. Previous source/layout/header/compiler/bindings remain unchanged.
Accepted graph remains524 units/1412 functions/381108 callable authored bytes;
the prior Remilia checkpoint is still the latest aggregate cold receipt. No
new aggregate cold replay is claimed. Ledger validation records mapped1578,
source-present1559 and598 configured units/1566 functions;1484 floating target
references pass.

Continue4E0D30. Inspect the803 secondary-alpha call sharing and the five excess
returns before another whole-body trial. The first800 path also has an observed
inclusive phase comparison against2 and EBX-held5; source currently compares
against3 and uses an immediate5. Test only evidence-backed source epochs and
relation forms, without introducing a constant local to force a register.
Preserve complete comparisons and stop any repeated neutral controls. Remaining
unknowns include full execution equivalence, precise source expression/return
sharing, original nominal owner/return type and original TU/compiler context.
