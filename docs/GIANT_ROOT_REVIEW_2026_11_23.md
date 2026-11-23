# Giant action root review

Start the compiler investigation at the shared Fighter root `0x004740C0`.
The current VC8 SP1 build reproduces 53 of 66 physical owners in the
instruction/edge diagnostic. Its 10,219-byte callable still differs at
`+0x14`, and the candidate section is 10,801 bytes versus a 10,736-byte
target envelope. It is small enough to review all the remaining shared
tails and is called by all fifteen roster Fighter roots. All TH105 results
below use the hash-attested Japanese 1.06a PE.

## The difference can originate in another case

The target places the sequence-selection tail in action 73 at `0x00474992`.
Actions 75 and 88 can enter with a value live on the x87 stack. The normal
build places the tail in action 88. Removing only case 88 in a scratch copy
keeps the source of case 75 identical, yet its emitted span grows from 148
to 200 bytes. Its jump into action 88 becomes a local x87 compare followed
by a virtual call and epilogue on each of two paths. The
owner audit rejects the scratch object's changed dispatch topology as
expected. The switch mapper and disassembly are sufficient to observe the
effect on case 75.

[Earlier controls](COMMON_FIGHTER_EXIT_PHASE_EVIDENCE_2026_09_12.md) already
showed that this VC8 can emit the target SUB in a different switch shape,
and that moving the source order or inlining the sequence body trades one
wrong owner for another. Follow the x87 value and receiver through the
73/75/88 join and the two virtual exits in the complete carrier. Treat the
50/159–162 clamp tail as a second group. Record changes to the instructions
and their destinations separately from shifts in byte offsets.

TH09's `RunEcl` omitted neighboring handlers in scratch to find the shared
tails driving register choices in otherwise unchanged handlers. Its
`BeginPlaybackStage` retained the seed setter call, but exposing the real
setter definition changed which earlier load and store depended on the call.
The allocator and scheduler traces distinguished those dependencies from the
final register choices. See TH09 `e099d327`, `docs/RE_WORKFLOW.md` and the
`RunEcl register coupling across handlers` and
`Co-visible replay seed and exact playback` sections of its knowledge base.

Use the same declaration-versus-real-definition control when an actual
call or global read/write lies in a divergent slice. Fix the caller, ABI and
profile. Track each retained call and compare the real callee and affected
consumers. TH105 already has a positive TU control at `0x00471E50`: hiding
the exact 33-byte base loader behind its declaration restores the out-of-line
call and gives a 97/97 match. Trace allocation or scheduling in the pinned VC8
SP1 `c2.dll` once a before/after pair isolates a shared tail, live range or
memory dependency. TH09's private C2 addresses are for a different binary.
The existing Rich records and failed LTCG controls do not identify this
root's original compilation context. [TH105 TU example](BUILD_MATCHING.md#use-translation-unit-visibility-before-compiler-attributes)

## What the byte check covers

The fresh exact Sakuya Fighter initializer at `0x004DE060` compares all
2,656 bytes, including 47 jump words, 359 remap bytes and the alignment.
A separate replay using GNU objdump's PE sections and COFF symbols and
relocations reproduced all 2,656 bytes and 99 relocation fields. Changing
the last remap byte at `0x004DEABF` from valid index 25 to valid index 26
leaves the 2,106-byte callable comparison equal. The configured
`switch_payload` rejects the changed object at that address.

Komachi `0x005E20E0` now has a complete `switch_payload` in its build unit.
The 63,993-byte callable comparison runs first and currently fails at `+8`
(frame `0x490` native, `0x498` rebuilt). A separate replay of the complete
candidate section resolves 1,857 relocations and compares 65,304 rebuilt
bytes against the 65,176-byte target envelope. The switch mapper pairs the
card gate and the three action tables. The raw owner audit follows those
four tables and the three keyed by `g_match_identifier`, covering all
63,993 callable bytes. The selector reads at `0x005F06F9`,
`0x005F0B23` and `0x005F0DB6` all address `0x006FA894`, which the exact
battle setup writes from the first `MatchSetup` DWORD at `0x0047096A`.
Owner pairing stops because actions 209 and 212
share one entry in the selected candidate. Their native entries at `0x005E3661` and
`0x005E3815` have distinct prefixes and join at `0x005E3683` on the
non-crossing path. Expanding action 212's helper and spelling its branch
in the opposite direction still emits the original candidate.

The compact-switch verifier checks the reaching `EBX = 8` definition at
`0x005E210A` for the card gate's register bound at `0x005E213B`. The one
intervening call is the VC8 deque subscript at `0x004399C0`, which preserves
EBX. Action 730's `FSTP` at `0x005F0DBE` stores a DWORD to the stack between
CMP and JA. The native structural check covers all seven tables, 120 jump
words, 692 remap bytes and 11 alignment bytes. A one-byte change in each
table is rejected at the changed address. This check uses target bytes and
expected relocation sites. Source acceptance still requires an actual COFF
object with all matching bytes and relocations.

## Engine references and readable source

- TH075 `4abd6618` has full code-plus-table matches for Alice Object
  `0x004EBDA0` (33,731 bytes) and Remilia Object `0x0055AC80` (28,862 bytes).
  Its Youmu Fighter `0x005214B0` and Sakuya Object `0x004CA6E0` are useful
  role and control-flow references with open register-allocation differences.
  Compare action and animation transitions, call order, and object ownership
  before borrowing a source shape. Even a reused action number can select a
  different path. See TH075 `docs/GIANTS.md` and `config/matches.csv`.
- EFZ `7198298` has a full 63,551-byte match for Nayuki `Slot06`, including
  137 live cases, two switch tables and 1,433 relocations. Its entry freeze
  gate and frame-driven dispatch are useful parallels to Fighter action
  updates. Its visual patterns and battle-frame arrays differ from TH105's
  action map and linked animation blocks. EFZ's way of recovering frame
  lifetimes and comparing whole dispatchers is transferable. See EFZ
  `src/Character10State.cpp`, `docs/ORACLES.md` and
  [TH105 sequence evidence](ANIMATION_SEQUENCE_SEMANTICS_2026_11_07.md).
- The Komachi dispatcher now uses five checked position, velocity and
  acceleration members in place of 447 float offset accesses. Its complete
  65,304-byte candidate and switch topology are identical to the offset
  version. Applying typed fields incrementally keeps signed and unsigned
  consumers, evaluation order and individual x87 rounding points visible
  during review. [Checked motion fields](KOMACHI_ACTION_STATE_2026_10_28.md#checked-motion-fields-2026-11-23)

## Reproduce the selected baselines

```sh
scripts/repo-python scripts/build.py --unit exact-first-sakuya-action-initialization --compare --json
scripts/repo-python scripts/build.py --unit exact-first-komachi-action-state --compare --json
scripts/repo-python scripts/compare-giant-action-switches.py komachi-vslot28 build/match-units/ExactFirst_KomachiActionState.obj --json
scripts/repo-python scripts/build.py --unit gpt-web-fighter-common-action-state --compare --json
scripts/repo-python scripts/audit-giant-action-owners.py fighter-common-action build/match-units/GptWeb_FighterCommonActionState.obj --unit gpt-web-fighter-common-action-state --json
```
