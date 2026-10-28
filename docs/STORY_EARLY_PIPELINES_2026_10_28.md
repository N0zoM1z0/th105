# Story early phase pipelines

Canonical Japanese 1.06a raw PE observations and focused VC8 replay accept two
complete authored bodies: 0x00471590, 59 bytes, and 0x004715D0, 88 bytes.
The RTTI-owned CBattleManagerStory table at 0x006C1374 contains them at
slots +0x10/+0x14 (pointer cells 0x006C1384/0x006C1388).
Both bodies have a single final return and all decoded instructions are
reachable. Extents are 471590..4715CB and 4715D0..471628, exclusive.

The first resets fighter fields through 46B080, invokes the existing scenario
predicate 45A290 through the current battle-phase global, and transitions to
phase 1 if AL is zero. Action, position/status and post-update phases follow.
The second decrements the signed InfoManager counter at this->info_8c+494
only when nonzero, invokes reset vslot40 and fighter reset46AFF0, then action,
collision, position/status and post-update phases. Pending08 causes transition
to phase2. Both return integer zero. Negative counters are not clamped.

Ordinary implementations use the established Story owner and caller-backed
helper views. No assembly, fake ABI, extra guards, storage or compiler changes
are introduced. The only consumer of BattleManagerStory.hpp is this TU;
all five registered unit functions compare exact, including unchanged
203/157/309-byte peers. The new authored increment is147 bytes.

    scripts/repo-python scripts/build.py --unit cross-v106a-battle-manager-story-core --compare --json

Receipt: build/frontier-471590-20261028/formal-build.json.
Origin rules were checked for both previously unknown roots before acceptance.
No generated or library functions are credited.

The independent typed story-owner trial for update471930 was byte-neutral:
321/native323, first+67. Its retained source and exactness status are unchanged;
private receipt build/frontier-471930-20261028/typed-owner.json records this
negative result.
