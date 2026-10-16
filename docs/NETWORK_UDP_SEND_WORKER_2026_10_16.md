# UDP send worker and native thread entry

## Observed target boundary and ownership

Only the original Japanese TH10.5 v1.06a executable was inspected, SHA-256
`56350024879199861579c11b0e1c67b9590e10a8d40cd5996b109deec9afca7e`.

| Address | Role | Bytes / instructions | Body SHA-256 |
| --- | --- | ---: | --- |
| `416D90` | Native send-thread entry | 18 / 8 | `0172c396239ced0a7fe1962aba00b52ccf3eceaf7f7bdd06053975f27f78e52f` |
| `416DB0` | Private UDP send loop | 395 / 116 | `87a75b97cd80876ba129af487f217cae7790b8f159ef7a2095a00b7faa1ac03c` |

Raw CFG traversal reaches every byte in both independently padded bodies,
with no escaped branch, indirect jump, overlap or unreached byte. The worker
returns at `416F3A`; the next function starts at `416F40` after INT3 padding.
The native callback loads its single stack parameter into ESI, calls the
worker at `416D96`, returns zero and executes RET4. The worker consumes ESI,
has no stack parameters and returns through RET without saving ESI.

Initializer `412E10` pushes callback `416D90` at `412F52`, together with the
UDP owner and thread-id destination, then calls the PE-attested CreateThread
IAT `6C0138` at `412F5F`. Its thread wrapper is owner+5C. This native caller
plus game-owned queue, timeout and recycling policy establishes authored
ownership independently of the compiler/private ABI or comparison result.

## Complete behavior and source

`src/network/NetworkWinsockSendClient.cpp` now contains the two senders, real
thread entry, complete send loop and complete acquire/lookup/release members.
The owner view names the already observed socket+28, preserving running+74,
native token deque+168, packet manager+17C, event+1E0 and queue lock+1E4.
Compile-time assertions retain these offsets; its full class spelling and
original TU partition remain unknown.

The target creates an unnamed auto-reset, initially nonsignaled event and
stores its handle even on failure. While running, it waits indefinitely,
ignoring the wait result, then drains queued tokens while running remains set.
Each front/pop operation uses the queue's native critical section at+1E8;
an empty queue supplies token zero, which ends this drain and returns to wait.
There is no RAII/EH scope in this loop and no new API-error guard is added.

For each nonzero token, ordinary ECX lookup `417800` returns its packet or
null. Null skips both sending and recycling. A valid packet is sent when
`timeout_ms_14 == 0` or unsigned `timeGetTime() - timestamp_10 < timeout_ms_14`.
Thus the formerly provisional `options_14` field is now named for its observed
expiry role; zero disables expiry. The two target argument-setup branches
converge at the same six-argument native sendto call. Socket+28, packet
payload+1C, size+18 and its complete16-byte endpoint supply the arguments;
send failure is ignored. Every valid token is recycled through private EAX
release `405200`, including expired packets and failed sends. Exit closes the
event and clears the stored handle.

The lookup member reuses the established scoped-lock policy of the reviewed
shared handle lookup: check slot range and16-bit generation, return null on
mismatch, otherwise return the checked stable slot. It supplies complete
honest source context to the worker; it adds no separate source/exact claim
for the already mapped generic lookup. The source worker uses provisional
void because its callback discards incidental CloseHandle EAX. No meaningful
worker return contract is established by these instructions alone.

## Real import-library comparison

The target E8 at `416EFD` reaches six-byte thunk `6898CC`, `FF25 74026C00`,
whose IAT `6C0274` imports WS2_32 ordinal20. Declaring sendto with dllimport
would introduce a different six-byte call instruction. Source instead uses
its normal six-DWORD stdcall declaration and links the actual VC8 SDK
`PlatformSDK/Lib/WS2_32.Lib`, SHA-256
`fc1fbe94773a2bafd735b7123d31e5f9377d8381d704494a7757c8a2eccfec90`.
Its `_sendto@24` i386 code/ordinal20 short import member has SHA-256
`677c886dace564fc7dd6ca26b7eec488a4b65d67c46847ba0da1b9396d261168`.
The SDK member instructs the linker to emit its thunk; no executable address is bound as absolute
data, and no source stub, copied bytes or synthetic callee is supplied.

The linked comparison's narrow SDK registry attests that member ABI, target
excluded import origin, complete six-byte thunk, IAT literal and actual PE
ordinal identity. Source import, unique map symbol/library owner and explicit
callee mapping must agree. pefile annotates known ordinal imports with names;
the comparator now preserves the underlying ordinal instead of treating that
annotation as a named import. Named VC8 runtime calls remain supported;
arbitrary external/ordinal calls remain rejected. SDK contracts and the full
library hash join stale-artifact provenance. See [the comparison contract](LINKED_PE_MATCHING.md).

The smallest ordinary COFF file-local worker control was393/395 nonexact.
Recovering the target's nested running loops, with the real caller and full
member helpers under LTCG, produces the following complete canonical results:

| Address | Source / target bytes | Result |
| --- | ---: | --- |
| `416D90` thread entry | 16 / 18 | Nonexact at+0; target also reserves/restores a scratch DWORD |
| `416DB0` worker | 395 / 395 | Nonexact at+0; callee-save shrink wrapping differs |
| `405200` shared release | 167 / 167 | Exact, preserving its real client caller witness |

All five worker REL32 calls resolve. Its middle `[+0x21,+0x170)` agrees for335
canonical bytes, including queue, lookup, expiry, send, release and running
edges. This is diagnostic evidence only: full entry/exit bytes still differ,
so neither new function gains exact credit. The source naturally generates
the worker's private ESI ABI; no register facade, padding, inert local or
forced compiler attribute is used. Original frame/optimizer context remains
open. Both existing senders remain561/464 and644/548 nonexact.

```bash
python3 scripts/audit-candidate-boundaries.py 0x00416D90 0x00416DB0 --json
python3 scripts/build.py --unit cross-v106a-network-winsock-send-client --json
python3 scripts/compare-linked-unit.py cross-v106a-network-winsock-send-client --json
python3 scripts/compare-linked-unit.py cross-v106a-network-winsock-send-client --address 0x00405200 --json
```

The full comparison intentionally returns1 for the source-present functions.
Reports are `build/network-udp-send-worker-{boundaries,formal}.json` and
`build/network-udp-send-worker-affected-accepted.json`. After shared source,
header and comparator changes, fresh serial builds preserve all three
affected accepted linked units: scene281, pool98 and release167. No all-unit
replay or new aggregate exact claim is made. Both supported Capstone versions
pass the23 linked-contract tests; the final focused replay uses4.0.2, with
pefile2024.8.26. The local CI gate passes155 workflow tests.

The full target-backed origin replay also corrected an older guard that still
expected caller416990 to be identified; it is now source-present/implemented.
Its original deque push_back edge and all four generated exclusions remain
unchanged. The new authored rule pins both body hashes and real callback edge.

## Direct analysis state

IDA preflight still reports a different executable, so no IDA analysis is used.
Direct Ghidra independently attests executable/program SHA, image base, entry
marker, x86 Windows identity and all mapped .text bytes before touching
metadata. Full decompilation remains a hypothesis. Supported owner/packet
fields, names, complete extents, stdcall stack parameter and private ESI
storage are saved and checked in a separate read-only invocation. Logs are
`build/network-udp-send-worker-ghidra-{save,readback}.log`; private scripts and
saved analysis remain below `.analysis/`. Ghidra's project-name restriction
requires a disposable visible build path during invocation. One process uses
768MiB heap and two CPUs; the temporary database copy is removed afterward.
