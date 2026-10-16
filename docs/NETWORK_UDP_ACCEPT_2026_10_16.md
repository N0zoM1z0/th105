# UDP connection acceptance handler

## Observed target and physical contract

The original Japanese TH10.5 v1.06a executable has SHA-256
`56350024879199861579c11b0e1c67b9590e10a8d40cd5996b109deec9afca7e`.
`NetworkWinsock_accept_connection @ 00415AB0` has69 instructions /223 bytes,
all reached by raw CFG traversal. Its sole RET4 is415B8C; no indirect jump,
escaped branch, overlap or remote authored chunk is visible. Body SHA-256:
`3267aef9af3bb9ddf47a699372593cbe049989009ea3a8cf9e8308430e9182e7`.

The reviewed receive loop calls it at41DAC3 for opcode6. The preceding gate
requires payload length to equal the WORD at packet+8 plus12. ECX contains
the16-byte sender address, EDX contains the UDP owner, and the sole stack
argument points to the received payload at buffer+1. The entry independently
saves/uses both register parameters and reads that stack pointer only when
dispatching a nonnull callback. All exits pop four bytes and establish no
meaningful return value.

This physical parameter sequence fits a normal x86 fastcall definition.
`src/network/NetworkWinsockAccept.cpp` supplies the complete typed body using
that convention, rather than a register adapter or a declaration that ignores
an actual parameter. No synthetic caller is needed. Original explicit
fastcall versus compiler-private source spelling remains unknown; physical
compatibility alone does not recover original source provenance or TU scope.

## Complete behavior and packet view

When owner state+144 differs from3, return without touching the sender,
packet or either lock. Otherwise:

1. Construct the endpoint lock guard at wrapper+E0, entering its native
   critical section at+E4. Copy all16 sender bytes to owner+C0 and clear
   probe counter+D4.
2. While retaining that guard, construct the callback lock guard at+84,
   entering native critical section+88. If callback+80 is nonnull, invoke
   its vtable slot0 with the DWORD at packet+4, payload pointer packet+C,
   and zero-extended WORD at packet+8. The three physical callback argument
   slots are DWORD sized; original callback scalar spelling remains unknown.
3. Set state+144 to0 even when no callback exists. Destroy callback guard
   before endpoint guard. A C++ exception propagating from the callback
   unwinds both guards in that same reverse order.

The source uses a packed12-byte header view because the packet begins one
byte into a receive buffer. Only code+4, length+8 and payload+C have roles
established here. DWORD+0 and bytes+A..B remain unreviewed; no local packet
allocation or invented buffer capacity is introduced. Compile-time assertions
check the header size and selected owner offsets. Endpoint16 is copied as a
four-DWORD value, preserving its full bytes rather than only IP/port fields.
The helper adds no separate packet-size gate or endpoint validation absent
from the target.

## EH observations and compiler controls

The main prologue points to27-byte GS/EH handler6BD6C0, SHA-256
`dd5aed13b5931f3c11122967e942ce22880a7b50ae812cebbac9a5f28dd8fabe`.
It checks the frame cookie through689D25, loads FuncInfo6E3C90 and jumps to
the VC8 C++ frame handler6899E7. FuncInfo has magic19930522, two unwind
states, map6E3C80 and EHs flag1. Its36-byte SHA-256 is
`1ddfd98c7330608e3fdcf3f5adfde572fec5f21c709acc83bad6b42384063105`.
The16-byte unwind-map hash is
`f0575a8af8a4d6a726628e6701de35e62ed15a197c3b63e6c6c76ae1d70ed549`.
State0 unwinds to-1 through6BD6B0; state1 unwinds to0 through6BD6B8.
Both eight-byte chunks derive the appropriate guard from the enclosing
EBP and tail-jump to401870. They are compiler auxiliary code, not extra
independent authored functions or additional bytes credited to the223-byte
main body. The source retains ordinary `/EHsc`; asynchronous EH is not
introduced to change instruction scheduling.

Ordinary `/O2 /GS` COFF emits the full223-byte extent and resolves all four
relocation fields: the dedicated EH-handler operand, GS cookie, and native
Enter/LeaveCriticalSection IATs. It remains nonexact at+28: source saves
EDX into ESI before ECX into EDI, whereas target saves ECX into EDI first.
Two later windows differ in when the compiler writes EH states0 and1.
The packet view's explicit one-byte packing is byte-neutral in this body.

A genuine pinned `/GL` compile and resolved `/LTCG /NODEFAULTLIB` link, with
actual VC8 runtime libraries and attested data/IAT bindings, retains223
bytes and reproduces both target EH-state windows. It still reverses the
two incoming-register saves. A sender-reference control is byte-neutral
for these windows and is not selected. Neither control adds a caller,
callback stub, executable ABS symbol or forced unresolved link.

Native linked cookie and EH-handler addresses are not covered by the current
linked canonicalizer. The resolved control is therefore instruction/extent
evidence, not an accepted linked comparison or a claim that only two
canonical bytes differ. This concrete compiler-stage effect does not prove
that LTCG is required or that the full original TU would match. Do not
repeat ordinary frame/argument permutations without new source evidence.

## Reproduction and durable state

```bash
python3 scripts/audit-candidate-boundaries.py 0x00415AB0 --json
python3 scripts/build.py --unit cross-v106a-network-winsock-accept --json
python3 scripts/compare-unit-object.py cross-v106a-network-winsock-accept build/match-units/CrossV106a_NetworkWinsockAccept.obj --json
```

The strict comparison intentionally returns1 for223/223 nonexact. Build
provenance is independently checked against current source/object hashes
and the unit-input digest. Reports are
`build/network-udp-accept-{boundary,facts,build,formal}.json`; resolved-link
commands, source hash, tool pins and data bindings are in
`build/network-udp-accept-linked-probe.diagnosis.json`. Private controls remain
under `.analysis/network-udp-accept-20261016/`.

The origin rule pins the main hash, receive-loop edge, lock IAT fields,
EH-handler operand and FuncInfo fields. The dedicated DIR32 EH mapping
attests the complete27-byte target handler and changes no prior permission.
One function moves from review to authored/source-present. There is no new
exact credit or compiler/library exclusion, and no accepted unit shares a
changed source/header/flag. Verification remains focused on this new unit.

IDA preflight still identifies a different executable and is not used for
analysis. One direct Ghidra process at a time, limited to768MiB heap/two CPUs,
attests executable/program SHA, base, entry marker, x86 Windows identity and
all mapped .text bytes. Supported owner/address/packed-header types, the
complete223-byte body, void result and physical ECX/EDX/stack parameter
storage are saved and independently checked in a fresh read-only invocation.
Decompiler output is retained as a hypothesis. Logs are
`build/network-udp-accept-ghidra-{save,readback}.log`.
