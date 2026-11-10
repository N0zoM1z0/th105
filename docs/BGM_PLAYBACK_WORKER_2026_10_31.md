# Complete BGM playback-worker source, JP1.06a

The complete playback polling worker at 403B90 is now source-present and
independently authored, but nonexact. This is the first worker, not the already
reconstructed loading worker 403CE0.

Native [403B90,403CD6) is 326 bytes, with 98 instructions, all reachable, 15
calls and one final RET at 403CD5. Whole body SHA-256:
8b33f92a9dbc11c1a586018f99162f8a49cd950c46fa90e45b4299f386340ae1.
Exact COM wrapper 403B50 calls it at 403B5C. The wrapper owns COM initialization
and shutdown; this source does not create another thread or add COM policy.

## Observed policy and data

While the existing service running byte +18 is true, wait up to 16 milliseconds
on event +10, then enter lock +20. Iterate the native checked unsigned-handle
list at +88. For each token, resolve it through manager +38 at 404330. A
missing stream stays in the active list. If stream update 402C10 returns false,
advance normally. If it returns true, append the same handle to retired +A0,
erase its active node using the returned next iterator, and signal event +14.
Leave the service lock only after the active traversal, then recheck running.

Wait and signal return values are ignored, as in the target. No extra running
check, allocation policy, missing-stream removal or recovery path is added.
The loader worker owns subsequent release of retired tokens. The bounded global
view contains only independently observed fields; it is never constructed.

The new data alias names only this worker's observed event/running/lock/manager/
list offsets relative to 7026E0. It does not expand the old BGM base-only
relocation contract or silently unblock the loading-worker unit. Raw native
absolute operands and known checked-list field accesses justify the explicit
offset set. Compile-time offset assertions check the ordinary source layout.

## Comparison and private ABI boundary

The public unit exact-first-bgm-playback-worker compiles ordinary C++ and
replays all source relocations. Its full 331-byte source body versus 326 native
is a mismatch at byte zero: the target has an 8-byte-aligned EBP frame absent
from standalone compilation. No local, padding, volatile state or alignment
directive is added to manufacture that frame.

A separate genuine whole BGM CIL graph includes actual stream start/update/
handoff, codec/readers, lifetimes, handle manager, shutdown, loading worker and
this new caller. With the existing separately compiled unsigned-list library
it emits 337 bytes. Natural single-CIL template visibility instead emits 326
and recovers the actual aligned 8-byte frame. It is still nonexact: native
keeps the list owner in EBX, whereas this source keeps it in EDI and hoists the
element address into EBX before lookup. Most importantly, native 403C1E moves
the stream to EDI before calling update; the compiler-generated source call
uses ordinary ECX. No invented register convention is declared to bridge it.

These are bounded complete-context diagnostics, not canonical exact receipts.
They do not establish equality of neighboring stream providers or justify a
register/type-spelling search. The complete public standalone comparison is
unambiguously nonexact; neither equal CIL size nor recovered frame earns credit.

## Validation and accounting

The new authored-origin rule checks the complete native body hash, exact
wrapper edge and calls to the already source-recovered lookup/update methods.
Only this new origin row is materialized. Fresh affected replay preserves
service linking 4039E0 / 73 and both thread wrappers 403B50/403B70 / 28 each.

Source: src/audio/BgmPlaybackWorker.cpp.

Source functions increase to 1,751; authored ownership to 1,771; review becomes
616, exclusions remain 1,640. Match units become 745. Exact authored remains
1,553 functions / 441,679 bytes. No game/audio execution or global all-unit
rebuild was performed.

## Real token queue context follow-up

After the service lifetime/load recovery, the same worker policy was tested with the
actual BgmHandleResult queues and complete BgmStreamRuntime provider context.
Its326-byte size still agrees, but the first mismatch remains at65: native retains
the list owner in EBX and source selects EDI. Stream update is 918/native943 and
also unaccepted. Both accepted play351 and prepare159 roots remain exact in this
private context. The token type alone therefore does not close the worker. No ABI or
register declarations were added, and the control was restored out of selected
source.
