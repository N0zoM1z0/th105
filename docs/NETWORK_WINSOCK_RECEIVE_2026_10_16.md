# Winsock receive thread and UDP dispatch boundary

## Observed target and native entry

Only the original Japanese TH10.5 v1.06a executable was inspected, SHA-256
`56350024879199861579c11b0e1c67b9590e10a8d40cd5996b109deec9afca7e`.

| Address | Role | Main bytes | Body SHA-256 |
| --- | --- | ---: | --- |
| `41D7B0` | `NetworkWinsock_receive_thread_entry` | 14 | `29085c8a40c4412b819dc9284c0eb4b36ebea1ea27583ad9fa7998613c54eb6a` |
| `41D7C0` | `NetworkWinsock_receive_loop` | 1424 | `11a2105c52c0611564483f615280639f7c050bd22086e473474c83ba64410912` |

The initializer at `412E10` supplies entry `41D7B0` at `412F7F` to the
PE-attested CreateThread import, with the Winsock owner as its parameter and
the thread handle/id stored at owner+64/+68. The four-instruction callback
loads that parameter into ECX, calls `41D7C0` at `41D7B4`, returns zero and
executes RET4. The loop consumes ECX, has no explicit stack arguments and
returns through plain RET. No custom register convention is needed here.

Natural C++ in `src/network/NetworkWinsockReceiveThread.cpp` compiles to
**14/14 canonical exact**, with the complete COFF extent and one named REL32
replay. The loop now has complete source in the same TU, together with the
actual private lookup/rejection/endpoint-list helper bodies. Its source main
is1456 bytes plus56 bytes of switch metadata, nonexact against1424+56.
The loop receives source-present credit and no exact credit. Its game-owned packet policy and native
thread lifecycle establish authored origin independently of that distinction.
The socket+28/running+74/worker+64 fields agree with the separately reviewed
Winsock constructor and exact shutdown views; the original class spelling is
not recovered by these method names.

## Complete main control flow

The initial direct-edge audit reached only226 bytes because dispatch at
`41D86D` is indirect. Raw instructions at `41D859` zero-extend the opcode,
subtract one, reject indexes greater than13 and index the14-entry dword
table at `41DD50`. Seeding precisely those destinations closes **364
instructions/all1424 main bytes**, with no overlap, escaped direct branch,
unreached main bytes or additional indirect jump. The sole RET is at `41DD4F`.

The following56 table bytes are metadata, not part of the callable extent.
Their SHA-256 is
`5160d7cf990c7db8cba03302f230877d399c2ca515846b226e8443ff8c4a57da`.
The table maps these opcode values; packet meanings remain provisional:

| Opcode | Destination | Observed length gate / action |
| ---: | --- | --- |
| 1 | `41D93B` | Payload36; compare two embedded endpoints, reply3 or forward21-byte packet2 with a converted port |
| 2 | `41DA0E` | Payload20; send one-byte packet3 to the embedded destination |
| 3 | `41DA40` | Publish16-byte sender address at owner+3C; transition state+144 from2 to3 |
| 4 | `41D874` | Payload4; find sender peer, update peer+1C and clear peer+14, or update matching primary peer+DC/+D4 |
| 5 | `41DA82` | Payload length equals word at `packet+0x15` plus24; call private `415560` |
| 6 | `41DAA8` | Payload length equals word at `packet+0x09` plus12; call private `415AB0` |
| 7 | `41DACD` | Payload4 and state+144 equals3; call private `415B90` |
| 8 | `41DAF4` | Payload68; call `415C10` |
| 9, 10, 12 | `41DD22` | Resume receive loop |
| 11 | `41DB0C` | Call `413170` with peer+10, or `415340` for the matching primary peer with terminal value FFFF |
| 13 | `41DBE0` | For matching primary sender clear+D4; dispatch callback slot+8 under its lock |
| 14 | `41DC6C` | Clear peer+14, then dispatch callback slot+C with peer handle and payload |

