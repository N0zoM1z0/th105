# UDP initialization and native worker ownership

## Observed target boundary and callers

The original Japanese TH10.5 v1.06a target has SHA-256
`56350024879199861579c11b0e1c67b9590e10a8d40cd5996b109deec9afca7e`.
`NetworkWinsock_initialize_udp @ 00412E10` has149 instructions /441 bytes,
all reached by raw CFG traversal. Three RET8 exits, no indirect jump, no
escaped branch or remote chunk, and surrounding INT3 padding establish its
complete main boundary. Body SHA-256 is
`e1f2b573d83afe2ba21e29b92e87702aad50aad9427e80f24ea90b02d394a686`.

Two independently canonical-exact MenuConnect methods call this entry:
442530 at4425AF and4425D0 at442652. ECX supplies their UDP subobject at+3B4;
two DWORD stack slots supply the16-byte connection-key pointer and port.
The raw entry independently reads those slots and all exits pop eight bytes.
Only AL0/1 is established. Source uses bool; original bool/char spelling is
unknown. The earlier UI int declaration merely forwards full EAX in one
wrapper and does not prove a meaningful upper24-bit return contract. That
shared header is left for a complete consumer/return review.

## Complete recovered behavior

`src/network/NetworkWinsockRuntime.cpp` contains the full initializer and its
real socket-bind helper alongside the already exact Winsock lifetime/error
functions. The method-focused owner view names only supported fields, with
native vector/deque/thread storage and compile-time offset/element assertions.
It reaches+17C; the separately reviewed full CNetworkUDP owner remains314
bytes. Original class spelling and TU partition are not recovered here.

The source preserves these target operations in order:

1. Set state+144 to1 and the peer limit+11C to16. Assign
   sixteen32-byte peer records, initializing only signed slot+10 to-1.
   Endpoint and remaining bytes are left untouched in the local value, as
   observed; no blanket zero initialization is invented. Clear active count+118.
2. Copy the four-DWORD key to owner+4, then copy it again to owner+14.
   Acquire the process-wide Winsock runtime through exact41DDC0. On failure,
   return false without socket creation or later cleanup/thread operations.
3. Store `socket(AF_INET, SOCK_DGRAM, 0)` at+28. On INVALID_SOCKET, report
   the exact CP932 socket-error text and release the runtime reference before
   returning false. The source's real release call naturally inlines here,
   including reuse of zero/one constants already live in the caller.
4. Call the private bind routine413080. On failure, call exact41DEC0 and
   return false. No new socket close or address clearing is added to this path.
5. Free a nonnull prior buffer+78 and clear its pointer. Set running+74 and
   call the native token deque's clear operation at+168. The observed413A90
   callee releases the deque's storage as well as emptying its elements.
6. For each thread wrapper+5C/+64/+6C, first call exact wait-for-exit414640,
   then create a native thread with the UDP owner, zero flags, null security
   and zero stack-size arguments, and wrapper+4 as thread-id destination.
   Store each returned handle. Entry points are416D90,41D7B0 and416F40.
   Set the first two priorities to15, including when creation returns null;
   the third has no priority call here. No new API-error guard is inserted.

The source key is a16-byte value and the peer is a32-byte POD; its only
initialized local field is slot+10. Active-count meaning is independently
corroborated by reviewed peer removal413170. Request415560 subsequently compares active count+118 with+11C before
allocating a peer, establishing the limit role independently of this initial
constant. The source field is now named `peer_limit_11c`.

## Actual private interfaces and source controls

The complete120-byte peer assignment callee4139D0 receives its record pointer
in EDX and vector pointer on the stack, copies32 bytes, erases the old range,
then inserts sixteen values. Its native insertion callee independently has
constant16. This supports `peers.assign(16, value)` semantics; original
template/TU specialization and its private boundary remain unknown. No new
compiler/library exclusion or authored credit is assigned to these callees.

The complete68-byte bind routine413080 receives owner in ECX and port in EAX,
with no stack parameters. It writes AF_INET at owner+2C, converts the port
through htons, writes INADDR_ANY and binds the complete16-byte address. Its
padding bytes are retained. SOCKET_ERROR reports the original CP932 bind text
and returns AL0; success returns AL1. Every caller of the shared error reporter
discards incidental EAX, so no fabricated status value is introduced there.

The initial user-constructor/temporary peer control produced398 bytes without
a GS cookie. The explicit POD local, with only slot initialized, produces the
observed GS protection and442 bytes. Public/private member-access controls for
bind are byte-neutral apart from symbol spelling: their76-byte ordinary
member still loads/pops a conventional stack port parameter. These controls
are evidence about this source shape, not a general GS or compiler recipe.

A complete file-local `static bool __stdcall` bind definition and its actual
initialization caller naturally produce the target ECX/EAX private interface.
The whole helper is68/68 in a diagnostic canonical comparison, and the
initializer becomes439/441 nonexact. There is no external custom-register
prototype, forced compiler attribute or synthetic caller. Original member
versus file-local source form remains unknown. A subsequent independent
bounded acceptance records the complete68-byte bind below; the initializer
continues to be source-present/nonexact.

A separate file-local assign wrapper around the same native operation emits
only a nine-byte wrapper and leaves the initializer unchanged. It does not
recover the target120-byte boundary and is not retained. The selected source
uses the direct native assign operation. No copied STL body, aligned dummy
record, inert local or frame-padding adjustment is added.

## Full canonical results and remaining link boundary

