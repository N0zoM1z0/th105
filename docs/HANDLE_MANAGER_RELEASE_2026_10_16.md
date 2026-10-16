# Shared handle-token release: full private-entry match

## Observed target and ownership

Only original Japanese TH10.5 v1.06a was inspected, SHA-256
`56350024879199861579c11b0e1c67b9590e10a8d40cd5996b109deec9afca7e`.
`CHandleManager_release_token @ 405200` is canonical **167/167** in
`cross-v106a-network-winsock-send-client`. Body SHA-256 is
`f225dfcb190c5b55cba3f65a784ba7a244a15da3670549afac6573f6c4166421`.
Independent raw CFG traversal reaches all63 instructions through RET4 at
`4052A4`, without uncovered bytes, outgoing direct branches, indirect jumps,
overlaps or remote chunks. Padding isolates the callable.

Nine observed direct callers include exact Title texture load `404C90` at
`404CCC`, exact Title resource release `404D70` at `404DD5`, source-present
UDP client sender `416990` at `416B01`, and identified server sender `416B60`
at `416D25`. Both Title sites independently move their manager into EAX and
push the packed token. The UDP caller uses its RTTI-backed packet manager+17C.
This supports a shared game handle-manager policy rather than a UDP-only name.
The generation/token decision and manager lock are authored behavior; the
standard list allocator/increment callees remain separate compiler-library
code. No new library exclusion is made.

The physical ABI is EAX=manager, DWORD token at entry stack+4, RET4, no
meaningful return value. The body does not inspect the manager's payload type.
Its reached prefix is a generation vector+28, free-index list+38 and critical
wrapper+48/native lock+4C. Source uses the concrete packet-manager specialization
whose common prefix is independently recovered; other original source
specializations and the original template spelling remain unknown.

## Complete behavior and source

The function enters the manager lock, extracts unsigned slot=token low16 and
generation=token high16, and reads the checked generation vector at that slot.
If it differs, it leaves the lock without recycling anything. On equality,
it performs a second checked vector access, sets that generation to zero,
pushes the unsigned slot onto the free list's back, then leaves the lock.
It neither destroys the payload nor removes its stable pointer.

There is no extra nonzero-generation, slot-validity return or duplicate-free
guard. Invalid indices retain native checked-vector behavior. The lock uses
explicit Win32 calls and the function has no main EH region; source does not
add RAII cleanup or rollback around list allocation failures.

`NetworkUdpPacketHandleManager64::release` in
`src/network/NetworkWinsockSendClient.cpp` is ordinary C++, using the shared
two-word token view, actual native vector/list members and Win32 calls.
The file contains its real sender and acquire definitions. No external EAX
prototype, register variable, assembly, fake caller, copied STL implementation
or shaping local is introduced. An isolated ordinary candidate is151 bytes;
the real caller allows LTCG to generate EAX self and the aligned frame.
Pure CIL produces163 bytes because it privately specializes the list size
helper. The genuine ordinary `src/library/UnsignedIntList.cpp` instantiation
linked before CIL preserves the normal list helper ABI and explicit increment
argument, giving the complete167-byte target body. It receives no authored
credit and does not establish the original TU partition.

All four REL32 fields replay by name: two invalid-parameter calls to `68A143`,
list `_Buynode` to `4129E0`, and `_Incsize` to `402700`. Both absolute Win32
references attest Enter/LeaveCriticalSection IAT cells `6C0108`/`6C0104`.
Every other instruction, branch, stack operation and immediate compares
without masks. Source and target full body hashes agree.

## Strict private-function contract

The configured mixed unit exports only the real sender. Exporting release
would preserve its public calling convention and lose the private entry.
Its function contract instead declares:

```toml
private_from = { caller = "0x00416990", site = "0x00416B01" }
```

The linked comparator independently requires:

- A distinct configured exported caller with reviewed implemented/matching
  source in the same TU; private witness chains and self-witnesses fail.
- Exactly one source CIL-owned map entry for the private symbol. Function
  aliases and any export of that entry, including ordinal-only aliases, fail.
- Independently closed source and target caller CFGs. Both must have exactly
  one ordinary direct E8 call to their respective private function. The
  original call must be exactly the declared instruction site, not a byte
  sequence inside another instruction or an unreachable tail.
- A matching named callee mapping in the actual caller contract. Missing or
  wrong mappings, changed source ownership and unreviewed parents fail.
- No internal base relocations in the witness caller for this initial contract.
  Caller source/target hashes and actual E8 sites are retained in the report.

These checks also run when only release is selected. The private function then
passes the unchanged complete map/CFG boundary, named call/data replay and
full canonical comparison. The target's167-byte size is never used to crop
the source body. Build/source/CIL/COFF/map/image/tool/header/parser hashes still
guard every artifact before decoding. Existing COFF comparison is unchanged.

The source sender remains561/464 nonexact, first difference+A2, on iterator
register allocation and token-queue inlining. Its role here is independent
caller ownership evidence; no prefix or sender bytes enter matches.csv.
Acquisition remains ordinary427/410 nonexact in its separate probe unit.
The new exact row accounts only for the full167-byte release.

## Reproduction and validation

```bash
python3 scripts/audit-candidate-boundaries.py 0x00405200 --json
python3 scripts/build.py --unit cross-v106a-network-winsock-send-client --json
python3 scripts/compare-linked-unit.py cross-v106a-network-winsock-send-client --address 0x00405200 --json
```

Reports are `build/network-udp-release-boundary.json`,
`build/network-udp-release-callers.json`, `build/network-udp-release-linked-build.json`
and `build/handle-manager-release-formal.json`. The complete mixed-unit
comparison, `build/network-winsock-send-client-linked-full.json`, intentionally
returns1: sender561/464 is nonexact while release167/167 is exact. Both supported
Capstone versions4.0.2 and5.0.6 independently rebuild and compare the private
167-byte entry and pass all19 linked-path acceptance/rejection tests. A build
and comparison must use the same recorded parser version.

After changing the shared linked comparator, fresh builds and accepted-function
dispatch verify scene retirement281/281, pool destructor98/98 and this helper
167/167. `build/handle-release-accepted-dispatch.json` records all three selected
accepted results, including the private caller witness when only release is
selected from its mixed unit. Local `python3 scripts/ci.py` and the pinned
Capstone4 CI environment both pass all151 tests and generated-progress checks;
`git diff --check` passes. No unrelated aggregate cold replay is used; status
totals remain ledger totals until a separate `--all` run.

## Analysis working state and unknowns

The IDA preflight remains attached to a different executable; no IDA analysis
is used. The typed-re request records that blocked session. Raw target bytes,
complete CFGs, widths, caller edges and ABI provide the observations above.
Direct Ghidra independently attests executable/program SHA, base, entry marker,
x86 Windows identity and every mapped .text byte. Its saved shared prefix,
full extent, durable name, custom EAX/stack token storage and RET4 are checked
in a fresh read-only invocation. The source remains a normal C++ member;
custom storage is analysis metadata describing the observed machine entry.
Logs are `build/handle-release-ghidra-save.log` and
`build/handle-release-ghidra-readback.log`. One process uses768MiB and two CPUs.

The original TU, template source spelling, broader source profile and sender
inlining choices remain unknown. This accepted function proves the bounded
167-byte result and its recovered policy; it does not prove the whole original
networking module or the95% authored-byte goal.
