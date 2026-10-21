# ReimuObject 822 constant lifetime and physical sharing

This bounded follow-up uses only the hash-attested Japanese 1.06a PE,
SHA256 `56350024879199861579c11b0e1c67b9590e10a8d40cd5996b109deec9afca7e`.
IDA preflight still rejects the open image. No database semantics are used.
The selected `496540` source, public types, compiler profile, bindings,
ownership and exact rows remain unchanged. No new exact credit is claimed.

## Selected comparison and entry observations

`build/reimu-object-822-constant-lifetime-20261022/mapper-formal.json` freshly
reproduces the complete selected comparison:

| Body | Result |
| --- | --- |
| `496540` | Source section 45,700 bytes; owned target comparison 46,138 bytes; first difference `49655F / +31` |
| `4963A0` | Accepted exact 66/66 |

Selected source SHA256 is
`3b9e4896c3645bb1228db3b432a832154870c5639a80df6c02cb67ce2dba12cc`;
canonical compared source SHA256 is
`d0ff3d3259c823cc56e322c5e0ec238456d8b490c78b4a5336a249b45a405a58`.
The target envelope includes 46,128 code bytes and 10 alignment bytes.

The target dispatches immediately after its index-table load. The source
inserts `mov ebx,1; xor ebp,ebp` before the indirect jump, retaining constants
across action entries. The first byte difference is the earlier JA displacement,
not the first constant instruction. `entry-facts.json` pins both entries;
its 1,450-byte action-822 disassembly is a lexical window, not a closed boundary.

## Controlled source pair

`controlled_pair.py` recompiles two frozen sources through the same input path,
output path, compiler command and explicit current profile. Their only diff
places the real 822 sequence-4 direction/Y/X expressions inside the outgoing
spawn call instead of evaluating them into preceding locals. The pair is
historical source input, not the selected source epoch.

| Frozen input | Fresh section bytes | Entry constants |
| --- | ---: | --- |
| `old-coordinate-locals.cpp`, SHA prefix `78d85ab4` | 46,144 | Neither EBX=1 nor EBP=0 before dispatch |
| `old-call-arguments.cpp`, SHA prefix `f614d41b` | 45,716 | Both constants before dispatch |

Both builds retain the exact 66-byte counter. Full source/object/compiler pins
and copied objects are in `controlled-call-argument-pair.json`. The newly built
46,144-byte input is **not** byte-identical to the old retained 46,160-byte
object; this experiment establishes the transition under current controlled
inputs and does not reproduce that historical object.

This pair ties the outgoing argument rewrite to a whole-root optimization
change under the tested context. It does not attribute the entire 428-byte
size change to two loads or establish the original source form. The selected
argument preparation remains supported by the preceding original-RNG execution
receipts: equal final outputs alone did not preserve target facing and pending
argument lifetimes. Reverting it merely to remove entry constants would discard
that stronger evidence. See [the argument-lifetime record](REIMU_OBJECT_822_ARGUMENT_LIFETIMES_2026_10_21.md).

## Fresh physical call and return census

`census.py baseline` rebuilds target reachability from the PE and candidate
reachability from the current object, including reviewed switch destinations.
`baseline-census.json` records 433 physical calls / 68 RETs in the target and
428 / 63 in the source; call/RET membership distances remain 11 / 27.
These are normal-control-flow facts, not execution through opaque callbacks.

For example, target advance calls at `496844`, `497D6F` and `49A5DD` belong
respectively to actions 800/821, 811 and 825. The source shares one physical
call among all four actions. In all three target tails, a successful advance
can decrement `state_330`, followed by an independent frame/sequence predicate
that can decrement it again. A short-circuit return after the first decrement
would change behavior. The selected 811 source already has local independent
checks; a natural zero-guard rewrite produces exactly the same complete root
bytes and sharing distances. Merely duplicating source tails does not force
the compiler to retain distinct physical calls.

The generic mapper now reports 404 decoded direct calls to 25 targets. Its
legacy raw E8 fingerprint remains 405/26: the extra E8 is inside FLD1 at
`49C35A`, not a call to `4C611D`. The specialized auditor already excluded it.
The raw regression guards remain unchanged. `direct-provider-inventory.json`
lists the 25 real starts and their current source/unit annotations.

## Unselected controls and limits

All controls retain source recipes below
`.analysis/reimu-object-822-constant-lifetime-20261022/` and reports below the
matching `build/` directory. None changes reconstruction selection.

| Control | Observation |
| --- | --- |
| Byte variant formal and matching callback typedef in genuine Object providers | Complete parented/unparented wrappers still exact 77/77 and 78/78; original formal width remains ambiguous |
| Matching byte-variant caller view at all 106 request expressions | Root 45,712 bytes and still nonexact; 822 diagnostic window remains 225 bytes with 13 differing bytes after known CALL replay |
| Signed direction choice with int-facing declaration | Root 45,700 bytes; request window 227 versus 225; entry constants remain |
| Signed direction choice with the preceding byte-facing caller view | Root 45,700 bytes; request window 224 versus 225; entry constants remain |
| Consistent bool declaration/definition for the genuine `4963A0` counter | Counter still 66/66 and complete root byte-identical; does not prove the original return type |
| Actual `OutcomeRandom.cpp` body visible with the root | RNG `4067D0` remains exact 27/27, counter 66/66, complete root byte-identical; RNG visibility alone does not fix this context |
| Root-local size optimization preference | Raw entry already differs; strict root comparison blocked on unknown `_ftol2`; not a completed canonical negative |

Interior window comparisons are diagnostics with no partial exact credit.
The bool-counter result does not establish a bool contract for the different
advance provider at `4351C0`, whose virtual return may contain arbitrary AL.
No extra runtime sweep is claimed for these unselected nonidentical callers.

Next investigate a genuine provider-backed compiler/link context using the
decoded callee inventory. Previous hosted controls with ABS code placeholders
do not qualify that context. These observations prove neither that LTCG is
required nor that a standalone object match is impossible. Preserve the
selected argument-lifetime evidence, independent retirement checks and all
accepted helper comparisons while changing one context at a time.
