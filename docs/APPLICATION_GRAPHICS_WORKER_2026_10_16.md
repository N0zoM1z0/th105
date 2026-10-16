# Application graphics worker: complete source, nonexact 401/401

## Observed extent and ownership

The only target is original Japanese TH10.5 v1.06a, SHA-256
`56350024879199861579c11b0e1c67b9590e10a8d40cd5996b109deec9afca7e`.
`Application_graphics_worker @ 4084F0` physically ends after RET at `408680`,
followed by INT3 padding. Complete body SHA-256:
`50285919fdb10a3ff2191ae5c4df8ae23e316a62029898070157495d4c9f9ab2`.
Exact callback `408820` calls it at `40882C`, without explicit arguments or a
register receiver. The worker establishes singleton `702820` itself and calls
exact `present_d3d_frame @ 401060` at `40858F`. Application-owned rendering,
event and scene lifetime establish authored ownership independently of matching.

The ordinary CFG reaches383 bytes / 131 instructions, leaving
`[408649,40865B)` unexplored. It is not padding: target GS/EH handler `6BD7A0`
loads FuncInfo `6E3D84`, which selects the typed catch at `408649`. The catch
sets receiver running+4C to zero and returns continuation `408656`; that
continuation restores the saved singleton pointer and joins final cleanup.
These six instructions / 18 bytes close the complete401-byte,137-instruction
callable. The natural VC8 COFF owner independently has that same401-byte
extent, including its local catch funclet and continuation.

## Exception evidence

| Structure | Observed content |
| --- | --- |
| GS/EH handler `6BD7A0`,27 bytes | Cookie check `689D25`, FuncInfo `6E3D84`, tail jump `6899E7` |
| FuncInfo `6E3D84` | Magic `19930522`, two states, unwind map `6E3D50`, one try block `6E3D70`, EH flags1 |
| Unwind map `6E3D50` | Two `(-1, null action)` entries |
| Try block `6E3D70` | tryLow0, tryHigh0, catchHigh1, one catch at `6E3D60` |
| Catch descriptor `6E3D60` | adjectives0, type descriptor `6FA40C`, no named catch object, handler `408649` |
| Type descriptor `6FA40C` | type_info vptr and decorated type `.H` |

Compiling the ordinary `catch(int)` source emits `??_R0H@8` with the same `.H`
type spelling, corroborating the raw typed descriptor. The catch has no
destructor or lock-unwind actions. It neither closes the local pause event nor
unlocks a critical section before common cleanup. Preserve those observed
paths; do not replace them with catch-all or RAII cleanup.

Hashes of the combined EH tables `[6E3D50,6E3DA8)` and 11-byte type descriptor:

```text
fac731285ddea78fba30f0dc5a24d5a7df4abc139309445823dfe33f102c3ad2
0d8f89ba58c71f8fbd48b0d0a622d5adaf18d2abfc77adb54bd71081fc26fe5c
```

## Behavior and layout

The worker creates an unnamed, initially unsignaled automatic-reset event at
application+60. The tested byte is **application+2D**, startup option+25;
it is not application+4D. Graphics initializer `4147E0` independently uses
that same option to choose presentation interval1 versus `80000000`, supporting
its vertical-sync role without renaming the shared startup header.

When true, the worker tries native scene critical section application+98,
renders the previous scene pointer at+7C, and conditionally renders fade+78
through slot+10. Successful render results call `401060` and increment+44.
Failed locking/rendering waits one millisecond on event+60 before retrying.
A real wait-status boolean persists through consecutive successful renders;
the scene/fade result remains a separate boolean lifetime.

When false, a second local automatic-reset event supplies one-millisecond
delays. The worker waits indefinitely on event+60, checks running+4C, then
tries at most16 swap-chain submissions. Byte `6FA246`, backend critical
section `7036A4` and swap chain `7036C4` gate the attempt. Present flags are1;
only HRESULT zero clears the byte, releases the lock, increments counter+48
and exits the retry loop. A failed attempt releases any acquired lock and
waits on the local event. The next indefinite wait again uses event+60.
Normal exit closes the local pause event, then the shared event. Catch(int)
clears running and reaches only shared-event cleanup. Events remain stored
after closing; no new nulling or failure guards are added.

`src/platform/ApplicationGraphicsWorker.cpp` retains these native widths,
typed scene/fade calls, manual lock ownership, retry limits and exception
behavior. Only the accessed application prefix is modeled. Existing shared
types, headers and flags are unchanged; two new mappings attest the singleton
fields and complete GS/EH handler. The established reset-flag field alias is
reused with its existing addend permission.

## Comparison and unknowns

```bash
python3 scripts/audit-candidate-boundaries.py 0x004084F0 --json
python3 scripts/build.py --unit cross-v106a-application-graphics-worker --compare --json
```

The raw boundary report deliberately exposes the18-byte EH-only interval;
the exception evidence above reconciles it. Formal report
`build/application-graphics-worker-formal.json` gives complete candidate401
and target401 with first difference **+43 hex / +67 decimal**. After full
relocation replay,20 bytes differ:16 in the EH state0 store / sync-byte test /
event-publication ordering, two selecting the pause-event argument register,
and two selecting the catch receiver register. This is **nonexact**; no match
row or exact bytes are added.

Natural render-result lifetime and failed-Present-first branches recover the
target register topology and loop layout. Moving event creation into the try
region moves the state write before the call, unlike the target; a returned
handle published inside try still leaves the sync test hoisted. Those controls
do not resolve original EH scheduling/TU visibility and are retained privately.
No assembly, forced register, synthetic local or altered shared contract is
used. The original source spelling, class partition and compiler phase remain
unknown; the state-store difference does not prove a semantic exception-policy
difference between these source variants.

The authored-origin rule independently replays the incoming exact callback,
outgoing exact presentation call, whole body hash, critical data operands,
unwind states, typed catch and table pointers. Only this origin row changes;
unrelated fingerprints are preserved after scope/rule-overlap checks.
Direct Ghidra initially omitted the catch in its decompilation, retained only
as a hypothesis. Independently attested save and fresh read-only sessions
verify the complete body, EH/type data hashes, cdecl/void no-argument contract,
zero purge and catch label. Scripts stay under
`.analysis/application-graphics-worker-20261016/ghidra-scripts/`, logs under
`build/application-graphics-worker-ghidra-*.log`; processes use768MiB and two
active processors. No unattested IDA data or factory adapter is used.
