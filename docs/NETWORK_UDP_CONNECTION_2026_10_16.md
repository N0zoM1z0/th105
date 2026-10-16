# UDP connection and handshake-worker link closure

The critical receive/connection chain now has all genuine implementation
inputs for a resolved mixed COFF/LTCG link. This checkpoint adds complete
connection542 and worker1009 source to `NetworkWinsockReceiveThread.cpp`.
It adds no canonical authored exact bytes.

## Observed target and boundaries

Only original Japanese1.06a SHA-256
`56350024879199861579c11b0e1c67b9590e10a8d40cd5996b109deec9afca7e`
is used. IDA still reports another executable and is not used. Raw PE CFG
audits close both bodies without missing bytes, external tails, indirect
jumps, invalid decoding or overlap:

| Entry | Instructions / bytes | Native ABI | Full body SHA-256 |
| --- | --- | --- | --- |
| `415340` |160 /542| ECX owner; endpoint, port, packet, size in four stack slots; AL0/1; RET16 |`5adc2f59eba3c9831a6813a1bf82cfe0e803ae2e9db354c558524d6f83089b3b`|
| `415D60` |286 /1009| stdcall handoff pointer at stack4; EAX0; RET4 |`96a7f05395f2e1d7f83cc661e6448e87ba2688726fbe50acc4a751f5d24383f5`|

Connection has normal calls from receive `41DBD6` and the independently exact
MenuConnect finalizer `4426F2`. The latter supplies a40-byte ConnectPacket40;
the former passes null endpoint/data and the FFFF reuse sentinel. Connection
registers worker415D60 at `4154EB` through the real8-byte native thread owner
and its separately accepted `414600` start implementation. These caller,
protocol, state and ownership operations establish authored provenance for
both entries; no generated container/helper gains new exclusion credit.

## Connection behavior

Before locking, a nonnull worker handle is queried with GetExitCodeThread;
exit code259 rejects another start. The API result is discarded and its local
output is not initialized by the target. Under the endpoint wrapper+E0/native
E4 scoped lock, state2 or3 rejects the operation.

For size below FFFF, free any old CRT allocation+78, publish WORD size+7C,
allocate/copy a nonempty replacement or clear the pointer for zero size. FFFF
preserves both old fields. No allocation-failure recovery is invented. A16-byte
stack handoff stores owner+0, WORD size+4, data pointer+8 and DWORD copied+C;
the unused two bytes following size remain untouched.

A nonnull endpoint writes AF_INET and htons(port) to owner+A0/A2, then tries
inet_addr. Result FFFFFFFF uses gethostbyname and its first address; null host
or null first address rejects the operation. No extra h_addr_list null guard,
address-family check or rollback is added. A null endpoint retains the existing
A0 address, as required by the real receive retry caller.

Copy all16 endpoint bytes into published+3C and previous+4C, clear the native
candidate vector+14C and push the retained/resolved endpoint. Publish state2,
start415D60 with the stack handoff and poll its copied DWORD through16ms waits
on the stored worker handle. Start's bool result is discarded; the target has
no separate failure exit. The endpoint guard remains held until acknowledgement
and success return. The worker copies the handoff before trying that lock.

Connection prologue points to the complete27-byte handler `6BE158`, SHA-256
`bdcc78d85c1ef9c87c7a30a484b78603f7859d057dc8c7da8c0ab1b69ba6de55`.
Its FuncInfo `6E488C` has magic19930522, one unwind state, map `6E4884` and
flags1. State0 unwinds to-1 through the8-byte cleanup `6BE150`, which derives
the guard at EBP-0x24 and tail-calls its real destructor. Main RETs are41553D
and41555B. The ordinary source lacks the target's aligned EBP frame and remains
524/542 nonexact, first differing at entry.

## Worker behavior

Capture the native worker handle before acknowledgement. Build opcode5 with
key16 at+1, owner WORD24 at+11, low byte of peer limit11C at+13, WORD payload
size at+15 and copied data at+19. Holes+14/+17/+18 remain untouched. Its
transmitted length is25+WORD size. Only after copying this data, store DWORD1
at handoff+C (`415E1D`); the main function can then release its stack handoff.

Create a separate UDP socket with AF_INET/SOCK_DGRAM/protocol0. Its zeroed
local endpoint uses htonl(0) and port
`htons((unsigned short)timeGetTime() %1000 +11000)`. The target import is
WINMM timeGetTime at6C0258, not GetTickCount. A negative bind result closes
the socket immediately; only a successfully bound auxiliary socket is used
or closed at final cleanup. Socket failure does not abort the handshake.

Reset candidate index+148. An empty candidate vector skips the loop. Otherwise
publish candidate0 to+3C, then take/release the endpoint lock manually on every
iteration, with no EH guard added:

