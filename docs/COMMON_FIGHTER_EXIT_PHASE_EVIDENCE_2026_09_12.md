# Common Fighter: exit, switch and compiler-phase discriminators

## Result and scope

This follow-up stays on common Fighter `0x004740C0..0x004768AB`
(10219 callable bytes), original Japanese 1.06a SHA-256
`56350024879199861579c11b0e1c67b9590e10a8d40cd5996b109deec9afca7e`.

**No additional diagnostic owner closes in this batch.** Production remains
53/66 instruction/edge-identical owners, with 13 pending. Its canonical
comparison remains nonexact at +0x14, metadata +0x2838 and section tail 10801.
No matches, boundaries, shared headers, compiler profiles or relocation
permissions are changed. Only this root was compiled; no unrelated accepted
unit or global cold suite was replayed.

Fresh attestation and target packet:
`build/common13-next-preflight.json`, `build/common13-next-typed.json`.
Fresh baseline and final source comparison:
`build/common13-next-baseline-formal.json`,
`build/common13-next-width-formal.json`.
Both canonical windows hash to
`99563500433bccf1f68e7c256b438595de9cdcf5b18aee4816f19e69e1cda835`.
The corresponding `-owners.json` reports independently reproduce 53/66.

## Retained caller-width correction

**Observed:** all 15 current roster primary vtables have +8 = `0x0045BFE0`
and +0xC = `0x0045C390`. The following slots were individually read back
from the attested IDA database, using the existing RTTI-owned vtable anchors:

| Roster | +8 pointer slot | +0xC pointer slot |
| --- | --- | --- |
| Reimu | 0x006C4134 | 0x006C4138 |
| Marisa | 0x006C458C | 0x006C4590 |
| Sakuya | 0x006C491C | 0x006C4920 |
| Alice | 0x006C4BE4 | 0x006C4BE8 |
| Patchouli | 0x006C4EB4 | 0x006C4EB8 |
| Youmu | 0x006C514C | 0x006C5150 |
| Remilia | 0x006C53CC | 0x006C53D0 |
| Yuyuko | 0x006C5654 | 0x006C5658 |
| Yukari | 0x006C58D4 | 0x006C58D8 |
| Suika | 0x006C5B94 | 0x006C5B98 |
| Udonge | 0x006C5E34 | 0x006C5E38 |
| Komachi | 0x006C606C | 0x006C6070 |
| Aya | 0x006C62DC | 0x006C62E0 |
| Iku | 0x006C6534 | 0x006C6538 |
| Tenshi | 0x006C679C | 0x006C67A0 |

At `0x0045BFE0` the action argument is forwarded through a four-byte stack
slot into `0x00435200`. That body reads its low word into AX at
`0x00435200`, stores AX at this+0x13C, and ends with RET 4.
The sequence callee separately reads a DWORD argument at `0x0045C3E8`;
its subsequent word tests do not justify narrowing that caller declaration.

**Retained inference:** the local common-Fighter caller view now declares
`set_action(short)`, consistent with the established Animation API.
All this root's action arguments are constants in 0..789, so this does not
change values or stack cleanup. The caller deliberately ignores virtual
return values; the callee leaving EAX live is not by itself proof of an
original C++ return type. No return-type experiment is retained.

Fresh production build proves this parameter correction byte-neutral.
Raw IDA readback is in `build/common13-next-virtual-abi.json`.
It improves the documented call contract, not the canonical match count.

## Sequence-selection and exit controls

The target selection at `0x00474992` belongs to action 73. Target 75 and 88
enter it with the zero still live in the x87 stack. The selection's two
virtual-call paths each end in a normal epilogue. The default/x87-drop
epilogue also has a specific physical owner near action 75; reproducing just
the selection's local length does not reproduce that whole contract.

All private probes below start from the 53-owner checkpoint unless identified
as using the preceding native action-0 cohort. No row is retained in production.

| Probe suffix (`build/common13-next-*.cpp`) | Whole-root diagnostic | Outcome |
| --- | --- | --- |
| `inline-sequence` | blocked | Ordinary inline member remains an extra unresolved call; no helper binding was invented. |
| `inline-body` | 51/66; metadata 10332 | Explicit inlining regresses default owner 68 and action 799; action 75 grows to 195 bytes. |
| `sequence75-return` | 51/66; metadata 10332 | Independent selection with 75 returning and 88 breaking still moves default/selection ownership. |
| `sequence-else` | 53/66; metadata 10296 | Keeping the shared label but making action 73's motion a full else arm does not improve ownership. |
| `sequence-source-order` | 52/66; metadata 10300 | Moving case 88 before 73 moves its actual body there too, and loses action 799. |
| `completion-guards` | 56/66; metadata 10560 | Negative completion guards in the native action-0 cohort retain its previous late duplication and action-799 regression. |
| `compound-steps` | 56/66; metadata 10560 | Two real field `+=` steps generate the same rounded sequence as two float temporaries, without repairing late tail merging. |
| `positive-shared` | 51/66; metadata 10212 | Positive late guards with a real shared action-50 label still move the tail to action 162 and lose action 50/799. |
| `inline-slide` | 54/66; metadata 10544 | A fully inlined semantic slide helper gains 53/54 locally but loses action 799 and leaves other failures. |
| `range-guards` | 10/66; metadata 10924 | Explicit low/high range guards introduce extra code and broad owner regressions. |

