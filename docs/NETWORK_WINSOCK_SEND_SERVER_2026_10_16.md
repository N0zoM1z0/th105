# UDP server sender and peer-record access

## Observed target and full boundary

Only original Japanese TH10.5 v1.06a was inspected, SHA-256
`56350024879199861579c11b0e1c67b9590e10a8d40cd5996b109deec9afca7e`.
`NetworkWinsock_send_server @ 416B60` has548 bytes,168 reached instructions,
and body SHA-256
`f9c4811900e4c22873f2176f36dd601d1e2fc4782308c183d1c9c863a7e8d3f9`.
The complete raw CFG closes at RET20 `416D81`, without indirect jumps,
escaping direct branches, overlapping decode or uncovered tails. Its entry
immediately follows the separate client's RET16; prior origin-rule prose
incorrectly described preceding INT3 padding. The independent incoming E8
edges and closed prologue/epilogue establish this boundary. Existing
authored ownership already pins six exact caller sites in five Server methods;
the candidate-local direct-call census also finds four sites in two unreviewed
methods. These extra callers are leads only and gain no source/origin credit.

The physical interface is ECX=UDP owner and five DWORD stack arguments:
peer index, payload pointer, byte count, options and optional result-token
pointer. Exact wrapper `44F4E0` serializes into its buffer and passes the packet
result field; the other exact wrappers likewise establish index/buffer/size/
options/result positions. Raw callee stack accesses independently confirm all
five and the20-byte pop.

## Return uncertainty

The inactive-slot path branches directly to the epilogue while EAX still holds
the vector begin pointer. The active path ends with SetEvent's incidental EAX.
No uniform authored return value is established. Most reviewed call sites
discard or overwrite EAX; one exact forwarding wrapper simply preserves it.
Prior source `int` declarations do not prove a result contract.

The new source therefore uses a void method and a bare inactive-path return,
without manufacturing a status value or an incomplete nonvoid return. This
is a source-level hypothesis, not recovery of the original spelling or proof
that no later caller observes the incidental register. The target ABI, full
side effects and this remaining return-type uncertainty are recorded separately.

## Complete behavior and native layout

`src/network/NetworkWinsockSendClient.cpp` now contains both senders and the
complete acquire/release member definitions. Its method-focused CNetworkUDP
view replaces the formerly opaque+FC..168 region with an untouched12-byte
prefix, native peer-record vector+108, untouched+118 bytes, critical wrapper
+120 and untouched+13C bytes. Existing token deque+168, packet manager+17C,
event+1E0 and queue lock+1E4 keep their offsets. Compile-time assertions pin
the32-byte peer element, vector+108 and lock+120 as well as earlier offsets.
The view reaches+200; the full known owner remains0x314 bytes elsewhere.

The reconstructed server method follows these observed operations:

1. Check `records_108[index].slot_10` using native checked vector access.
   If it is-1, return before packet allocation, output-token writes, locking,
   queue mutation or event signaling. No new out-of-range early return is added.
2. Initialize a packed token to zero, acquire a packet from manager+17C,
   write opcode0D at payload+1C, copy options+14 and record timeGetTime+10.
3. Enter the peer lock's native critical section at+124. Perform the second
   checked vector access after locking and copy all16 endpoint bytes. Leave
   that lock. The first record access is intentionally outside this lock;
   no source synchronization change is invented.
4. Copy caller bytes to packet+1D, store byte count+1 at+18, and enter the
   queue lock's native critical section at+1E8.
5. If result is nonnull, traverse the native checked token deque. Test token
   equality before the running+74 early stop. On a match, release the old
   pool token, erase its iterator and stop. Publish the new token whether or
   not a match was found. Append the new token, leave the queue lock and
   signal event+1E0.

The peer view names only endpoint16 and signed slot+10; the final12 bytes
remain unreviewed here. The token deque uses actual native iterators and
repeated end checks. Both locks use explicit Win32 calls, as in the target;
no EH guard, transactional rollback or payload-capacity check is added.

## Complete comparison and real caller context

The smallest ordinary `/O2 /GS` probe is **548/548 nonexact**, with first
difference+42 at the private acquire call setup. All relocations resolve.
Identical size alone is not accepted: target acquisition receives owner on
the stack, whereas the standalone member call uses ECX.

The formal mixed COFF/LTCG unit now exports both actual senders. Complete
source definitions let the compiler naturally recover the private stack
acquire and EAX release interfaces. The native unsigned-list instantiation
remains unchanged and receives no authored credit. Full canonical results are:

| Address | Source/target bytes | Result |
| --- | ---: | --- |
| `416990` client sender | 561/464 | Nonexact, first difference+A2 |
| `416B60` server sender | 644/548 | Nonexact, first difference+3D |
| `405200` shared release | 167/167 | Exact, with its actual client caller witness |

The server's first difference is the inactive-branch displacement to its
larger epilogue, not an unresolved relocation. Token push_back remains expanded
in the linked senders instead of the target's out-of-line helper. Original
inline/TU context and register choices remain open. No fake caller, register
ABI facade, noinline annotation or partial match is added to remove them.
The separate ordinary acquire unit remains427/410 nonexact.

```bash
python3 scripts/audit-candidate-boundaries.py 0x00416B60 --json
python3 scripts/build.py --unit cross-v106a-network-winsock-send-client --json
python3 scripts/compare-linked-unit.py cross-v106a-network-winsock-send-client --json
python3 scripts/compare-linked-unit.py cross-v106a-network-winsock-send-client --address 0x00405200 --json
```

Reports are `build/network-udp-send-server-boundary.json`,
`build/network-udp-send-server-callers.json`,
`build/network-udp-send-server-coff-comparison.json`,
`build/network-udp-send-pair-formal.json` and `build/handle-manager-release-formal.json`.
The full mixed comparison intentionally returns1 because both senders remain
nonexact. Selecting only the accepted release repeats the source/target caller
CFG and unique E8 checks. This checkpoint changes no matches or exclusion rows.

After the source/TU/export change, a fresh build and accepted-only dispatcher
retain the sole affected accepted function at167/167, recorded in
`build/network-udp-send-server-accepted-dispatch.json`. The ordinary acquire
probe remains427/410 with all relocations resolved. Local
`python3 scripts/ci.py` passes all151 tests and generated-progress checks;
`git diff --check` passes.

## Analysis state

IDA preflight still reports a different executable, so no IDA analysis is used.
All exact observations above come from the hash-attested PE. Direct Ghidra
independently attests executable/program SHA, base, entry marker, x86 Windows
identity and every mapped .text byte. Its initial decompiler output misnames
stack values across an untyped memcpy boundary; raw instructions determine the
five-argument contract and both peer checks instead. The peer/owner views,
supported name, complete extent, physical parameter storage and explicitly
provisional void return are saved and checked in a fresh read-only invocation.
Logs are `build/network-udp-send-server-ghidra-{inspect,save,readback}.log`.
One Ghidra process uses768MiB and two CPUs; private probes stay below `.analysis/`
and `build/`. No whole-program exact replay is performed.
