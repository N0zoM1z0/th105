# Command gates read the real PAT groups

Command lookup now uses `std::map<int, PatGroup *>`, the same type written by
Fighter's PAT loader and read by animation sequence selection. This replaces the
undefined `CommandGateTree::lower_bound` facade and its manually copied node,
iterator and entry layouts. The original helper at `0x45C320` is `find`, not
`lower_bound`: after the signed traversal, `0x45C35C..0x45C35F` rejects a greater
key and returns the end iterator. The real VC8 specialization reproduces all
105 bytes, including that rejection.

## Target evidence

The 78-byte lookup at `0x493D40` sign-extends its short key, loads the map pointer
from Fighter `+0x160`, calls `0x45C320`, performs the checked iterator access,
and returns the short at the selected group's `+0x10`. The 950-byte front-card
gate at `0x494450` performs the same lookup for keys 690, 691 and 695. All four
calls and both complete reader bodies are checked against the pinned Japanese
1.06a target. `find`'s existing compiler-generated classification is unchanged.

The unchanged PAT loader at `0x461B70` supplies the ownership evidence. It reads
the same `+0x160` map at `0x461DDF`, inserts the selected `PatGroup` pointer through
`0x4606E0` at `0x461F26`, then reads two file bytes into that group's `+0x10` at
`0x462147..0x462150`. This is the shared `PatGroup::field_10`, not a separately
allocated command-gate record. The public field name remains conservative.

## Build repair and complete comparison

The original worktree could not compile `CommandGates.cpp`: it still referenced
`state_13c` and `y_component_f8`, which had already become `action_id_13c` and
`y_velocity_f8` in the shared Fighter layout. Those references are corrected.
A private baseline makes only these two name corrections, retaining the old
facade, to isolate the subsequent container change.

All three affected units compile. Their ten accepted roots reproduce all 2,349
bytes. Every complete root, including the nonexact front-card gate, is identical
to that repaired baseline after resolving the real helper symbol. The latter
remains 950/950 with its first difference at `+72`; this work adds no authored
exact credit. Each object retains all 72 existing non-debug sections and adds
22 ordinary STL code sections. No new RTTI or EH sections are introduced.

An initial candidate retained a checked iterator across the front-card policy
and changed register allocation from `+4`. Keeping the actual `PatGroup *`
after the checked lookup restores the previous complete 950-byte candidate.
There was no register/flag search or change to its known residual.

`CommandGates.hpp` has only this source consumer, and public Fighter signatures
are unchanged. Validation is limited to the three actual units, complete roots,
helper body, and supporting target data flow. No source pins change.

Lightweight CI and the staged diff check pass before the local checkpoint.