The1024-byte receive buffer is zeroed once before the loop. Each iteration
calls the PE-attested WS2_32 `recvfrom` thunk at `6898BA` using socket+28 and
a16-byte sender address. The unsigned length check accepts0..1023 and rejects
SOCKET_ERROR and1024; payload length is the result minus one. Several cases
have no independent payload-length gate. Do not add a new zero-length guard
or clear the buffer again when recovering source. Running+74 is checked before
the first receive and at the common continuation. `sendto`, `ntohs` and
`htons` independently resolve through the target PE import directory.

## Locks, EH and remaining source boundary

Three critical-section wrappers are observed at owner+84, +E0 and +120;
their native critical sections begin four bytes later. The peer container is
at+FC, with a sentinel at+100. `412A60` queries an IP-key range and checks
peer ports, returning a checked iterator. Native multimap semantics are an
inference from its tree/iterator and equal-range behavior, not a new library
exclusion claim. The iterator accessor at `413890` uses ESI; the lookup and
several protocol helpers also consume private register arguments. External
fastcall declarations would not preserve their actual contracts.

The loop's GS/EH handler is `6BE54C`,46 bytes, hash
`c9d6b556d9a8247ab1dd2def2ceda19beb2234c720dbf29bcc47447542855c08`.
It supplies FuncInfo `6E4D60` (magic19930522), whose four-entry unwind map is
at `6E4D40`. States0..3 each unwind directly to state-1 through11-byte chunks
at `6BE520`, `6BE52B`, `6BE536` and `6BE541`. Each derives a local lock guard
from the enclosing EBP and tail-jumps to lock-guard destructor `401870`.
These are compiler auxiliary chunks, not additional independent authored
functions or an excuse to include the adjacent jump table in the main body.

The selected source uses the separately reviewed native
`multimap<unsigned int, Peer20 *>` and vector layouts. Original source/TU
visibility, template boundaries and the large reply-storage frame remain
open. The actual receive caller and full file-local normal C++ helper bodies
naturally generate EAX owner for the checked peer lookup and ESI owner for
rejection. There is no external custom-register declaration or synthetic
caller. Endpoint-list source remains389/315 and uses ESI rather than the
target EDI; lookup170/167 and rejection122/122 also remain nonexact. These
supporting definitions receive no new independent source/exact/exclusion
credit in this bounded loop checkpoint.

## Complete source and preserved edge cases

The source retains every opcode gate in the table above. The received buffer
is1024 bytes and zeroed once, and sender length is initialized to16 once.
Unsigned receive-length filtering rejects errors and1024 while retaining
zero-length datagrams. The source does not invent an empty-packet guard:
the retained opcode byte and size-1 behavior remain as observed.

Opcode1 compares IP/port fields in two packed16-byte endpoints. Equal endpoints
produce one-byte opcode3 to the sender. Otherwise the handler constructs
opcode2, copies the complete sender16, and replaces its embedded port with
`htons(port)`; a low16-bit value below1024 first adds `ntohs(sender.port)`.
It forwards21 bytes to the second embedded endpoint. Only the first17 reply
bytes are written: the trailing four bytes remain untouched in the target.
The selected21-byte local preserves that fact without zeroing them or guessing
the original larger local capacity. Opcode2 replies with one-byte opcode3 to
its embedded endpoint. Opcode3 publishes the entire sender16, then changes
state2 to3 under the native endpoint lock.

Opcode4 manually locks the peer table. A found peer receives its report at+1C
and counter+14=0. On a miss, the peer lock is released before a scoped endpoint
lock compares the primary IP/port, updates owner+DC and clears+D4. Opcode11
uses a scoped peer lock; the found-peer path removes its signed slot bits and
exits that scope. The miss path destroys that guard before constructing a
separate endpoint guard, then calls ordinary connection415340 with
`(null, 0, null, FFFF)` only for the matching primary sender.

Opcodes13/14 preserve manual endpoint/peer locking and release that lock
before a scoped callback guard. Opcode13 clears the primary probe counter and
calls callback slot+8; opcode14 clears the found peer counter, saves its slot
and calls slot+C. Their payload lengths are the actual receive result minus
one. Manual locks are not upgraded to RAII: native lookup failure/exception
behavior differs from the four observed scoped guards. The ordinary source's
FuncInfo independently has exactly four states, each unwinding to-1, matching
the target's four independent cleanup scopes.

