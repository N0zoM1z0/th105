# ResultList population exact, JP1.06a

4478B0 is canonical exact1133/1133, SHA256
 efe21868756deb6404d589619792708ac47ca758f7f585c73c637ddb100fd343.
The full body ends447D1C RET0; no cold branch or indirect jump table is omitted.
Vtable6C2058 owns populate through slot+4 at6C205C. COL6D8494 independently
names ResultList and a single CFileList base at displacement0. Existing exact
constructor4471E0, normal destructor447260 and scalar447510 close its lifetime.

## Actual owners and behavior

The new method-facing view inherits the already recovered CFileList. It owns
the native string deque+B8, int deques+CC/+E0 and short deque+F4 after the
character selector+B4. Size108 and field offsets are asserted. It is never
allocated as a replacement full nominal class. The method clears visible rows,
+B8, +CC and+F4; it deliberately does not invent a clear of+E0.

ScoreData+198 contains twenty checked record vectors; the active roster uses
fifteen. The
method rereads the score singleton for the loop bound and checked indexing,
retaining the native invalid-parameter path rather than introducing at()/an
out-of-range exception. A real32-byte ProfileDeckResourceGroupNative20 owns
the spell map/handles. Its constructor42E880 and destructor42E900 are already
independently exact; the load/lookup/cleanup methods use the observed shared
SpellDataOwner prefix, without constructing its larger unrelated tail.

For a new record character, the loader uses flags1/0. A missing spell name
skips the row. Otherwise the real1024-byte buffer receives either the full
name, E/N/H/L column, current/maximum and signed frame-time formatting, or the
native empty-record format. Replay metadata appends the converted spell ID
or signed -1. Character/column int values are appended to their own deques.
The resource owner is cleared before virtual finalize and then destructed.

## Source correction that closes the old stop

The old unselected source hand-expanded a string-deque push_back and reused
one named ResultString28 for two appends. Native447AD5..447BA4 constructs and
destroys one row-buffer string, then447BA9..447C81 independently constructs and
destroys a second one. Real rows.push_back(std::string(row)) and a separate
indices.push_back(std::string(row)) preserve these two lifetimes and their
checked allocator/EH behavior. No manual STL internals remain in this TU.

An initial natural-container view with named references to all the owned
members emitted1141 bytes by hoisting their addresses. Direct typed members
restore the exact1133-byte stream without forced inlining, register state,
extra locals or padding. The two unchanged format literals and full46-byte
native handler6B9C0F receive explicit target-attested relocation keys.

## Focused replay

scripts/repo-python scripts/build.py --unit exact-first-result-list-populate --compare --json

Receipt:build/frontier-result-list-populate-20261029/formal.json.
Only the previously unselected ResultListPopulate.cpp is replaced; shared
headers and accepted lifetime/menu/caller units remain unchanged. The method
gets authored exact credit only after the full canonical zero-difference replay.
Generated string/vector/deque helpers remain dependencies, not new authored
roots. There is no whole-corpus rebuild or unrelated test expansion.

## Shared score record owner, 2026-11-10

The result list now reads `ScoreData::records_198` and `ObservedRecord24`
directly, eliminating its duplicate fifteen-vector owner and duplicate record
schema. The formerly unknown DWORD at record+4 is named `difficulty_04`:
score defaults stores the 0..3 difficulty index there, and native result
formatting reads it at `0x447A5E` to select the E/N/H/L label at `0x447A64`.
The producer's sequence count, observation count and maximum frame count now
retain their shared names in the consumer rather than maximum/current/frames.
The original two singleton lookups per iteration and all helper calls remain.

Complete `0x4478B0` remains 1133/1133 exact with its previous canonical hash.
All fourteen affected source-dependency units were rebuilt. Every executable
section, data byte and executable relocation remains unchanged. Only two
vector-helper debug relocations in the result-list object change their nominal
record type from `ResultRecord24` to `ObservedRecord24`; all other whole-object
section/relocation dumps are identical. The existing nonexact consumer roots
remain nonexact at the same locations. Focused CI passes.

Reports: `build/frontier-score-record-owner-20261110/result-consumer/`, compared
with its `after/` baseline. This preserves local exactness; no new Factory
acceptance or authored-byte count is claimed.