The `completion-guards`, `compound-steps` and `inline-slide` inputs use
the previously rejected native action-0 assignment cohort, not production.
Their higher counts must not be described as improvements over the retained
checkpoint: they also regress previously matching owners and grow the body.

## SUB is not an unavailable VC8 encoding

A read-only scan of already accepted target extents identified sparse-switch
SUB/CMP witnesses in Alice action entry, Youmu/Remilia control mode, and
Komachi control mode. Existing units record the same ordinary VC8 /O2 profile.
Youmu's actual IDA instructions at `0x00539FAA` were read afresh:
SUB EAX,12; CMP EAX,243; JA default; MOVZX; indirect jump.
These were bounded compiler witnesses, not a new character reconstruction
batch, and their modules were not rebuilt.

More decisively, a **fresh common-Fighter single-switch probe** emits SUB
at the low selector +0x1E and at the high selector under the unchanged
standalone compiler profile. Consequently the old ADD-negative difference
alone does not prove a compiler-version or LTCG limitation.

It is still the wrong complete function:

- `native-switch`: the low table has 48 destinations, merging target-distinct
  50/52 and 62/63/64 owners. The strict audit correctly refuses its topology.
- `native-partition`: ordinary assignment-expression distinctions preserve
  50/51/52, but its 49-entry low table still merges 62/63/64.
- `native-distinct`: 50 low entries; 62/64 remain merged. The audit correctly
  reports merged distinct target physical owners.
- `native-rounded`: all expected low destinations survive, permitting a
  complete audit, but only **45/66** owners match. Eight previously matching
  owners regress; metadata is 10560. It also leaves an extra action-690 body
  near the high dispatcher, so the entry branches are wrong even though SUB
  is now correct. Canonical comparison is nonexact at +0x14.

Those table counts were read directly from the compiled dispatch instruction
relocations and their index tables. No target manifest, accepted candidate
counts, owner-identity checks or comparator rules were relaxed.

The surviving question is simultaneous switch/source and tail ownership.
Neither matching the selector bytes nor preserving table cardinality closes it.

## Reproducible LTCG visibility control

The native assignment source still generates an aligned EBP frame under /GL
and /LTCG, even after eliminating the live cross-label double intermediates.
Linking the same GL input with /INCLUDE instead of /EXPORT also preserves that
non-target frame. This rejects those two simple explanations; it does not
prove that every possible real TU/caller context is impossible.

The reusable diagnostic is now tracked as
[scripts/probe-ltcg-visibility.sh](../scripts/probe-ltcg-visibility.sh):

```bash
bash scripts/probe-ltcg-visibility.sh \
  src/battle/FighterCommonActionState.cpp \
  '?update_common_action_state@FighterCommonActionStateView@th105@@QAEXXZ'
```

It compiles one real source TU once and performs two serial links of that
same GL object. Input/compiler hashes, compile/link logs, maps and disassembly
are generated in a fresh `build/ltcg-visibility.XXXXXX/` directory.
The current production replay is `build/ltcg-visibility.Z41KS0/`.
Both forms start PUSH EBP; MOV EBP,ESP; AND ESP,-8, unlike the target PUSH ECX.

**These DLLs have unresolved symbols, must never be executed and are not
canonical comparison inputs.** The tool adds no fake providers, ABI stubs or
synthetic callers. Exit zero means the inspection pipeline completed only.
It does not replace the normal object comparator or establish exact progress.

## Focused final gate

```bash
python3 scripts/build.py --unit gpt-web-fighter-common-action-state --compare --json
python3 scripts/audit-giant-action-owners.py fighter-common-action \
  build/match-units/GptWeb_FighterCommonActionState.obj \
  --unit gpt-web-fighter-common-action-state --json
python3 scripts/validate-tracking.py --require-target
python3 scripts/ci.py
git diff --check
```

The first command still returns 1 for the nonexact body. Remaining owners are
entry; low 53/54/55/56, 73/75/88, 159/160/161/162; and low 180 including the
high dispatcher. Future changes need an independently motivated source/TU
distinction, not more arbitrary register, label or storage permutations.
