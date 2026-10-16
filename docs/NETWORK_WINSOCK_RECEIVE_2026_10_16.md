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
replay. The loop has a declaration only: it is identified and mapped, without
source-present or exact credit. Its game-owned packet policy and native
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

Original source/TU visibility, complete private protocol helper definitions,
the concrete peer container/record types, and the ownership of the remaining
large stack frame are still open. A temporary reply packet is observed, but
the frame alone does not establish its source buffer capacity. Recover a
closed source unit before implementing the loop; preserve its actual length,
lock-release, callback and exception behavior.

## Reproduction and analysis state

```bash
python3 scripts/audit-candidate-boundaries.py 0x0041D7B0 0x0041D7C0 --json
python3 scripts/build.py --unit cross-v106a-network-winsock-receive-thread --compare --json
```

The ordinary boundary audit deliberately reports the unresolved switch rather
than claiming full closure. The full table-resolved packet is
`build/network-winsock-receive-facts.json`, produced by the private raw-PE
driver `.analysis/network-receive-20261016/audit.py`; it verifies target and
guard bytes, owns every main instruction, and records table/EH hashes.
Focused comparison is `build/network-winsock-receive-thread-formal.json`.

Direct Ghidra inspection independently attests executable/program SHA, base,
entry marker, x86 Windows identity and every mapped .text byte before analysis.
Decompiler output remains a private hypothesis. Supported names, complete
main extents, return/parameter widths and ECX versus native stdcall storage
are saved and checked in a fresh read-only session. Scripts stay below
`.analysis/network-receive-20261016/ghidra-scripts/`; logs stay below `build/`.
Only one Ghidra process runs at a time, with768MiB and two active processors.
