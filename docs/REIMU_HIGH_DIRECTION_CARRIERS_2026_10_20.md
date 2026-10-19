# Reimu high-action direction carriers and next-sequence ownership

## Target and source scope

The authored root remains `Reimu_dispatch_action_state_vslot28 @478FA0`,
callable `[478FA0,48CE2E)`,81550 bytes, SHA256
`dbf6f375a809fea91cbbccf0f8cff2196f40cba11458c98e475a290b623053e6`.
Only original Japanese TH10.5 v1.06a executable SHA256
`56350024879199861579c11b0e1c67b9590e10a8d40cd5996b109deec9afca7e`
is used. The root stays unclassified/declaration-only, with no
`implemented.csv` or `matches.csv` row and no exact credit.

This checkpoint extends the selected600/601/602 facing-value hypothesis to
604/605/606/608/650/651/658. The four new source declarations are confined to
the effect115 guards in `ReimuActionStateHighEntryCases.hpp`,
`ReimuActionStateHighMiddleCases.hpp` and
`ReimuActionStateHighLateCases.hpp`. Each stores the unsigned facing byte
in a used int, consumes its signed-byte interpretation for X, and supplies
the unsigned value as direction. Capture remains after the actual event23
call. Layouts, field widths, helper definitions/prototypes, compiler flags
and relocation bindings are unchanged.

## Observed target instructions and inferred carrier

**Observed:** all ten actions600/601/602/604/605/606/608/650/651/658 reuse
`MOVZX EAX,BYTE104` for the direction argument and interpret AL as signed
for the X calculation. For example605 uses MOVZX488CA3, PUSH EAX488CB2,
MOVSX EAX,AL488CB7, then LEA/subtraction for multiplication by7.
608 and658 multiply the signed value by24, and650/651 subtract twice the
signed value from X. The two byte interpretations have separate meanings.

**Inferred:** a local int in0..255 exposes this wide reuse to VC8 without
altering the actual signed arithmetic. It is not a unique reconstruction of
the original local declaration. The previous byte-valued source required an
extra conversion in these seven argument preparations.

Each selected scalar preparation now agrees with the complete branchless
target window, from after event23 until the next CALL or unconditional JMP.
All registers, widths, stack displacements and canonical literal addresses
are retained. The JMP itself is excluded and its destination recorded; no
edge encoding is silently normalized into equality.

| Action | Target / selected instruction count |
| --- | --- |
|600,601|19 /19 each|
|602|16 /16|
|604,605,606|20 /20 each|
|608,658|22 /22 each|
|650,651|16 /16 each|

The earlier602 report used a shorter pre-tail window for direct-call cases;
the counts above extend those windows to the actual CALL boundary. This
does not add unique coverage or canonical partial-match credit.

Direct read-only Ghidra independently re-attests imported/raw executable
identity, base/entry, x86/windows analysis target, full mapped text, complete
root hash and vtable cell6C4154->478FA0. It decodes all ten preparation
windows plus next-sequence tails47D7BE and4852F6. All nine primary database
hashes remain unchanged; the temporary project alias is removed. The failed
IDA preflight identifies another executable and is not used semantically.

## Controlled combinations and complete physical ownership

A fresh ordinary baseline reproduces the preceding complete78043bc1 payload
and1224 equal physical membership/multiplicity checks. Nine private controls
vary the carrier property; all undergo both complete root auditors.

| Actions changed | Canonical prefix | Bytes / callable prefix | Source instructions | Previous checks lost / new checks |
| --- | --- | --- | --- | --- |
|605 only|`518b6d64`|82824 /81452|20251|0 /0|
|608 only|`48607980`|82824 /81452|20251|0 /0|
|651 only|`f112613a`|82792 /81420|20234|10 /0|
|658 only|`555e22ae`|82824 /81452|20251|0 /0|
|604/606|`192f29db`|82792 /81420|20233|10 /0|
|604/605/606|`7863a6b5`|82792 /81420|20232|10 /0|
|608/658|`e15a2107`|82824 /81452|20250|0 /0|
|604/605/606/608/651/658|`82c29cde`|82808 /81436|20245|0 /0|
|All seven, selected|`bb2b2a43`|82808 /81436|20245|0 /6|