All initializer relocations resolve, including native callback pointers,
the Winsock ordinal IATs and full NUL CP932 texts. Ordinary COFF function
pointer replay uses the actual SDK stdcall callback declarations and pinned
target entry bytes. It does not create executable ABS bindings for a linked
PE or provide implementation/exact credit for those callback declarations.

| Address | Source / target bytes | Result |
| --- | ---: | --- |
| 412E10 initialization | 439 /441 | Nonexact at+0, aligned frame/private assign and API pointer allocation |
| 413080 socket bind | 68 /68 | Exact, naturally private ECX/EAX entry |
| 41DDC0 acquisition | 148 /148 | Exact; adjacent103 metadata bytes separately verified |
| 41DEC0 release | 47 /47 | Exact |
| 41DEF0 error reporter | 84 /84 | Exact |

The smallest source control has no aligned EBP frame. Target assigns the peer
value through EDX plus one stack pointer; standalone native `_Assign_n`
instead uses the normal receiver/count/value interface. Target caches
CreateThread in EBX and directly reads SetThreadPriority twice; the ordinary
candidate allocates EBP and EBX to those pointers. No partial prefix or
same-sized diagnostic is accepted as exact.

A real pinned `/GL` compile followed by `/LTCG /NODEFAULTLIB` link at this
checkpoint stops with LNK2001/LNK1120 for the three actual thread-entry symbols
and the new thread-view wait declaration. The wait and send bodies are
recoverable from other reviewed source units. The service callback416F40 is
subsequently source-defined in
[the probe-worker checkpoint](NETWORK_UDP_PROBE_WORKER_2026_10_16.md), retaining
this initializer's existing callback symbol. The receive loop subsequently
gains full nonexact source in [the receive checkpoint](NETWORK_WINSOCK_RECEIVE_2026_10_16.md);
request415560 is now implemented in [the request checkpoint](NETWORK_UDP_REQUEST_2026_10_16.md),
while its connection415340 link input remains missing. No `/FORCE`, stub, fabricated return,
import facade or executable ABS binding is used to bypass them. This is a
concrete limit of the attempted source unit; it proves neither that LTCG is
required nor that a completed linked unit would match the initializer.

```bash
python3 scripts/audit-candidate-boundaries.py 0x00412E10 --json
python3 scripts/build.py --unit cross-v106a-network-winsock-runtime --json
python3 scripts/compare-unit-object.py cross-v106a-network-winsock-runtime build/match-units/CrossV106a_NetworkWinsockRuntime.obj --json
```

The complete comparison intentionally returns1 for initialization. Fresh
accepted-only comparison selects413080/41DDC0/41DEC0/41DEF0 and preserves all four.
Reports are `build/network-udp-initialize-{boundary,callers,formal}.json`,
`build/network-udp-initialize-accepted.json` and
`build/network-udp-initialize-ltcg-probe.diagnosis.json`.
The target-backed origin rule pins the full main hash, both exact caller
edges, seven exact helper edges and native callback/IAT fields. The separate
bind adds68 authored exact bytes; initialization remains nonexact. No new
exclusion rows are added. Only the affected runtime source unit is replayed.

## Accepted socket-bind boundary

`NetworkWinsock_bind_udp_socket @ 00413080` is independently canonical
**68/68**, SHA-256
`db31570b87c5c3560214f32a8027e3b96488c1c75703b712326b0b03a4959a3f`.
All26 instructions are reachable, with two plain RET exits and no indirect
jump, escaped edge, remote chunk or extra executable tail. Its complete
source COFF section is68 bytes. The sole instruction-checked incoming E8 is
412EFC, and a raw absolute-entry scan finds no function-pointer references.

The complete real caller and normal typed file-local definition produce the
private ECX owner/EAX port interface under ordinary `/O2 /GS`. The source
does not declare an external custom-register ABI or use a register wrapper.
Its native htons/bind IATs, CP932 error text and call to the complete real
error reporter all replay; endpoint bytes+34..3B are retained. This proves a
reproducible source/byte result, without recovering original member versus
file-local spelling or making the439-byte caller exact.

```bash
python3 scripts/build.py --unit cross-v106a-network-winsock-runtime --json
python3 scripts/compare-unit-object.py cross-v106a-network-winsock-runtime build/match-units/CrossV106a_NetworkWinsockRuntime.obj --address 0x00413080 --json
```

The result is `build/network-udp-bind-formal.json`. A fresh build and focused
accepted-only replay preserve this68-byte body and the existing148/47/84
helpers. Ghidra saves and independently reads back the supported name,68-byte
body, ECX/EAX pointer/scalar storage, zero stack pop and AL:1 bool return.
Logs are `build/network-udp-bind-ghidra-{save,readback}.log`; raw closure is
`build/network-udp-bind-boundary.json`.

## Direct analysis and gate

IDA preflight reports a different executable and is not used for analysis.
Direct Ghidra first attests executable/program SHA, base, entry marker,
x86 Windows identity and all mapped .text bytes. Owner/key/peer types, the
complete441-byte main extent, physical ECX/key/port storage and AL return,
plus EAX-port and EDX-value callee storage, are saved and checked in a fresh
read-only invocation. Existing runtime689D25 uses Ghidra's standard
`security_check_cookie` call fixup, consistent with the independently
VC8-attested15-byte checker preserving EAX. This avoids mistaking the cookie
call for the authored result; decompiler output remains a hypothesis.

Logs are `build/network-udp-initialize-ghidra-{save,readback}.log`.
One process uses768MiB heap/two CPUs. Private probes and saved analysis stay
below `.analysis/`; temporary database copies and compiled probes are removed.
The local CI gate passes155 tests and `git diff --check` passes. No all-unit
replay or new aggregate exact claim is made.
