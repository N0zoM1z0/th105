# UDP client sender and real caller context

The later [formal shared-release checkpoint](HANDLE_MANAGER_RELEASE_2026_10_16.md)
accepts `405200` as167/167 through a strict source-owned private-entry contract.
Its sender unit is now mixed COFF/LTCG: sender561/464 remains nonexact, while
selecting the release verifies its actual exported caller even when that caller
is not selected for matching. The ordinary465/464 and formerly unaccepted
private controls below remain historical measurements.

## Observed target and complete boundary

Only original Japanese TH10.5 v1.06a was inspected, SHA-256
`56350024879199861579c11b0e1c67b9590e10a8d40cd5996b109deec9afca7e`.
`NetworkWinsock_send_client @ 416990` has464 bytes,145 reached instructions,
and body SHA-256
`5b83746b7004fc7e95b134b175b5b03d11feb738ac0e177d7d1b735506f48031`.
The entire CFG closes at RET16 `416B5D`, without indirect jumps, outgoing
direct branches, overlapping decode or uncovered tails. The address already
had independently observed authored ownership from nine exact client callers;
no new origin exclusion or authored-byte denominator change is made here.

Exact wrappers `44D770` and `44E6A0` call it at `44D794`/`44E6C6`, passing
ECX=client's UDP member+3B4, serialized buffer, size, options and either null
or packet result-field+4. Their return chains preserve EAX. The sender itself
returns the final Win32 SetEvent value. Raw stack operands independently fix
four DWORD arguments and RET16; old two-argument declarations are insufficient.
Source uses `int send_client(const void*, unsigned, unsigned, unsigned*)`.
Signedness of the copied options has no observed arithmetic meaning.

## Source-level behavior

`src/network/NetworkWinsockSendClient.cpp` contains a method-focused owner view
with compile-time assertions for endpoint+C0, native token deque+168, packet
manager+17C, event+1E0 and queue lock+1E4. Its footprint through+200 is not a
replacement claim for the full known0x314-byte CNetworkUDP owner.

The complete sender performs these operations in target order:

1. Initialize a packed token DWORD to zero and acquire a packet from manager
   +17C, passing its slot/generation words through the existing token type.
2. Write opcode0E at packet+1C, copy options to+14, then store timeGetTime at+10.
3. Enter endpoint lock's native critical section at owner+E4, copy all16 endpoint
   bytes from owner+C0, and leave that lock.
4. Copy caller bytes to packet+1D and store size+1 at+18. The target adds no
   capacity or overflow check here; source does not invent one.
5. Enter queue lock's native critical section at+1E8. If result is nonnull,
   traverse the checked token deque. Compare each token with `*result` first;
   on a match release that pool token, erase its queue iterator and stop.
   On a mismatch, stop if running+74 is zero; otherwise increment and continue.
   Publish the new packed token through result regardless of whether one was
   found. A stopped owner can still replace a matching current token.
6. Append the new token, leave the queue lock, signal event+1E0 and return its
   Win32 BOOL value as int.

These two lock regions use explicit Win32 calls, as observed. No EH guard is
added around them. Acquisition retains its separate real scoped lock and
packet local. Source keeps real native checked deque/list/vector operations,
including the iterator comparison/dereference/increment checks and repeated
end lookup. Decompiler output is not copied as source.

## Whole-function comparison and private entries

Unit `cross-v106a-network-winsock-send-client`, ordinary VC8 `/O2 /GS`, compares
the complete candidate as **465/464 nonexact**, first difference+0A. Every
relocation resolves: acquire `417660`, release `405200`, token erase `4172C0`,
token append `417240`, memcpy `68AA30`, invalid-parameter runtime and the four
attested Win32 IAT identities. The candidate uses normal C++ member calls;
the target's acquire/release are private stack/EAX entries. Relocation replay
does not hide those instruction/argument differences.