Opcode7's complete same-TU helper calls slot+4 with its packed DWORD and sets
state9 before guard destruction. Opcode8's complete helper clamps its signed
count only above4. A matching published IP/port returns without further writes;
otherwise it backs up/publishes endpoints, writes marker+148=FFFFFFFF, clears
the native endpoint vector and appends the clamped count, then writes state2.
Negative and zero counts still publish the first endpoint and clear the vector.
No new lower-bound guard is added.

The source declares opcode5 request415560 only after checking its complete
physical entry: ECX sender, EDX request, one stack owner pointer, saved
remaining registers and RET4 fit a normal fastcall prototype. Acceptance415AB0
uses the independently reconstructed compatible fastcall definition. The
connection415340 declaration preserves its ordinary ECX receiver, four stack
slots, RET16 and observed AL0/1 result. These are typed native contracts,
without register forwarding wrappers; original source spelling remains unknown.

## Full comparison and genuine link boundary

The fresh minimum-storage source reserves470 bytes versus target890. Its
complete main code is1456 bytes; the following56 bytes are its14-entry table,
so the comparator's1512-byte section tail is not described as authored code.
All selected relocations resolve, including internal switch destinations,
the full GS/EH handler and every native/protocol call. The main remains
nonexact, first at+0x16 in frame allocation; the affected native callback
remains14/14 through the actual full loop definition with GS enabled.

A pinned `/GL` compile and real `/LTCG /NODEFAULTLIB` control includes the
actual ordinary-COFF acceptance and peer-removal implementations, native VC8
runtime/WS2_32 libraries and attested data/IAT bindings. Its private source
uses the genuine peer-removal view's declaration and implementation. The link
stops at LNK2001/LNK1120 for exactly two genuine missing bodies: request415560
and connection415340. No stub, fake return, executable ABS symbol or forced
unresolved link is introduced. This does not prove that LTCG is required or
that the remaining source inputs would make the full loop exact.

## Reproduction and analysis state

```bash
python3 scripts/audit-candidate-boundaries.py 0x0041D7B0 0x0041D7C0 --json
python3 scripts/build.py --unit cross-v106a-network-winsock-receive-thread --json
python3 scripts/compare-unit-object.py cross-v106a-network-winsock-receive-thread build/match-units/CrossV106a_NetworkWinsockReceiveThread.obj --json
python3 scripts/compare-unit-object.py cross-v106a-network-winsock-receive-thread build/match-units/CrossV106a_NetworkWinsockReceiveThread.obj --address 0x0041D7B0 --json
```

The ordinary boundary audit deliberately reports the unresolved switch rather
than claiming full closure. The full table-resolved packet is
`build/network-winsock-receive-facts.json`, produced by the private raw-PE
driver `.analysis/network-receive-20261016/audit.py`; it verifies target and
guard bytes, owns every main instruction, and records table/EH hashes.
The complete comparison intentionally returns1 for the main; the accepted-only
entry comparison returns0. Reports are
`build/network-receive-source-{build,formal,accepted}.json` and
`build/network-receive-source-ltcg-probe.diagnosis.json`. Fresh source/object
hashes and the current unit-input digest are independently checked against
the build record. No other accepted unit shares a changed source/header/flag.

Direct Ghidra inspection independently attests executable/program SHA, base,
entry marker, x86 Windows identity and every mapped .text byte before analysis.
Decompiler output remains a private hypothesis. Supported names, complete
main extents, return/parameter widths and ECX versus native stdcall storage
are saved and checked in a fresh read-only session. The source checkpoint
adds the supported15C-byte owner prefix and native address/peer/map/vector
types; complete original owner size remains separately reviewed as314.
Scripts stay below `.analysis/network-receive-source-20261016/ghidra-scripts/`;
logs are `build/network-receive-source-ghidra-{save,readback}.log`.
Only one Ghidra process runs at a time, with768MiB and two active processors.
