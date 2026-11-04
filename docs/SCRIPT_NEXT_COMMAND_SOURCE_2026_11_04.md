# Script command cursor source

The game-owned `CScript::next_command` at `0x00405AC0` is now represented by
ordinary C++ over the real 20-byte checked command deque and 12-byte iterator:
return null at end; otherwise read the command, advance the iterator and
return it. The complete 104-byte native body and two calls from the exact scene
timeline loader are independently pinned in `SCRIPT_COMMAND_CURSOR_2026_10_29.md`.

The source's fresh VC8 object emits a 104-byte section, but its normal checked
iterator dereference uses a standard receiver convention. The native dereference
helper uses an internal EAX receiver. Therefore strict comparison stops at an
unqualified local helper relocation; same length is not an exact match. No
fabricated provider address, forced ABI, matched-byte count or general runtime
claim is used. The new nonvirtual declaration preserves the existing `CScript`
layout; the exact accepted dependencies are replayed separately.

This is source-present, not canonical exact. Original source spelling and the
whole-program context that produced the private helper remain unknown. Receipts:
`build/frontier-script-next-source-20261104/`.

All 89 accepted roots across the 19 affected source-dependent units replayed
exact, including the real linked script lifetime and CSV loading units. The
nonvirtual declaration changed a pinned header's hash; their source pins were updated, then both affected linked
origin proofs (script map cleanup and CSV deque copy) were rebuilt and fully
revalidated. The source comparison remains
blocked; those positive dependency proofs do not close its private ABI.
Target-independent CI passed all 1,030 tests and progress checks.