| State | Observed policy |
| --- | --- |
|2| Send37-byte opcode1 with both endpoints=published and port0 through the main socket, and through the bound auxiliary socket when available. Replace the first endpoint with previous+4C; send main-socket probes to that previous address with port0, then owner WORD24+probe counter, then ntohs(local auxiliary port)+counter when auxiliary bind succeeded. The second endpoint stays published. Signed `probe_count++ >32` advances candidate index; exhaustion sets state6, otherwise reset count and copy the next checked native vector entry. Reset the request retry counter. |
|3| Send the prepared opcode5 request through the main socket to published+3C. Signed `request_count++ >100` sets state6. Reset the probe counter. |
|other| Clear the loop flag. |

If running+74 is zero, set state6 after the state-specific work. Unlock, wait
128ms on the captured worker handle, then check the loop flag. Thus state6
publication does not itself skip the current wait or the next state check.
The37-byte probe has a WORD at+21 and two untouched tail bytes+23/+24.
The worker returns zero after closing only a successfully bound auxiliary
socket. Its sole RET4 is41614E; it has GS protection and no EH frame.

## Source inference and storage unknowns

Normal C++ thiscall and stdcall signatures explain the physical entries.
Source char versus bool spelling for connection is not uniquely determined by
AL0/1; the existing actual caller contract uses char and is preserved. Packed
wire views, native vector operations, scoped connection lock and manual worker
locks follow the target. No volatile flag, failure recovery or additional
packet initialization is introduced without evidence.

Selected source uses only the observed37-byte probe and65-byte request
(25-byte header plus the only fresh caller's40-byte payload). Original stack
capacity remains unknown. The worker's two packet addresses are420 apart;
this new independent observation justified one control using two genuine
NetworkUdpPacketBuffer41C objects with views into their1024-byte payloads.
That control is992/1009, frame860 versus target870, and is not selected.
No16-byte padding or larger guessed packet is added to make the frame agree.
Selected ordinary worker source is945/1009, first mismatch on the frame size.

## Genuine linked control and verification

The private reproducible recipe
`.analysis/network-udp-connection-20261016/probe-linked.py` compiles the full
receive/request/connection/worker TU with pinned VC8 `/O2 /GL /GS /EHsc` and
links actual ordinary COFF implementations from NetworkWinsockPeerRemoval,
NetworkWinsockAccept and BattleThreadHandleRuntime, plus pinned runtime and
WS2_32 import libraries. Calls use the actual existing class declarations;
there are no substitute bodies, executable ABS symbols or `/FORCE`.
Only attested nonexecutable data/IAT bindings are absolute link inputs.

The link succeeds with zero unresolved implementations. Connection is also
exported to preserve its real external UI call surface; without that visibility
an exploratory link specialized it to the receive caller's FFFF/null arguments
and eliminated real DNS/copy behavior. The corrected diagnostic retains the
complete542-byte connection body; worker is948 bytes. These lengths are not
canonical exact claims. The main receive map extent also contains switch
metadata, so its map extent is not an accepted callable boundary.

The configured ordinary unit compares all seven functions. The previously
accepted callback remains14/14 exact. The148/33 dependency controls remain
exact in origin review, without authored/source/exclusion credit. Receive,
request, connection and worker remain nonexact. The fully linked callback is
also a14-byte canonical diagnostic; native EH/GS data ownership and switch
metadata currently prevent canonical large-root acceptance.

Reproduce the focused build and comparisons:

```bash
python3 scripts/audit-candidate-boundaries.py 0x00415340 0x00415D60 --json
python3 scripts/build.py --unit cross-v106a-network-winsock-receive-thread --json
python3 scripts/compare-unit-object.py cross-v106a-network-winsock-receive-thread build/match-units/CrossV106a_NetworkWinsockReceiveThread.obj --json
python3 scripts/compare-unit-object.py cross-v106a-network-winsock-receive-thread build/match-units/CrossV106a_NetworkWinsockReceiveThread.obj --address 0x0041D7B0 --json
python3 .analysis/network-udp-connection-20261016/probe-linked.py
```

Fresh reports are `build/network-udp-connection-{boundary,facts,build,formal,accepted}.json`,
the worker-boundary/known-packet-comparison reports, and
`build/network-udp-connection-ltcg-probe.diagnosis.json` with exact tool/source
hashes and commands. The direct Ghidra save and separate readback re-attest
the executable, mapped .text, entry, x86 Windows language and both complete
bodies; owner/handoff types and physical argument/return storage are saved.
Decompiler locals and imported prototypes remain hypotheses; raw bytes decide
the packet offsets, handle capture, acknowledgement and loop lifetimes.
