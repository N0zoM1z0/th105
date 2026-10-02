# AyaObject quarter-speed motion and callback value reads

## Retained bounded result

**Observed:** `AyaObject_update_action_state_vslot28 @ 0x0061A290` owns the
reviewed `[61A290,61EED2)`, 19,522 bytes, in the original Japanese 1.06a
executable SHA-256
`56350024879199861579c11b0e1c67b9590e10a8d40cd5996b109deec9afca7e`.
Callable SHA-256 remains
`18c813a20cea427b2c3577e2612e3f2e949a191ee2496dc9204331758bebb895`.
This follows [the alpha-read checkpoint](AYA_OBJECT_ALPHA_READ_AND_X87_2026_10_02.md).

Retained source now recovers812/821's quarter-speed Y update,812's separately
evaluated projection inputs,820's post-effect sequence and post-spawn owner
reads, and820's floating variant addition. No shared ABI/header/helper,
compiler profile, relocation mapping or object partition changes.

Fresh configured whole-root request remains **nonexact at +0x22**, target
`0F` / candidate `1C`. Candidate metadata starts at19,024 (`+4A50`) versus
target19,524 (`+4C44`), a500-byte metadata gap. Available section tail is19,492,
30 bytes shorter than the requested target callable. Raw owner diagnostics
are2/34 (entry,980), with33 distinct destinations/zero target-group splits;
the apparent default802 loss is an alignment-span artifact explained below.
No exact function or byte credit is added. Retained LF source SHA-256:
`c02e07a43b73e2fadd89f8d59dea2062a48b417cf2a5078e5a7ab0ca555306a7`.
Available canonical candidate-window SHA-256:
`2387851567da37f6e21757747d0c3053d7004cdd5de5ca1e1e641812f1166ae2`.
This window includes adjacent metadata; it is neither a body hash nor a
complete comparison extent.

## Quarter-speed Y update

**Observed:** target812 sequence2 at `[61AE15,61AE2D)` and821 sequence1 at
`[61B9A0,61B9B8)` perform exactly:

```
FLD  dword [this+F8]
FMUL qword [6C33A8]
FADD dword [this+F0]
FSTP dword [this+F0]
```

Qword6C33A8 is `000000000000d03f`, exactly0.25. There is no preceding full
vertical-speed addition on either selected path. The old source performed
`Y += velocity_y`, then `Y = float(Y + velocity_y * 0.25)`. Its first addition
also introduced an extra32-bit rounding step in the candidate. For the exact
finite inputs Y=100, velocity_y=8, target yields102 and old source110;
velocity_y=-8 yields98 and90 respectively. These demonstrate the arithmetic
difference within the update interval, without assuming full-game reachability
of those states or a particular global x87 environment.

**Inferred and retained:** remove only the first full-speed addition in812/821.
VC8 emits the target's four instructions naturally. Fresh corresponding
candidate intervals `[61AECA,61AEE2)` and `[61BA2F,61BA47)` have the same24
replayed bytes as their target intervals. This is a diagnostic of two bounded
updates, not regional/function acceptance: surrounding control flow, helper
inputs and whole-root bytes remain nonexact.

## Separate812 projection argument evaluations

**Observed:** after cosine call61AFB2, target stores X at61AFD4, loads the
heading input again at61AFDA, multiplies by the sign-extended facing value,
rounds the outgoing float argument and calls sine at61AFED. The retained
source previously computed one `oriented_phase` and reused it for both X/Y.
Candidate consequently loaded the old rounded local for the sine call.

**Inferred and retained:** evaluate each outgoing phase at its own call site.
Candidate now stores X at61B01A and reloads heading at61B020 before sine
61B033. This preserves the target's actual reads and separate arithmetic,
without asserting that heading storage can alias X in ordinary game states
or that the intervening callee changes it. Those invariants remain unknown.
The stage-phase integer is also converted directly in its outgoing argument,
matching target's FILD/FSTP-argument pair rather than an extra named float
store/reload. Float parameter widths and current helper return declarations
are unchanged; the latter are not newly proven by these caller observations.

The first oriented multiply still lowers differently: target loads heading
then FILD/FMULP, while candidate uses FILD/FMUL-memory. Stack homes differ.
The new fresh-read behavior does not establish complete precision/exception
or instruction closure for this path.

##820 values read after effect calls

**Observed:** target's early0/4 sequence gate precedes call5575C0 at61B4D0.
After a false helper result,61B4DD tests the current word `[this+13E]` against0.
Old source/candidate used the pre-call `sequence` value, held in DI. Source
now refreshes `sequence` at that boundary; candidate directly compares
`[this+13E]` at61B567. The existing later sequence refresh after the own
next-block callback is preserved.

