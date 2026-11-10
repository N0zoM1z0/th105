# Fighter scripted-input origin, JP 1.06a

The pinned original body at `0x463E40` spans 753 bytes (SHA-256 `f4fc93f5a85590424dd4f614584f07b853b9541eeeeeffbb58915e3d20fabddc`). Its decoded body implements the game-specific fighter input snapshot, state dispatch, deque history and probability policy described in `KNOWLEDGE_BASE.md`. The boundary audit covers all 753 bytes and identifies one indirect virtual tail jump; it does not by itself prove that destination's ownership.

Two independently canonical-exact callers replayed in this checkpoint: round
initialization at `0x470BC0` (306 bytes) calls the target at `0x470C02` and
`0x470C0A`; pre-reset at `0x472230` (314 bytes) calls it at `0x472272` and
`0x47227A`. These body and edge anchors establish authored game ownership.

The typed source retained in private analysis is now selected as `src/battle/FighterScriptedInputRuntime.cpp`. It models the actual signed-short history deque, six button fields, snapshot/timer policy, virtual mode dispatch and game selector. Existing exact helpers and target relocation addresses are bound in `exact-first-fighter-scripted-input`. Fresh whole-body comparison is 760/native753 bytes, first mismatch at offset 1; the original TU/compiler context remains unresolved. The input sampler and CPU selector now call the existing real `FighterInputRuntimeView` and `FighterCpuInputRuntimeView` implementations; their 480/480 and 171/171 exact bodies replay. Other system-level dependencies mean a complete link is not claimed. Source-present credit is recorded, but no canonical exact credit.

## Native probability and snapshot order

The target branches directly from each random threshold to the common clear/return
path; representing that policy directly removes the extra temporary boolean. The
snapshot timer is published before the vertical snapshot, as the native body does.
Together, these target-backed changes produce 753/native753 bytes and only two
unequal canonical bytes at `+0x22` and `+0x2F`: VC8 uses ECX rather than EDX for the
same horizontal input multiplication. Reversing the multiplication operands is
byte-neutral. At that checkpoint no register forcing or exact credit was claimed;
the later result below supersedes it.

## Exact direction tests, 2026-11-03

Expressing the two independent horizontal-direction tests directly as
`horizontal_6b4 * facing_104 > 0` and `< 0`, instead of introducing a named product,
naturally reproduces the target register allocation without forced registers or
synthetic liveness. Neither field is modified between the tests. The complete
bounded function now compares exactly, 753/753, SHA-256
`f4fc93f5a85590424dd4f614584f07b853b9541eeeeeffbb58915e3d20fabddc`. Both exact
caller bodies and their four original edges replay; the real input and CPU provider
bodies also remain exact. The indirect virtual tail remains outside the ownership
proof and integrated linking is not claimed.
