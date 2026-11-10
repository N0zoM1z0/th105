# Character stage and BGM maps use a real find provider

The two 72-byte lookups at `43C0B0` and `43C100` now use ordinary
`map<int, unsigned char>::find` and share their declarations with the bootstrap
writer. This replaces hand-written tree/iterator layouts and a declared but
unimplemented `lower_bound` member. Both wrappers and the actual emitted
105-byte find provider match the original target completely.

## Native operation and objects

This pass inspected raw Japanese 1.06a PE bytes, SHA-256
`56350024879199861579c11b0e1c67b9590e10a8d40cd5996b109deec9afca7e`.
The shared callee is `45C320`. Its first walk finds the lower bound, but it then
compares the requested signed DWORD with the candidate's key at `45C35C`.
The JL at `45C35F` rejects a greater candidate and selects the end node at
`45C367`. That final equality check makes this find, not lower_bound alone.
Both wrappers validate the iterator and return the mapped byte at node +10.

The stage receiver is `6FC60C`; the BGM receiver is `6FCA3C`. Bootstrap
`43E2E0` inserts fifteen character mappings into each, all through `4606E0`.
`CharacterPolicyMaps.hpp` now gives readers and writer the same real container
and global declarations. Its signed int keys and unsigned byte values agree
with the actual comparisons and loads. Historical relocation aliases remain
unused and are labeled accordingly.

The native direct-call census contains three stage calls, at `4709C2`,
`47318E`, and `4737F2`, and four BGM calls, at `4709D1`, `473180`, `47319A`,
and `473801`. Each is a decoded instruction in the complete battle-transition
or Arcade setup/finalization body. The public signatures and both canonical
wrapper bodies are unchanged, so these callers require no source changes.

## Focused verification

The two affected units were rebuilt with the pinned VC8 profile. Both lookup
roots remain 72/72 after every relocation is resolved. The generated find has
no relocations and matches all 105 bytes through RET8, including its rejection
branch. The bootstrap's 348 non-debug sections, relocations and SafeSEH list
remain unchanged; its existing full-body mismatch at +863 remains unresolved.

Tracking and lightweight CI pass. No authored exact count changes: the wrappers were
already counted and find is generated container machinery.