**Observed:** after spawn call64CCB0 at61B589, target reloads `[this+348]`
at61B58E, checks owner action540, and conditionally checks owner sequence>1.
Old source/candidate kept the owner pointer cached before spawn in EDI.
Source now captures the current owner after that call boundary. Candidate
reloads `[this+348]` at61B61B; its complete35-byte owner-check/next-block-call
suffix `[61B61B,61B63E)` agrees with target `[61B58E,61B5B1)` after replay.

The old source also named owner sequence before its OR predicate, but baseline
VC8 already placed that load inside the short-circuit branch. There was no
unconditional emitted sequence dereference to fix. The new source expresses
the existing target short circuit directly; the actual recovered operation
is the owner-pointer reload. These observations do not prove that either
effect helper changes sequence/owner on a reachable game path.

##820 random variant conversion order

**Observed:** target masks MT output with1, converts the resulting unsigned
integer through FILD/unsigned correction, then adds qword2.0 at6C21C0.
Old source/candidate added integer2 before conversion. Changing2u to2.0f
naturally recovers the target conversion/FADD order and the DWORD unsigned
correction constant6D6EF8. Both produce exactly2/3 for the two masked values;
this is instruction/value-flow recovery, not an additional behavioral bug.
A double-conversion control emits the qword unsigned correction constant at
6D6ED0 instead of target's DWORD and is not retained.

## Owner diagnostic alignment correction

**Observed:** final candidate default802's call/epilogue ends with RET61ECDE.
Byte61ECDF is a following90 alignment NOP; metadata starts61ECE0. The current
owner auditor extends the last candidate owner up to metadata, including that
NOP, while target default802 stops at the callable RET. Its only difference
for this owner is the inserted NOP, giving spans13/14. No direct branch enters
the NOP, and it has no fallthrough from the preceding RET. The callable
default instructions remain unchanged.

Private-control readbacks identify the same issue in the earlier817/822
switch controls: one post-RET NOP, or a3-byte `LEA ECX,[ECX]` alignment. Current
fresh-phase and owner-read controls similarly have3-byte LEA or2-byte
`MOV EDI,EDI` alignment. Thus their2/34 score does not mean default behavior
or instructions were lost. Earlier language saying the switch control
"loses default802" is corrected in the alpha checkpoint. Incorrect822
sequence1 sharing still independently makes that control nonexact.

The private raw exporter is now explicitly sliced at candidate metadata
start: its COFF helper returns a section tail despite the requested length.
Earlier unsliced packets also annotated zeroed adjacent metadata as default
instructions. Those annotations are not callable facts. Target decoding was
already bounded correctly; reviewed float intervals, callback sites and guard
roles are before metadata and remain valid. The durable auditor/comparator
and acceptance rules are unchanged;2/34 is reported as its actual output.

## Controls, reproduction and remaining work

| Sequential control | Metadata | Raw diagnostics |812 /820 /821 spans |
| --- | ---: | ---: | --- |
| Fresh baseline |19020|3/34|801 /1002 /1059|
| Quarter Y only |18988|3/34|785 /1002 /1043|
| Fresh812 phases |19012|2/34|806 /1002 /1043|
| Float variant addition |19012|3/34|806 /1005 /1043|
| Current owner read |19020|2/34|806 /1011 /1043|
| Current own-sequence read, retained |19024|2/34|806 /1016 /1043|

Target spans are817 /1015 /1123. These counts/sizes and individual equal
intervals provide no exact acceptance. Each added source property follows
the separately observed value/write/call boundary above; no artificial
storage, assembly or compiler-flag change is used.

```bash
python3 scripts/build.py --unit gpt-web-aya-object-vslot28-full-root --compare --json
python3 scripts/audit-giant-action-owners.py aya-object-vslot28 \
  build/match-units/GptWeb_AyaObjectActionState.obj \
  --unit gpt-web-aya-object-vslot28-full-root --json
```

Fresh configured reports are `build/aya-value-lifetimes-final-20261002.json`
and `build/aya-value-lifetimes-final-owners-20261002.json`. Corresponding raw,
guard and local-read proof reports share that prefix. Private source controls
and proof exporter are below `.analysis/aya-value-lifetimes-20261002/`;
their independently source-hashed summary is
`build/aya-value-lifetimes-20261002/controls-summary.json`. Existing-object
control comparisons have no configured build provenance and award no credit.

Complete target traversal remains4,630 instructions/all19,522 bytes with
seven validated switches and no unresolved indirect exit or unledgered direct
target. Guards remain124/124, with the previously reconciled902 ordinal
role/path lead. IDA still fails on the wrong attached executable; new facts
use the hash-verified PE. Prior900/902 unordered predicates and817/822 alpha
reads are preserved. Unknowns include the remaining floating operands/value
lifetimes, successful/failure suffixes, stack homes, argument/virtual-call
scheduling and original TU/LTCG context. No cold aggregate replay is claimed.
