# BGM service shutdown, 004034F0

The canonical Japanese1.06a [4034F0,4036B1) callable is449 bytes, SHA256
`9ba5a1e02fb81ffaf9c0d5b6844e04c8b4d39af9994eafebe19830d60a2f3fef`.
Raw instruction/CFG traversal closes the full function and RET0; fifteen
following INT3 bytes are outside it. Exact scene shutdown41E120 tail-jumps to
this method at41E134. The target identity remains
`56350024879199861579c11b0e1c67b9590e10a8d40cd5996b109deec9afca7e`.

The function clears running+18, signals event+14 if present, and joins the two
8-byte thread handles at+00/+08 through exact414640. It closes and zeroes the
two events at+10/+14 independently. It then traverses three checked unsigned
handle lists at+88/+94/+A0, passing each handle to manager+38's release404270.
Only after all three release passes does it clear the three list containers.
It does not add a service lock, early error return or new null-handle policy.

`src/audio/BgmServiceShutdown.cpp` uses the established BattleThreadHandle
contract and real std::list<unsigned>. The manager's0x50 storage is a narrow
opaque view bounded by the next observed member, not a claim about its complete
internal class or implementation. Its ordinary release member declaration is
kept truthful. Raw404270 consumes a packed generation/index handle, performs
checked generation access under its own critical section, destroys the pointed
stream and returns the slot to a free list. That helper and full stream/Ogg
lifetime are not reconstructed or credited by this change.

First complete source replay is **449/native449, nonexact at+0**, candidate SHA
`155646a11f0a1d49cb836d33c2a6b98f697711e69f1c63fc3b204d0cbbae8791`.
The shipped function has an aligned EBP frame and private EAX manager-release
calls, while ordinary source uses its normal member ABI. No invented aligned
local, ABI declaration or padding is used to hide these differences.

Unit: exact-first-bgm-service-shutdown. Focused receipts:
`build/frontier-4034f0-20261029/{formal-build,boundary}.json`.
No shared header, compiler profile or accepted consumer changed. Source and
independent authored ownership advance; exact totals do not.