The full acquire definition moves from `NetworkUdpPacketAcquire.cpp` into the
real caller TU. Release is also fully defined there from its bounded raw
167-byte body: manual lock, checked slot-generation compare, zero matching
generation, append its unsigned slot to the free list, unlock. This provides
real callee context rather than a synthetic resolver, dummy caller or
fabricated register declaration. The acquire unit points to this same TU and
still reports427/410 with GS. The release definition is context only in this
checkpoint, without its own source/exact ledger selection.

A resolved `/O2 /GL /GS- /LTCG` control exporting only the real sender naturally
changes acquire to stack owner/RET8 and release to EAX owner/RET4. Thus ordinary
member definitions can express both observed private interfaces. The pure CIL
control gives sender561, acquire481 and release163 bytes. The sender now has
the target's initial call/endpoint-copy shape but expands token push_back and
allocates iterator registers differently; equal prefixes give no exact credit.

Linking the genuine ordinary `src/library/UnsignedIntList.cpp` before that CIL
preserves shared list `_Buynode`/`_Incsize` identities and the explicit increment
argument. The retained-source control gives sender561, acquire481 and release
167 bytes. The complete release diagnostic replays all four REL32 fields and
both critical-section IAT references, with canonical SHA-256 exactly
`f225dfcb190c5b55cba3f65a784ba7a244a15da3670549afac6573f6c4166421`.
That is a useful private-function witness, **not an accepted exact unit**.
The source-owned function is deliberately not exported; exporting it would
preserve the public ABI and lose the very private entry being reconstructed.
The existing formal linked path requires source-owned exports and cannot yet
accept it. `matches.csv` and its review origin remain unchanged.

A separate ordinary `deque<unsigned int>::push_back` instantiation does not
prevent CIL caller inlining: a two-library control gives565/464 sender. It is
retained privately as a negative result, not added to repository library source
or progress. Do not replace these private interfaces with external facades or
add noinline/member-pointer tricks to compensate for original TU decisions.

Next work should independently bound/classify `405200` and establish a strict
private-function comparison contract tied to its genuine exported source caller,
target call edge, full map/CFG boundary and pinned build provenance. Its 167-byte
witness does not authorize bypassing those acceptance requirements.

## Reproduction and analysis state

```bash
python3 scripts/audit-candidate-boundaries.py 0x00416990 --json
python3 scripts/build.py --unit cross-v106a-network-winsock-send-client --compare --json
python3 scripts/build.py --unit cross-v106a-network-udp-packet-acquire --compare --json
```

Reports are `build/network-udp-send-client-boundary.json`,
`build/network-winsock-send-client-formal.json` and
`build/network-udp-packet-acquire-formal.json`. Both ordinary comparisons have
expected exit1 with complete nonexact bodies and no unresolved relocations.
Private sources, original commands, maps and diagnostic disassembly are below
`.analysis/network-udp-send-client-20261016/` and
`build/network-udp-send-client-{ltcg,mixed,public-mixed}/`. The retained-source
private release report is `build/network-udp-send-client-public-mixed/release-diagnostic.json`;
its driver explicitly records that no acceptance unit is configured.

After the shared nonvirtual release declaration and TU move, fresh focused
comparisons retain acquire427/410 and the accepted pool destructor98/98.
Local `python3 scripts/ci.py` passes all147 tests and generated-progress checks;
`git diff --check` passes. Only the affected accepted destructor is replayed.

IDA preflight still reports the wrong target; no IDA analysis is used. Raw
facts come from the hash-attested PE. Direct Ghidra independently checks source
and program SHA, image base, entry marker, x86 Windows identity and every mapped
.text byte before inspection. Initial decompiler output misinterprets stack
values across untyped runtime/private calls and drops the redundant checked
iterator self-comparison; raw instructions, not that pseudocode, determine the
source and four-argument signature. Supported sender name, complete extent,
physical parameter storage and owner view are saved and checked in a fresh
read-only invocation. Logs are `build/network-udp-send-client-ghidra-{inspect,save,readback}.log`.
One Ghidra process uses768MiB and two CPUs.

The source partition and original inlining decisions remain unknown. Preserve
the new complete source and measured private-entry evidence while keeping the
sender and acquire nonexact. This checkpoint claims no new exact bytes and no
aggregate cold replay.
