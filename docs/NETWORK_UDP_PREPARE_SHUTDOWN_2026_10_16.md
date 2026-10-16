# UDP shutdown preparation

## Observed target and complete boundary

The original Japanese TH10.5 v1.06a executable has SHA-256
`56350024879199861579c11b0e1c67b9590e10a8d40cd5996b109deec9afca7e`.
`NetworkWinsock_prepare_udp_shutdown @ 004130D0` contains46 instructions /
149 bytes, ending at the plain RET at413164. Raw CFG traversal reaches every
instruction, with no indirect jump, escaped edge or remote chunk. Its body
SHA-256 is
`8e38fc406dd1c2c6fd75ff587e6dccb836851c55ae0bcf84b122395cea22e5a3`.

The known direct caller is the canonical-exact175-byte shutdown412FD0, at
412FDE. That caller establishes ESI from its ECX owner before this call.
Preparation uses ESI without saving it or reading a stack argument, and
returns without a stack pop. Its peer-removal call at41313E instead supplies
ECX=ESI and one DWORD stack slot to the independently reviewed413170.
Neither the earlier ordinary-member declaration nor a register parameter
invented in source establishes this private interface.

## Recovered behavior and owner layout

`src/network/NetworkWinsockShutdown.cpp` now contains the preparation body
beside its actual shutdown caller. The method-specific owner view preserves
the existing worker/heap/event fields and adds the supported endpoint at+C0,
native24-byte critical section at+E4, native16-byte peer vector at+108 and
DWORD state at+144. Peer elements are32 bytes; other reviewed initialization
and removal paths establish their16-byte endpoint and signed slot at+10.
Compile-time assertions check the selected field offsets and element width.

The target performs these operations in order:

1. Store byte0B in local storage and enter the endpoint critical section.
   Call native `sendto` with socket+28, the byte's address, length1, flags0,
   endpoint+C0 and endpoint length16. Discard the send result, then leave
   the critical section. No exception guard or API-error branch is added.
2. Start slot at zero. On every iteration reload vector begin+10C and
   end+110, treating a null begin as size zero and otherwise dividing their
   difference by32. While slot is below that current size, call413170 and
   increment slot. Do not cache the count or filter peers before removal.
3. Store state+144=1 and finish the observed GS-cookie check/epilogue.

The selected source models the one transmitted byte. The target's aligned
EBP frame (`and esp,-8; sub esp,42C`) and cookie slot at frame+428 are exact
observations; they do not establish a local packet type or buffer capacity.
After the saved EDI and lock argument are accounted for, both the byte store
and send pointer refer to frame+20. Original local ownership, alignment,
source spelling and translation-unit partition remain unknown.

## Genuine source controls

A full file-local `static void __stdcall` definition and its real shutdown
caller naturally compile to the private ESI owner interface under VC8 `/O2`.
The helper's source body is115 bytes, nonexact against149, while the complete
caller remains175/175 canonical exact. The source supplies ordinary typed
C++ rather than an external custom-register declaration or synthetic caller.
GS is enabled for the unit, as observed in the target preparation; the
selected one-byte local does not cause this candidate to emit a cookie.

A separate control reuses the genuine `NetworkUdpPacketBuffer41C` from the
reviewed RTTI-backed packet pool, setting its first payload byte and sending
one byte. That type is established for pool storage, not for this local.
It emits150 bytes, with a420-byte frame and cookie at+41C, no aligned EBP
frame, and different opcode/pointer offsets. Enlarging it to fit the target
frame would invent storage, so this control is not retained as source.

A real mixed COFF/LTCG control compiles that candidate with `/GL` and links
with `/LTCG /NODEFAULTLIB`, the actual ordinary-COFF peer-removal and thread
runtime sources, pinned VC8 libraries, and attested data/IAT bindings. All
executable references resolve to genuine source or runtime implementations;
there are no stubs, executable ABS bindings or forced unresolved links.
The link succeeds and still emits the same150-byte helper without the
target's aligned frame. Thus this control does not explain the discrepancy
or prove that LTCG is required. The linked175-byte caller also canonically
matches through the actual helper and thread implementations.

Full linked-helper canonicalization separately stops at its native CRT GS
cookie global10004094, for which target data replay is not attested. A trial
absolute binding to the game's cookie instead conflicts with the real
`msvcrt.lib(gs_cookie.obj)` definition and is not retained. The independently
observed150-versus149 function extents already establish nonexactness; no
comparison mask or backend relaxation is introduced for this control.

## Reproducible results and saved analysis

```bash
python3 scripts/audit-candidate-boundaries.py 0x004130D0 --json
python3 scripts/build.py --unit gpt-web-network-winsock-shutdown --json
python3 scripts/compare-unit-object.py gpt-web-network-winsock-shutdown build/match-units/GptWeb_NetworkWinsockShutdown.obj --json
python3 scripts/compare-unit-object.py gpt-web-network-winsock-shutdown build/match-units/GptWeb_NetworkWinsockShutdown.obj --address 0x00412FD0 --json
```

The complete comparison intentionally returns1: preparation is115/149
nonexact, while the accepted-only175-byte caller comparison returns0.
All selected COFF relocations replay, including the ordinary peer-removal
call, native IATs and existing caller dependencies. Fresh source/object
hashes and the current unit-input digest are independently checked against
the build record; comparing an existing object alone does not attest a build.
Reports are `build/network-udp-prepare-shutdown-{boundary,build,formal,accepted}.json`
and `build/network-udp-prepare-shutdown-probe-comparisons.json`.
The resolved-link diagnosis is
`build/network-udp-prepare-shutdown-linked-probe.diagnosis.json`.
Private control scripts/sources stay under
`.analysis/network-udp-prepare-shutdown-20261016/`.

The origin rule pins the complete149-byte hash, the exact caller edge, the
peer-removal edge and all three native IAT fields. This promotes one game
function from review to authored/source-present, with no new exact credit
and no new compiler/library exclusion. Only the affected shutdown unit is
replayed; ledger totals are not presented as a fresh aggregate cold replay.

IDA preflight identifies a different executable and is not used for analysis.
One direct Ghidra process at a time, limited to768MiB heap/two CPUs, attests
the executable/program hash, base, entry marker, x86 Windows identity and all
mapped .text bytes. The owner/peer/vector types, complete149/175-byte extents,
private ESI preparation and ECX caller parameter storage, void returns and
zero stack pops are saved and independently checked in a fresh read-only
invocation. Decompiler output remains a hypothesis, especially its aligned
stack aliases. Logs are
`build/network-udp-prepare-shutdown-ghidra-{save,readback}.log`.