Every frame remains570h. The smaller rejected controls lose the correct
197/658 and198/608 landing pairs across height, motion reset, slotC, RET
and all-indirect domains. The selected combination preserves all1224 prior
checks and adds six, for1230: the two large slot14 groups, their RET groups
and corresponding all-indirect groups. Thus all35 physical slot14 CALLs
now have the target's complete action membership/multiplicity partition.
The nineteen and eighteen incoming target branches to the two main tails
remain distinct. The root discards the actual unsigned-byte return of the
accepted138-byte45C220 sequence helper.

The first tail at47D7C5 has actions
71/72/308/402/530/545/546/600/601/602/604/606/619/651/658/730/740.
The second at4852FD has
74/145/304/410/414/416/520/521/522/523/525/526/531/605/608/609/610/650.
In particular605/608 now associate with the second tail and651/658 with
the first. A failing650/651-only carrier control from the preceding phase
did not rule out this wider, consistent family treatment. Smaller code or
fewer instructions alone would not justify selecting a control.

## Current ordinary result and unresolved questions

| Artifact | SHA256 / value |
| --- | --- |
| Generated selected void source | `954cd26cf7503954c44e070965e9d858ea9c6152794008d7b67482de1d8ecfad` |
| Focused selected object | `e44226dc253f3a6a55bf969cf6b9c844a178a9233e3706bd76aa14c81a9b5b81` |
| Genuine producer's ordinary object | `76c2e6c942525e66867ecfc4c004d190daf5c986dbc22dc588c7ffaffa7bd2f2` |
| Complete canonical payload | `bb2b2a43c0f81150a968df23f3bca3392bd5a7ac744df6f5f80c598939c89b39` |
| Genuine producer receipt | `317246b93c2a0bebee725184707248950160387c0c29bbcd575acd9ee387fe52` |
| Linked diagnostic image | `939c0755b71af5ecbc1097a9e011c5db7ec4a8d8ccc4d52fdb5ac8a55595b574` |
| Payload / callable prefix / frame | 82808 /81436 /570h |
| First strict target difference | +541 /4791BD, JNE operand at4791BB |

The public source reproduces the private all-seven payload completely.
The target has20243 reachable instructions versus selected20245. These
counts do not locate or bound the remaining differences. All11 switches
and15 request-buffer contracts still qualify. Remaining direct partitions
are4351C0/473DD0/478EE0, all involving300/320's merged physical copies.
Indirect totals remain220/219. Slot8 still has both the missing300/320
copy and616's association with the wrong shared action0 tail; its RET
partition also remains unresolved. SlotC and the mixed8/C partition retain
their earlier equality. See [the shared low-advance checkpoint](REIMU_SHARED_LOW_ADVANCE_2026_10_20.md).

## Real linked replay and execution

The source/CRT closure was rebuilt serially with the current root. Its
complete ordinary and linked82808-byte canonical payloads agree, including
all2473 fields:1104 numeric literals,1185 REL32 calls,14 metadata addresses,
7 globals and163 local code pointers. All1281 PE HIGHLOW fields,32 direct
callee identities,11 switch maps and15 request-buffer contracts qualify.
Eight linker INT3 alignment bytes are separately accounted for outside
the payload. The five existing nonexact provider diagnostics remain
nonexact. No DLL execution, original-TU identity or target exactness follows.

| Current ordinary execution | Cases | Differences | Required outcomes |
| --- | --- | --- | --- |
|Ten-action facing/height matrix|400|0|280 real effect115 entries,120 native action9 returns|
|Next-sequence thresholds|480|0|200 actual47D7C5 and120 actual4852FD callback/RET chains|
|Full-root integration/shot/nonflat|2675|0|1010 /1380 /285 cohort inputs|
|Prior shared-low-advance domain|5752|0|Real helpers/RET or first world entry; explicitly empty initial x87 stack|
|602 firing/misses|210|0|120 actual MT/object854 entries,90 RETs|
|300/320/321 continuation|989|0|All native RETs; real321 event28 predecessor required|
|Independent bool staging through606|2136|0|Cadence1980, texture96, required branches60|
|Wrong605 unsigned X source|400|8|Expected negative; actual effect entry arguments differ|

