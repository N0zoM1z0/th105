# Sakuya Fighter action-state root (`0x004CADB0`)

`Sakuya_dispatch_action_state_vslot28` is canonically exact under VC8 SP1
`/O2 /GS- /GR /EHsc /MT` in `exact-first-sakuya-action-state`. The standalone
[typed source](../src/characters/SakuyaActionState.cpp) has 62 checked member
offsets and replaces the old raw-access header.

The target is original Japanese TH10.5 v1.06a, SHA-256
`56350024879199861579c11b0e1c67b9590e10a8d40cd5996b109deec9afca7e`.
This pass used hash-attested raw PE instructions and complete compiler replay.
No analyzer database or target bytes were changed.

## Complete comparison and ownership

The entire 76,336-byte envelope `[0x004CADB0, 0x004DD7E0)` matches with zero
byte differences after all 2,805 relocations are replayed: 1,148 REL32 calls
across 31 targets and 1,657 DIR32 relocations. Fourteen tables contain 151
destination words and 683 byte indices, including their original alignment.
The three primary maps cover 0–226, 301–526 and 541–770; direct cases include
300, 540, 795, 797 and 798.

The physical code extent `[0x004CADB0, 0x004DD2D2)` is 75,042 bytes. Raw
control flow reaches all 18,993 instructions / 74,937 owned bytes, with no
unresolved indirect exits. The owner audit is 106/106.

- Physical-code SHA-256:
  `a7d5eb49423691b16358efbb5cb857867932c230a86798f84da233fe4207eb51`.
- Complete-envelope SHA-256:
  `6ca4fc284871b25c320bfd93749f548b34b0b55122661caf137ab3efe6db138f`.

The inventory retains its 41,511-byte main span ending at `0x004D4FD6`.
The existing ownership ledger separately records 33,451 bytes in ten remote
chunks. Main exclusions total 25 bytes and remote alignment totals 80 bytes;
all 105 physical alignment bytes are compared and excluded from authored
credit. `remote_exact` is now true on the strength of the complete comparison.
The earlier exclusion correction at `0x004D2C77` and `0x004D2E17` remains:
those unreachable short jumps and following LEAs align the next loop entries.

Reproduce the result with:

```bash
WINEDEBUG=-all DISPLAY= WAYLAND_DISPLAY= scripts/repo-python scripts/build.py --unit exact-first-sakuya-action-state --compare --json
scripts/repo-python scripts/audit-giant-action-owners.py --unit exact-first-sakuya-action-state sakuya-vslot28 build/match-units/ExactFirst_SakuyaActionState.obj --json
```

Current private reports are `build/sakuya-root-work-codex/canonical.json` and
`owners.json`. The canonical comparator now composes the existing reviewed
owned-extent boundary with the complete switch-payload contract. Its scheduled
float-store check also accepts the native four-byte `FST [ESP+0x7C]` between
`CMP` and `JA` in story action 730. Ownership hashes, selector preservation and
full payload equality remain required. Focused positive/negative tests and a
fresh ordinary Marisa comparison cover these tool changes.

## Source findings and remaining interpretation

The [playbook](GIANT_ACTION_ROOT_PLAYBOOK.md#sakuya-source-shape-findings)
records the reusable source shapes: independent entry/frame guards, direct
spawn arguments, compiler-extracted remainders, separate difficulty arms and
live float/double intermediates. The final story730 correction preserves a
double row displacement and evaluates jitter plus the grouped Y base/row sum.
Changing that association moves x87 operations despite equal instruction counts.

All 95 address-taken request homes now agree. Nineteen reserve four floats;
twelve of these pass count three and leave their fourth element unwritten.
The reconstructed extents follow the native home allocation and complete replay;
original declaration spelling and the unused fourth values remain unknown.
A four-element aggregate with only three initializer expressions would silently
write an extra zero, so these packets use only the observed assignments.
The difficulty defaults in action 740 retain their native uninitialized reads.

Prior raw RTTI evidence identifies primary vtable `0x006C4914`, slot cell
`0x006C493C` pointing to this root, and type name `.?AVSakuya@@` at `0x006E8160`.
Offset-based names remain where field semantics are uncertain. The view describes
only this root's observed accesses and does not establish the complete class.
