# BGM loading worker and handle-token consumers

The complete 461-byte403CE0 body is now source-present and independently authored.
Exact second-thread wrapper 403B70 calls it at 403B7C after successful COM
initialization; the wrapper itself owns COM shutdown. The worker does not
create another thread or add initialization policy.

It checks running+18, waits indefinitely on event+14, then drains pending+94.
Before each pending entry it waits one millisecond, resolves the handle and
starts the stream. Success appends the handle to active+88 under the service
lock+20; failure appends it to retired+A0 without inventing another lock. A
missing stream is simply removed from pending. It then drains retired entries,
waiting one millisecond and releasing each token before removing its list node.
The next outer running check happens only after both queues are drained.

The global base 7026E0 and observed offsets are independently grounded in the
existing service callers and raw worker instructions. Source offset assertions
bound its lock, manager and queues. The narrow global view makes no claim about
unobserved service construction or destruction. The two source methods with
private native entries remain ordinary C++ declarations, not fake ABIs.

## Focused source verification and current limit

src/audio/BgmLoadingWorker.cpp compiles in exact-first-bgm-loading-worker.
Its canonical object replay stops at the existing global-data contract:
relocation.dir32.addend_unverified for the running flag at service+18.
The old known-symbol anchor proves only the service base. Its offset allowlist
is not widened merely to pass this candidate. No bytes are accepted.

A separate genuine full CIL graph includes existing stream start/update/handoff,
reader/codec providers, constructors/destructors, pool acquire/lookup/release,
shutdown and actual thread-wait methods. The worker compiles to 461 bytes with
the native aligned frame, and start naturally obtains its EAX receiver. The
worker still differs in STL scheduling/register use and loop alignment. Start
345/native358, update 918/native943, handoff 761/native806 and PCM 251/native252
also remain nonexact. Matching sizes are not acceptance. This diagnostic graph
remains private rather than replacing independently accepted source contexts.

The complete raw call scan finds manager-release edges at 403571,4035B9,40360D
and 403E53. The first three are shutdown, the fourth is this worker. Adding only
the actual shutdown source and wait provider closes its natural aligned frame
but not the release ABI. The combined worker graph is a distinct control, not
an invented caller intended solely to change register allocation.

## Word-token and free-list source corrections

Public BgmStreamAllocation.cpp now reads the packed token through the existing
two-WORD ResourceHandleToken view. This models native low/high word reads,
rather than forcing a new aggregate-by-value interface. Native caller pushes
remain ordinary scalar token values. A genuine value-class argument control
introduced extra temporary construction at callers and was not selected.

Release keeps the 16-bit slot until converting it for the unsigned free-list
entry. Pool reuse uses erase(--end()), reflecting the native checked iterator
and erase helper call, rather than the old inlined pop_back body. The source
constructor-unit allocator becomes 552/native401; the larger lifetime context
has 492/native401. Lookup 195/native196 and release 179/native184 remain
unaccepted. Full focused replay preserves the existing 89-byte constructor and
220-byte destructor, including all three destructor cleanup states.

Evidence:

No new exact ledger entry, broad gameplay test or all-unit rebuild is claimed.

## Shared list-library boundary follow-up

The existing genuine src/library/UnsignedIntList.cpp instantiates only the standard
unsigned list; it contains no authored game wrapper. Using this same COFF library
context already employed by the accepted network release preserves its ordinary
shared helper interfaces. In the public stream-lifetime unit it naturally recovers
release's native 8-byte-aligned frame, without any source alignment or extra local.
Release becomes 183/native184; allocator 494/native401 and lookup 195/native196 remain
nonexact. The private vector::at argument and register scheduling still differ. The
constructor-only unit is unchanged.

Applying that shared library to the larger private worker graph gives 477/native
461, so that separate worker control is not selected. No authored source is
moved into a library, no extra helper credit is added and no source signature is
fabricated to imitate the private vector boundary.