The facing matrix samples five facing bytes-128/-1/0/1/127, two X values,
Y0/150 and two x87 precisions.600/601/602/604/605/606 invoke the actual
landing transition even in sequence0; at sampledY150 it selects falling
action9, so those120 cases must RET without effect emission.608/650/651/658
retain their separately guarded landing behavior. Initially expecting400
effect entries correctly failed at600/Y150; the final contract distinguishes
the independently observed landing outcome rather than discarding the
airborne inputs. The accepted442-byte landing helper's real action9 path
also corroborates that outcome. Input SHA256 is
`caf28d5862601bc5e11ccdc536da5b65a3ea105386bbcd7e03c93dcdd15afd00`.

The private negative removes only605's signed-byte interpretation of the
captured direction before multiplication by7. Both full object auditors
qualify it; the same400 inputs detect eight real argument/trace differences
and the native audit exits1 as intended. No helper result or callback is
fabricated. Repeated/overlapping matrices are not additional unique coverage.
World/effect construction stops retain their existing entry-only meaning.
The matrix is now reproducible with the repository command
`scripts/audit-reimu-effect-direction-carriers.py`. It retains the complete
void-root qualification and native ABI/state/trace comparisons, additionally
requiring each input's actual landing CALL or skipped guard. The public
command freshly reproduces0/400 for selected source and8/400 for the negative,
with the same input hash as the private prototype.
The5752 matrix observes5292 actual advance entries per side, all with empty
x87 tags/TOP0. The bool stage excludes later fragments and disables the
separate sequence-landing macro whose608/658 labels are outside its scope;
it retains the current low-advance source and new604/605/606 carriers. This
is not a full bool root or an original compiler boundary.

**Unknown:** whole-root semantics, original TU/profile/visibility, returning
world/resource callbacks, indeterminate740 inputs, arbitrary initial x87
stacks and unmasked exceptions remain outside the proof. No compiler/LTCG
impossibility or aggregate exact-percentage claim is made.

## Reproduction

The selected ordinary build and diagnostics use:

```bash
python3 scripts/probe-reimu-action-source-shape.py --emit-only --void-root --output-dir build/reimu-sequence-carriers-20261020/selected
scripts/compile-unit.sh build/reimu-sequence-carriers-20261020/selected/ReimuActionStateDispatch.cpp build/reimu-sequence-carriers-20261020/selected/candidate.obj
python3 scripts/audit-reimu-call-sharing.py build/reimu-sequence-carriers-20261020/selected/candidate.obj
python3 scripts/audit-reimu-root-relocations.py build/reimu-sequence-carriers-20261020/selected/candidate.obj
taskset -c 0 nice -n 10 python3 scripts/audit-reimu-effect-direction-carriers.py build/reimu-sequence-carriers-20261020/selected/candidate.obj
```

Private recipes are under `.analysis/reimu-sequence-carriers-20261020/`;
input hashes and full reports are under the corresponding build directory.
`summary.json` retains every control's input/object/canonical pins and full
preservation outcome. `effect-prefixes.json` retains exact instruction
windows and actual outgoing destinations. `native-effects.json`,
`native-sequences.json`, `native-broad.json`, `native-advance.json` and
`negative605/native-effects.json` record the scoped execution and negative
control. `native-effects-public.json` and its `negative605/` counterpart
record the public command's fresh positive/negative replay.
`native602.json`, `native-three.json` and `native-bool606.json`
record the additional bounded replays. The current genuine receipts are
`build/reimu-ltcg/{receipt,coff-replay}.json`; the preceding receipts are
archived under this checkpoint's `prior-genuine/` directory. Generated files and analysis
databases are not committed. Builds, native probes and the single128MiB
Ghidra process use CPU0/nice10; VC8 builds are serial.
