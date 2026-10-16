# UDP probe and timeout worker

## Observed target, registration and boundary

The original Japanese TH10.5 v1.06a executable has SHA-256
`56350024879199861579c11b0e1c67b9590e10a8d40cd5996b109deec9afca7e`.
`NetworkWinsock_probe_thread_entry @ 00416F40` owns692 bytes through RET4 at
4171F1. Body SHA-256 is
`32a4bac3ae247113a2a9e87691983eb8af62126ceaa2a007e38a24ea1e5cabc4`.
Raw CFG traversal reaches201 instructions /682 bytes, with no indirect jump,
escaped direct edge, overlap or invalid decode. The only skipped range,
417046..41704F, is two alignment LEAs (`8da424000000008d4900`) before the
second peer loop. Those ten bytes remain part of the complete main extent.
INT3 padding separates the preceding and following functions.

The reviewed initializer412E10 loads native CreateThread from IAT6C0138 at
412F59. Its third thread setup at412FA6 pushes this callback, passes the UDP
owner, uses zero creation flags, stores the thread id at owner+70 and records
the returned handle at+6C. The callback independently reads its sole DWORD
parameter from EBP+8, returns EAX0 and pops four bytes. This is an ordinary
Win32 stdcall thread entry, with no private register interface to invent.

## Complete recovered behavior

`src/network/NetworkWinsockProbeThread.cpp` defines the initializer's existing
`network_udp_service_thread_416f40` symbol. Its method-specific owner view
uses the reviewed native vector and28-byte critical-section wrappers, and
asserts every selected owner offset and the32-byte peer width. It does not
change a shared header or another accepted source unit.

The target performs these operations in order:

1. Create an unnamed, initially nonsignaled auto-reset event and retain its
   handle locally. Store packet opcode4 once. Do this even when running+74
   is initially zero; no new API-error branch is added.
2. While running, snapshot active count+118 and compute the unsigned wait
   duration `500 / (active + 1) + 1`. Start the report DWORD at zero when
   limit+11C is below active, otherwise at limit minus active. Under peer
   critical section+124, iterate the dynamically reloaded vector count;
   for each peer whose signed slot+10 is not-1, add its DWORD+1C. The
   arithmetic wraps as unsigned32-bit arithmetic. Release the lock.
3. Iterate the current vector count again. Lock+124 separately for every
   slot and preserve the three checked vector accesses on the active path.
   Send five bytes, opcode4 followed by the unaligned little-endian report
   DWORD, to the active peer's16-byte endpoint. Ignore the send result.
   Postincrement its counter+14; if the old value was at least10, call the
   real peer removal413170 while still holding the recursive critical
   section. Release the lock, then wait on the local event for the computed
   duration. Inactive slots only release the lock and skip that wait.
4. Under native endpoint critical section+E4, when state+144 is zero, send
   the same five bytes to primary endpoint+C0. Postincrement counter+D4;
   if its old value was at least10, set state+144 to6. Release the lock and
   always perform one more timed wait. Check running only at the outer
   continuation; do not add cancellation checks inside either peer loop.
5. Close the local event and return zero, including when the outer loop
   never ran. The event is separate from the send worker's owner+1E0 event;
   this routine neither publishes nor signals its local handle.

There are five checked peer-vector accesses in total: two in the accumulation
loop and three in the send/counter loop. Vector begin/end are owner+10C/+110,
with32-byte elements and the native proxy at+108. Receive opcode4 independently
writes peer+1C and clears its counter+14 at41D8C7..41D8DF; the matching-primary
path writes owner+DC and clears+D4 at41D918..41D92B. This corroborates report
feedback and probe-counter roles. The precise meaning of the report value,
limit+11C and state values remains provisional; source names do not establish
a protocol specification.

## Source controls and remaining frame question

The selected ordinary VC8 `/O2 /GS` source uses only the five transmitted
bytes. It emits664 bytes against the692-byte target, with every selected
COFF relocation resolved. The first difference is the frame prologue:
source reserves14 bytes without aligned EBP; target aligns ESP to eight,
reserves434 bytes and stores its GS cookie at frame+430. Source additionally
keeps the report in a scalar through accumulation, then serializes it into
the five-byte message. Target writes and accumulates directly in its local
packet payload. Original local type/capacity, lifetime and TU context remain
unknown. No buffer enlargement or inert local is used to fit the frame.

A separate control reuses the genuine RTTI-backed `NetworkUdpPacketBuffer41C`
type and its payload+1C. It emits670 bytes with a428-byte frame and still
has no aligned EBP frame. Pool storage establishes that type elsewhere; it
does not establish that this callback used the same local type.

Both controls also compile with `/GL` and complete genuine `/LTCG
/NODEFAULTLIB` links against the actual ordinary-COFF
`NetworkWinsockPeerRemoval.cpp`, pinned VC8 runtime/WS2_32 libraries and
attested data/IAT bindings. The source calls the actual peer-removal view;
there is no synthetic callee, executable ABS binding, stub or forced
unresolved link. These resolved controls retain664/670-byte RET4 bodies and
the same unaligned frame shapes. Function extents alone establish their
nonexactness. They are diagnostic controls, not accepted linked match units
or a full canonical replay of their native CRT GS global. No backend or
comparison permission changes are needed. These results explain neither
the target frame nor its original storage ownership, and do not prove that
LTCG is required.

## Reproduction and saved analysis

```bash
python3 scripts/audit-candidate-boundaries.py 0x00416F40 --json
python3 scripts/build.py --unit cross-v106a-network-winsock-probe-thread --json
python3 scripts/compare-unit-object.py cross-v106a-network-winsock-probe-thread build/match-units/CrossV106a_NetworkWinsockProbeThread.obj --json
```

The boundary audit reports the ten skipped alignment bytes; the private
hash-attested driver `.analysis/network-udp-service-20261016/audit.py` checks
their exact form, native callback registration/imports and complete CFG.
Its packet is `build/network-udp-service-facts.json`. The strict whole-function
comparison intentionally returns1 for664/692 nonexact. Fresh build provenance
is independently checked against the current source/object hashes and unit
input digest. Reports are `build/network-udp-service-{build,formal}.json`.
The known-type COFF control is
`build/network-udp-service-known-packet-compare.json`; resolved-link extent
results are `build/network-udp-service-linked-comparisons.json`, with commands,
tool pins, source hashes and data bindings in the two
`build/network-udp-service-linked-*.diagnosis.json` files. Private control
source/scripts remain under `.analysis/network-udp-service-20261016/`.

The origin rule pins the full692-byte hash, callback operand, CreateThread
IAT load, event IATs, real removal call and native sendto thunk IAT operand.
One game function moves from review to authored/source-present, with no
new exact credit or compiler/library exclusion. No accepted unit shares a
changed source/header/flag, so verification is limited to this new unit.

IDA preflight identifies a different executable and is not used for analysis.
Direct Ghidra independently attests executable/program SHA, base, entry
marker, x86 Windows identity and all mapped .text bytes. The initial project
has no function object at416F40; a bounded function is created after raw
boundary reconciliation. Owner/peer/vector/critical-section types, complete
692-byte body, ordinary stdcall owner parameter, four-byte stack pop and
32-bit return are saved and checked in a fresh read-only invocation. The
earlier decompiler's aligned-stack aliases and untyped sendto-thunk calls
misrepresent local values, so the raw instructions determine behavior.
Logs are `build/network-udp-service-ghidra-{inspect,save,readback}.log`.
Only one Ghidra process runs at a time with768MiB heap/two CPUs.
