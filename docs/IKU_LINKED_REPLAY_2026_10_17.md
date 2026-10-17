# Iku full linked-root relocation replay

Historical d0eede0 compiler comparison. Current source and linked extents are
in [the glide exit checkpoint](IKU_GLIDE_EXIT_OWNERSHIP_2026_10_17.md); the
full replay procedure remains applicable.

The subsequent [action/payload partition checkpoint](IKU_ACTION_PAYLOAD_PARTITIONS_2026_10_17.md)
resolves the11 static correlation ambiguities below under the existing ordinal
pairing. This linked compiler comparison and the selected source remain valid.

The [real source link](IKU_REAL_LINK_2026_10_17.md) now has complete diagnostic
relocation replay. Its strict59038-byte comparison against Iku620920 remains
**nonexact+0x64 /620984**. Across all59594 shared bytes, the linked and ordinary
objects differ in only22 bytes inside one scheduling interval. This specific
link context does not explain the root's extra shared-tail calls or table
layout; it does not rule out other original TU/LTCG contexts.

## Observed target and replay

Target is the original Japanese TH10.5 v1.06a executable, SHA-256
`56350024879199861579c11b0e1c67b9590e10a8d40cd5996b109deec9afca7e`.
Root `[620920,62EFBE)` is59038 bytes, SHA-256
`abc831c6ccd95986bed811694f532ad8c8b92cb49702a7f6ce4de100b8a73dea`.
The attached wrong-image IDA preflight was rejected; evidence here is from the
hash-attested PE and genuine linked image, without an analysis database.

The v2 public link probe first closes the entire linked CFG through the
existing inspector, then uses `scripts/linked_switch_replay.py` to replay the
full59600-byte envelope at target coordinates. It accounts for every HIGHLOW:

| Field kind | Count | Evidence required |
| --- | ---: | --- |
| Floating literal references | 785 | Unique exact linker-map name, encoded literal bits, readonly initialized source bytes, access width, selected canonical key and target bytes |
| Local table addresses | 6 | Decoded switch/index operand and validated root-owned table range |
| Switch destinations | 110 | Table field relocation and destination at a decoded instruction boundary |

There are131 distinct floating literal identities. All867 ordinary CALLs are
replayed by actual provider symbols and their existing target contracts.
Two direct game-data reads retain their attested ABS address. Duplicate,
partial, unsupported and unconsumed base relocations fail; unclassified
pointer-shaped references fail. No instruction, branch, metadata or padding
byte is masked. The fixed target comparison includes all59038 bytes.

Metadata starts at linked offset58440 and ends59594, exactly the ordinary
section tail extent. Both one-byte NOP gaps between tables remain significant.
The six additional linked bytes are INT3 alignment before the next16-byte
aligned function. They are retained in the full envelope and reported as an
unmatched linked tail, not silently removed. SDK94/100-byte deque witnesses,
the41 providers, five nonexact dependency addresses and provisional406330
adapter retain their prior scope. No linked-image execution is claimed.

## Ordinary versus linked compiler context

The ordinary object is freshly rebuilt and its source, target, compiler,
unit-input digest and object hash are checked against build provenance before
comparison. All59594 common bytes are compared. The only differing ranges are
offsets `[53290,53304)` and `[53305,53313)`,22 bytes total. They lie inside the
same29-byte action730 interval, at **candidate coordinates**62D944..62D961.
These coordinates are not the corresponding raw target addresses.

Ordinary code orders `FMUL; ADD ESP,4; FADD velocityY; FSTP velocityY; MOV mode;
CMP mode,3`. Linked code moves the mode load before stack cleanup and the mode
comparison before the Y addition/store. All instruction counts, subsequent
offsets, ordinary/register call sites and switch metadata are unchanged.

Raw target `[62DB4F,62DB6C)` independently contains the ordinary order and is
byte-identical to that ordinary29-byte interval after relocation replay.
Its SHA-256 is `f4bd1a645e86324a7611815f22cd00776b513482a406968e219e092d9a5e082c`.
This internal witness is not an independent callable, exact unit or partial
authored credit. Source remains unchanged; no `/GL` acceptance-profile change
is selected from this scheduling result. Exceptional observation timing and
the original compiler context remain unknown.

| Artifact | Normalized SHA-256 |
| --- | --- |
| Ordinary complete59594-byte section | `33f09d2ac49075ed6495a5b10a884fe18cf1f5b9e8556dcdec157eb58038549d` |
| Linked first59594 bytes | `3885f32d209390b0df624f57c504d1ed4fb5af9959fe4a8d5ee210202798d544` |
| Linked full59600-byte envelope | `fc3961ccaf603687f7b25141d053775939e0bf53cdd7f7072ae6f69b01fe20fb` |
| Linked fixed59038-byte target comparison | `5e6951fa4fdef56977a2b47af5860a5988d0ee411f3b81a62e9752a05609be3d` |

## Reproduction and next work

```sh
python3 scripts/build.py --unit gpt-web-iku-action-state --compare --json > build/iku-linked-canonical-baseline.json
python3 scripts/probe-iku-action-ltcg.py --reuse --ordinary-object build/match-units/GptWeb_IkuActionState.obj > build/iku-linked-replay-final.json
python3 scripts/ci.py
git diff --check
```

The focused ordinary comparison intentionally exits1 for nonexact+64hex.
The genuine link and full diagnostic replay succeed; all44 source compilation
steps reuse hash-checked objects. The v2 receipt at
`build/iku-action-ltcg/receipt.json` binds the new replay module as well as
source/tool/image/map inputs. Five parser/control tests cover complete field
replay, preserved opcode differences, literal identity/bytes/width/section,
relocation completeness, instruction boundaries, index bytes, tail alignment,
call identity and game-data identity. They use synthetic parser fixtures,
not original executable content or fabricated match implementations.

No game source, shared header, accepted profile, type layout, source partition,
relocation ledger, match count or authored credit changes in this checkpoint.
Historical native matrices and unrelated accepted units are not rerun. Remove
the superseded private prototype and reports; retain the small current link
cache for the next bounded source change.

Continue the joint call/payload ownership problem: effect416/417/565..568 share
target626C34's live-ST0 argument tail while source retains four extra sites;
action730 retains one extra face site;11 payload-home correlations still merge
action and pointer provenance independently. Full original source/inheritance/
TU, broader LTCG context and post-backend/exception behavior remain unknown.
