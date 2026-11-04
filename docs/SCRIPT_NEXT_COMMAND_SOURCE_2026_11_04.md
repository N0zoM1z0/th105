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

## Genuine CIL execution, 2026-11-04

A new truthful CIL diagnostic emits a 156-byte root with the checked deque
dereference inlined. It compares nonexact against the native 104-byte root at
+28; the normal standalone unit remains blocked at the unqualified helper.
`scripts/audit-script-next-command-real-cil.py` executes the complete native
root and its actual dereference helper alongside the linked source root on
seven valid fixtures, including empty/end cursors and block-map wraparound.
Both agree with an independent cursor/result model; repeated reads also run
through exhaustion across an ordinary block and a wraparound boundary. A
modified increment is detected. These valid fixtures do not test allocation, actual script parsing, exceptions
or full-game behavior and do not add exact credit. Invalid iterator boundary
observations are described below.


## Checked-iterator boundary observations, 2026-11-04

The genuine native/helper and linked-source observer now also stops immediately
at each image's own invalid-parameter handler entry. For a cursor beyond the
end, an empty deque with a nonzero cursor, and a null iterator owner, both
images reach that boundary before changing the cursor. The handler itself is
not executed, so no termination, exception, or recovery behavior is claimed.
A separate deliberately invalid cursor immediately before the deque's start
is *not* rejected on these observed paths: both images read its mapped slot
and increment it. This is a bounded observation, not permission to use an
invalid iterator or a general memory-safety claim. The exact match status and
private ABI limitation are unchanged.
