# YoumuObject entry sequence-word and phase order, 2026-10-19

The5159-byte initializer at543670 now uses a short sequence parameter in its
local virtual interface and computes action902's decay before its phase
assignment. Instruction/edge-identical owner diagnostics improve6/30->23/30.
The complete root remains nonexact at+80; no exact function/byte is added.

## Independent target and ABI evidence

Original Japanese1.06a executable SHA256 remains
`56350024879199861579c11b0e1c67b9590e10a8d40cd5996b109deec9afca7e`.
Callable `[543670,544A97)` SHA256 is
`d680c9d1386e6c3f8cc5e755dffccbbd431864dee308f760cf48fe00274ed245`.
Fresh raw traversal reaches all1294 instructions/5159 bytes and closes both
validated switches, with no unledgered direct target or unresolved exit.

The canonical vtable cell6C50F8 points to this initializer at+3C. Its primary
table is6C50BC, COL6DA790 identifies YoumuObject, and slot+0C independently
points to45C390. This establishes that the
[Aya sequence-word witness](AYA_ENTRY_SEQUENCE_WORD_ABI_2026_10_19.md) applies
to this actual callee; an equal slot number alone would not suffice.

At45C390, sequence publication and loop termination consume only AX from a
four-byte argument slot; RET4 cleans that slot. The natural short implementation
in `scripts/probes/animation-sequence-word-abi.cpp` reproduces all202 bytes
under the existing animation-sequence unit comparator. This does not change
that unit's default int facade or add duplicate credit. The selected Youmu
view changes only its local sequence declaration; other virtual declarations,
field layout, receiver and root void-return ABI are preserved.

The width correction alone changes the entire canonical payload from
`43567e38fde7a057564096c0f761f977b30a50417b4f83e63ba606e1e5fddad9`
to `40b07bbd1269f9d10872b664b95c0e1b169432fd7e0e62cd1c23834f198b140e`.
It recovers16 additional owner instruction/edge sequences:6/30->22/30.
It does not recover the missing conversion copy or all tail memberships.

## Action902 order

The target limit6 duration path is explicit:

1. CALL4067D0 at544770, then its unsigned integer-to-x87 conversion.
2. JGE544782 / optional FADD544784 completes the unsigned correction.
3. FSUBR qword3.0 at54478A computes the real decay value.
4. MOV phase byte at544790 precedes FSTP state370 at544796.

The old source assigns phase before the subtraction expression. Its emitted
MOV phase precedes the conversion JGE, although the overall owner size agrees.
Moving the actual state assignment before phase in C++ permits VC8 to compute
the result first and schedule phase immediately before its final FSTP, matching
the target. No volatile access, forced register, extra operation or false
helper contract is introduced.

This recovers the whole action902 owner diagnostic:671 bytes/157 instructions
with the same encodings and internal/external edge roles. It is still an owner
comparison with relocation/owner offsets, not an independent exact function.
The complete unit continues to fail the strict canonical comparator.

## Selected result and remaining work

Selected source SHA256:
`09dd36f0e1c61a5f06e9f2e832a9dba9486e04d762f1190bc6ac5eea4a17c6b0`.
Canonical5488-byte payload SHA256:
`4b9bf0a4867dc153353faa2badf411196f4da92cd30112ec91cd115e79eefdce`.
Candidate metadata remains at5156 versus target5160. The5159-byte comparator
window therefore includes candidate-adjacent metadata; do not call it a
candidate callable hash. First mismatch remains+80/5436F0, the default-exit
branch displacement. Conversion-helper sites remain20/21 and RETs22/23.
All29 primary action destinations remain distinct.

The unclosed source/compiler questions are now concentrated in:

- Target820 enters850 after its two scale stores. The source hoists angle
  work and uses a different shared sequence tail;850 consequently lacks a
  target conversion/return copy.
- Action823 still differs in virtual-call register/preparation and subsequent
  spawn-argument registers.
