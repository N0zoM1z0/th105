# Network client snapshot import

The `CNetworkClient` primary vtable owns the 399-byte function at `0x44F200`.
The function imports ACK_INFO state while holding the critical section at
owner +0x25C, handles sequence changes, copies the two side queues or a local
deck, and sets the pending flag.

## Shared packet owner, November 8

The import now accepts the existing `NetworkAckInfoPacket40` instead of a
second, nonpolymorphic description of its storage. This relationship follows
the original receiver, not just matching offsets: the exact secondary
dispatcher constructs the packet at `0x44EFF1`, parses it at `0x44F006`, and
passes the same stack object through primary vtable slot +0x18 at `0x44F01F`.
The slot at `0x6C176C` resolves to `0x44F200`. The shared packet retains its
8-byte polymorphic base, two `deque<short>` members at +0x0C and +0x20, and
state fields through +0x3C. The import receiver itself remains a layout view.

Fresh pinned VC8 produces the same complete 399-byte candidate as before:
canonical candidate SHA-256
`bb0e0559ff30828bbbd9989fd0f51006ece01fa685a9a7619c6198d3911472d8`.
There are still 44 differing bytes, beginning at +106 in the sequence-byte
register. The exact secondary dispatcher and both ACK_INFO codec roots also
replay unchanged. No shared header or unrelated caller was changed.

## Full cleanup boundary

The complete 27-byte EH handler at `0x6BA5F8` and 44-byte unwind-map/FuncInfo
region at `0x6DFFDC` compare equal after their typed relocations. The single
state unwinds the four-byte scoped-lock object at frame -0x10.

The cleanup subtree is independently nonexact. Native action `0x6BA5F0`
tail-calls the 13-byte destructor at `0x401870`, which loads the wrapper pointer,
adds four and directly calls the `LeaveCriticalSection` import. The current
source destructor is seven bytes and instead tail-calls the out-of-line
`CriticalSectionWrapper::leave`. The action's callee therefore has no exact
binding, even though its guard offset agrees. Matching handler and metadata
do not close that difference or the main-body mismatch.

Evidence: `.analysis/frontier-network-snapshot-owner-20261108/check-context.py`
and `build/frontier-network-snapshot-owner-20261108/` contain the source/compiler
provenance, full body and metadata results, target dispatch edge checks, and
three exact witness comparisons. This checkpoint adds no authored exact credit.

## Lock lifetime and implementation visibility

The 7/13-byte difference is not a missing ownership operation. Native entry
stores `owner + 0x25C` in the four-byte guard before calling `enter`, then sets
the sole EH state to zero. Normal exit disables that state and calls `leave`
through the saved pointer. The unwind action uses the same guard at frame
-0x10. Both native destructor13 and current destructor7 followed by wrapper11
pass `guard.pointer + 4` once to the same `LeaveCriticalSection` import; neither
destroys the critical-section object.

One private ordinary-TU control makes the real `CriticalSectionWrapper.cpp`
implementation visible before the unchanged snapshot source. The guard
cleanup becomes exactly the native 13 bytes, and its eight-byte unwind action
and 44-byte metadata also match. However, the main function becomes 404/native399,
first differing at +16 as its frame grows by four bytes. The 27-byte handler
then differs in both frame displacements. The complete candidate CFG closes,
including its three-byte loop-alignment LEA; no bytes were omitted.

The control establishes an implementation-visibility issue, not a reason to
change the lock lifetime. It is not retained. A future source/TU reconstruction
must explain the native combination of out-of-line normal enter/leave calls
and the inlined wrapper inside the exception destructor. Do not replace the
guard with manual normal/exception cleanup or force an artificial destructor
boundary. Evidence: `build/frontier-snapshot-lock-lifetime-20261108/context.json`
and its paired private source/inspection script.
