# UDP packet slot acquisition

The later [client-sender checkpoint](NETWORK_WINSOCK_SEND_CLIENT_2026_10_16.md)
moves this definition into `src/network/NetworkWinsockSendClient.cpp` with its
real caller and release member. Its ordinary configured unit remains427/410;
that closed context now naturally recovers the observed private stack receiver
under LTCG, without matching the helper's full body. The isolated controls
below remain historical measurements, not a current claim that caller context
is still missing altogether.

## Observed identity, boundary and ABI

Only original Japanese TH10.5 v1.06a was inspected, SHA-256
`56350024879199861579c11b0e1c67b9590e10a8d40cd5996b109deec9afca7e`.
`NetworkUdpPacketHandleManager_acquire @ 417660` owns410 bytes through
RET8 at `4177F7`, SHA-256
`ffc37d12373208d75b91a5ce48359fc4247ae7a6775a05e824718ea56cbdd621`.
Raw CFG traversal reaches all125 instructions, without unowned tails,
indirect jumps, overlapping decode or escaping direct branches. Padding
isolates the body on both sides. Adjacent helper extents are not folded into
this authored boundary.

Two independently classified authored send methods call acquisition:
client `416990` at `4169AD`, and server `416B60` at `416BB5`. Both push the
output token pointer and their UDP owner+17C, then consume the EAX packet
pointer. The callee reads owner at entry stack+4 and token at+8, returning
with RET8. Its physical interface can be described as stdcall; its original
C++ source convention remains unknown. Source keeps a normal member instead
of imposing an external private-ABI facade.

The caller immediately writes protocol opcode0E or0D at packet+1C,
options+14, timeGetTime timestamp+10, endpoint+0 and copied bytes from+1D.
Native manager construction/destruction and original RTTI
`CHandleManager<NET_PACKET_UDP_BUFFER>` independently establish its game
payload specialization and0x64 layout. These facts support authored ownership
of the allocation/token policy, without classifying any new STL helpers.
See [the recovered manager lifetime](NETWORK_UDP_PACKET_POOL_2026_10_16.md).

## Complete behavior

The function acquires the manager's critical section at+48/native+4C and
retains the guard through its return or exception unwind.

When the unsigned-index free list at+38 is empty:

1. Read the fresh slot from packet deque size+14. Increment generation+44;
   if its unsigned value exceedsFFFF, assign1.
2. Write slot as the low16 bits to output+0, generation as the low16 bits to
   output+2. No additional capacity, overflow or invalid-token check is added.
3. Zero one complete0x41C-byte packet local, then push a copy into the native
   packet deque at+4. Push the address of its back element into stable pointer
   vector+18, and the output generation into unsigned vector+28.

When the free list is nonempty:

1. Read its last DWORD index, preserving both native iterator checks.
2. Increment/wrap generation and write both output words as above.
3. Pop the last free index, then write the output generation to the checked
   generation-vector element at that index. The packet and stable pointer
   remain unchanged; recycled payload is not cleared.

Both branches return the pointer stored in `slots_18.at(slot)` after releasing
the lock. The generation vector uses native `operator[]` checks; final stable
slot lookup uses `at`, including its out-of-range path. Native C++ operations
preserve the observed partial updates if a later allocation throws; no
transactional rollback is invented.

The source reuses the independently recovered `ResourceHandleToken` layout,
two unsigned16-bit fields, and the real `NetworkUdpPacketHandleManager64`
members. Packet size is0x41C: endpoint16, three DWORDs, payload1024. The new
method declaration is nonvirtual and adds no fields or vtable slots. No
assembly, byte arrays, manual iterator implementation or artificial frame
storage is introduced.

## EH and compiler context

The main body pushes handler `6BE58B`. Its full33-byte body validates the
security context, loads FuncInfo `6E4D8C` and tail-jumps to the C++ frame
handler. FuncInfo magic is19930522, with one unwind state and no catches.
Unwind map `6E4D84` contains state0 ->-1 through `6BE580`: an11-byte cleanup
derives the lock guard at enclosing EBP-430 and tail-jumps to `401870`.
These compiler chunks remain separate from the410-byte callable and receive
no new authored or exclusion credit.

The target uses an eight-byte-aligned EBP frame, stack owner and private STL
entries. The complete source is427/410 with ordinary `/O2 /GS`; all DIR32
and REL32 fields replay, with first mismatch+0 on the prologue. The target
has one visible cookie setup, whereas this candidate has separate buffer and
EH cookie setups. This motivates a bounded GS-minus control rather than a
profile claim: ordinary GS-minus387/410 still differs.

Resolved `/O2 /GL /LTCG` controls give540/410 with GS and486/410 without it.
Both naturally acquire the aligned EBP frame but keep source's ECX owner and
change native helper/inlining decisions. They are diagnostic sizes, not
canonical exact results: internal linked EH remains unsupported by the formal
linked comparator. Source, flags, tool hashes, commands, maps and disassembly
are retained privately below `.analysis/network-udp-acquire-20261016/` and
`build/network-udp-acquire-ltcg*/`. No control changes the accepted profile or
forces a register/stack ABI into the source.

The next useful evidence is original caller/TU visibility for the two real
send methods and their deque/vector operations. Do not compensate for those
compiler decisions with dummy callers, noinline, fake stdcall members or
manual GS/EH code. Exactness remains unproven; this is source-present only.

## Reproduction and working state

```bash
python3 scripts/audit-candidate-boundaries.py 0x00417660 --json
python3 scripts/build.py --unit cross-v106a-network-udp-packet-acquire --compare --json
```

Reports are `build/network-udp-acquire-boundary.json` and
`build/network-udp-packet-acquire-formal.json`. The latter's expected exit is1
with a full427-byte candidate, no unresolved relocation and a mismatch at+0.
A dedicated target-attested EH mapping is appended without modifying any
prior permission. `matches.csv` is unchanged. A fresh rebuild/comparison of the
accepted pool destructor `413820` remains98/98 after the shared nonvirtual
declaration. Local `python3 scripts/ci.py` passes all147 tests, ledger and
generated-progress checks; `git diff --check` passes. No full replay is used.

The attached IDA preflight still reports the wrong executable; no IDA analysis
is used. The typed-re request records that blocked session, while all boundary,
ABI, caller, width and EH observations above come from the hash-attested PE.
Direct Ghidra independently checks executable/program SHA, image base, entry
marker, x86 Windows compiler identity and every mapped .text byte before use.
Initial decompiler output was a hypothesis with missing private-register
types, and was not pasted as source. Accepted packet/token types, physical
stack parameters, name and complete extent were saved and checked in a fresh
read-only invocation. Logs are `build/network-udp-acquire-ghidra-inspect.log`,
`build/network-udp-acquire-ghidra-save.log` and
`build/network-udp-acquire-ghidra-readback.log`; the last ends
`NETWORK_UDP_ACQUIRE_READBACK_COMPLETE`. One process uses768MiB and two CPUs.

The original function spelling, source partition, compiler GS setting and
private entry specialization remain unknown. No aggregate cold replay or new
authored exact bytes are claimed by this source checkpoint.