- Target851 captures the pointer/vptr, writes state344, then loads heading[2].
  The retained double-value capture still loads the value too early.
- Action901's nested-table address reflects the four-byte metadata offset;
  the last owner also includes source post-RET alignment outside target credit.

An ordinary851 pointer-before-store/value-after-store control was repeated
only in this newly verified word-parameter context. It still merges distinct
851/854 owners: prefix/payload5116/5444,19 conversion sites and21 RETs.
The public owner audit rejects it with `candidate merges distinct target
physical owners`; its gate is unchanged and the control is not selected.
Preserve29 distinct destinations before accepting another lifetime model.

Read the earlier
[load-timing evidence](YOUMU_OBJECT_ENTRY_LOAD_TIMING_2026_10_02.md) and
[switch-closure evidence](YOUMU_OBJECT_ENTRY_SWITCH_CLOSURE_2026_09_26.md)
before repeating unchanged tail/cloning/visibility controls. Absence of a
reload does not determine whether the original source used a local variable.
Original remaining lifetimes, physical sharing and TU/LTCG context are unknown.

## Follow-up argument evaluation controls

A fresh build of source09dd36f0 retains canonical payload4b9bf0a4,
prefix/payload5156/5488,29 owners,20 conversions and22 RETs. The public
owner audit still reports23/30 instruction/edge diagnostics. The following
controls change only this root's private source; none is selected.

| Control | Result |
| --- | --- |
| Assign the850 angle inside the selector argument's comma expression | Complete canonical payload identical to baseline |
| Change all23 selector argument casts from `int` to `short` | Complete canonical payload identical to baseline |
| Cache the851 heading pointer, then write state344 inside the actual selector argument before reading parameters[2] |851/854 merge;28 owners,19 conversions,21 RETs |
| Cache the851 pointer and a typed `__thiscall` slotC dispatch before writing state344, then read the argument and call | Same complete payload as the preceding merge |
| Move the851 real double-value declaration after state344 in this word-parameter context | Same complete payload as the preceding merge |
| Add a local `float *__restrict` heading alias while retaining value-before-state order |29 owners remain, but851 still loads the value too early and other owners' shared tails/registers change |

The three merged controls all produce prefix/payload5116/5444 and SHA256
`76c4a245d987b57a04022a1f837854ab3ffb4d1e85be0b93aae57a2a9b2564d2`.
The explicit-dispatch public audit fails closed with
`candidate merges distinct target physical owners`; its acceptance contract
is unchanged. Neither a source comma expression nor an explicit pre-store
dispatch capture explains the target-distinct851 destination in this build.
The alias control produces prefix/payload5156/5488 and SHA256
`20e400af1cd2e22b91442c0b1e8de77bacea9f8a1c7de6bf5930c35c721134f3`.
Every control remains nonexact at+80/5436F0.

**Observed ownership evidence, limited scope:** the already accepted
YoumuObjectManager factory53B1C0 allocates a separate count*4 buffer when
count>0, publishes its pointer at53B240 to object+340, optionally copies
input words, then invokes object slot+8 at53B2A4. The raw237-byte factory
also reads its facing/field33c stack arguments as bytes at53B262/53B266.
This establishes the positive-count factory path. It does not establish
every writer, lifetime or caller of heading340, nor a compiler-visible
no-alias promise. No `restrict` declaration or shared helper ABI change is
adopted from that observation.

Receipts, complete trial sources, canonical packets and the factory raw
decode are below `build/youmu-entry-evaluation/`. Private candidates use
`scripts/compile-unit.sh`; baseline comparison and owner commands below
remain the public producer/checker. Direct384MiB/CPU0 read-only Ghidra
independently re-attests file/imported identity, entry, mapped text and root
bytes before bounded decoding/decompilation. All nine primary database
file hashes agree afterward and the temporary project alias is removed.
The decompiler output under
`.analysis/youmu-entry-evaluation-20261019/` remains a hypothesis. Required
IDA preflight again rejects the wrong open executable; no IDA semantics
or factory adapter is used. This follow-up changes evidence and handoff
only; source, ledgers, accepted-unit contracts and exact byte credit remain
unchanged.

## Whole-function exit and floating-environment controls

A further fresh target preflight and focused build retain the same baseline.
Replacing all27 outer-switch `return;` statements with `break;` produces the
same complete5488-byte canonical payload4b9bf0a4. None of these returns is
inside the nested match-identifier switch. Moving the real action823 payload
array declaration to the beginning of its arm and assigning its three values
at their original use point is also completely byte-neutral. The residual
tail/register behavior is not explained by either tested source scope.

Capturing heading340 once before the outer switch and using it for851's
post-state value load instead produces prefix/payload5000/5332, SHA256
`1c948f562eebebcd0a6a994636020c33a635828c2530f877868bf4aad5ee5bca`.
It first differs at+0A and has19 conversion sites/21 RETs; it is not selected.
Changing the local selector parameter to `unsigned short` under the same
profile produces5880/6212, SHA256
`b7a1c05591fe4ca14f469b0100ece15e12e6c008dbeaaff1a3a5ee73da33bbf0`.
It expands the frame from10h to14h and replaces all target conversion-helper
calls with inline control-word save/change, FISTP and restore sequences.
This is caller/profile evidence favoring the selected signed-word interface;
the low-word callee alone does not establish original source signedness.

Local `fenv_access(on)` produces5216/5548, SHA256
`5fcd69a05d9865b6afb8123f31f5aa7892f78fb0c3c8a2074b03ea6fee7ca08f`.
It preserves20 conversions/22 RETs and first differs at+80; it does not
recover the target21/23 copies. The successful sprite-rotation environment
recipe therefore does not transfer to this root as tested. All five controls
are unselected; no shared flags, headers or exact ledgers change. Sources,
build logs and complete canonical packets are below
`build/youmu-entry-exit-context/`. These experiments inspect the hash-attested
PE directly and make no new database/decompiler claims. Further identical
scope/exit tests lack new evidence; original ownership and compiler/TU phase
remain open.

## Reproduction and analysis limits

```bash
python3 scripts/build.py --unit gpt-web-youmu-object-action-entry --compare --json
python3 scripts/audit-giant-action-owners.py youmu-object-action-entry \
  build/match-units/GptWeb_YoumuObjectActionEntry.obj \
  --unit gpt-web-youmu-object-action-entry --json
scripts/compile-unit.sh scripts/probes/animation-sequence-word-abi.cpp \
  build/youmu-entry-sequence-word-abi.obj
python3 scripts/compare-unit-object.py cross-v106a-animation-sequence-virtuals \
  build/youmu-entry-sequence-word-abi.obj --address 0x0045C390 --json
python3 scripts/ci.py
git diff --check
```

The root comparison intentionally remains nonzero. The manual ABI producer
and existing-object comparator are separate; the latter does not attest build
provenance or replace the existing accepted unit's producer receipt. This
checkpoint does not claim new gameplay/native coverage or aggregate cold
replay. Shared headers, profiles, literal/relocation contracts and accepted
implementations elsewhere are unchanged.

Focused source, object and owner packets, independently read RTTI and the
rejected851 receipt remain below `build/youmu-entry-word/`. Direct Ghidra
re-attests executable identity, entry, mapped text and root bytes. Bounded
read-only decoding of the1294 target instructions and temporary5159-byte
function produces a decompiler hypothesis; it does not set the durable
boundary. Nine primary DB hashes remain unchanged and the temporary alias is
removed. The384MiB/CPU0 recipe is under
`.analysis/youmu-entry-word-20261019/`. Required IDA preflight rejects its
wrong PE; no IDA semantics, target-byte patch or factory adapter is used.
