# Weather and effect pool acquire: complete canonical matches

437520 and4379D0 are each463/463 exact in the reproducible unit
exact-first-weather-effect-pool-acquire. Each native body contains137 decoded
instructions, all13 direct branches stay within its body, and the complete
GS/EH epilogue ends in RET4. Both allocation and recycled-slot paths are covered.
This adds two authored roots and926 bytes, not their helper implementations.

## Source and new evidence

WeatherEffectPoolAcquire.cpp uses the actual CHandleManagerEx vector/list/lock
layout and EffectObjectBase hierarchy. Allocation extents are180 and178;
unknown trailing fields remain uninitialized. Generation wraps to1 aboveFFFF,
the two16-bit handle fields retain their store order, and the recycled path
removes the free-list node before recording generation and placement construction.
Checked vector accesses and the target's allocation behavior are preserved.

The real ObjectHandleValue member initializes the handle before CObjectBase sets
state1. Actual EffectSprite.cpp and FighterActionScratch.cpp definitions supply
constructor semantics and normal compiler exception inference. This independently
resolves the historical constructor-order blocker. The old opaque declaration
with an added throw() contract is not selected. No new noinline, forceinline,
assembly, register constraint, fake lifetime, aligned storage or bytes are used.

Canonical hashes:
-437520:bb7a7deaf9d5430a3487e4be7ac7dcecc1673d4fe7b9f10ffdf3a02fc77a14d5
-4379D0:6ed6323d87781cbf58b3cb24f888bb346141bc990351b11b4a4c0f356606961a

## Cleanup verification and provider-context limits

Both roots share the native cleanup6B7CB0 and handler6B7CB8. Separate strict
DIR32/REL32 replay of the formal object matches all35 bytes, the36-byte FuncInfo
at6DDDF8, and the8-byte unwind map at6DDDF0. The metadata regions are checked
separately because their physical ordering differs between COFF and the PE.
The cleanup loads the saved guard at EBP-10 and tail-calls401870.

The real guard destructor in the root TU is7 bytes, forwarding through40AC40.
It is NOT claimed exact at401870. An independent build of the same source with
actual CriticalSectionWrapper.cpp visible emits the native13-byte destructor
exactly, including the real LeaveCriticalSection IAT call. This verifies the
ordinary thiscall provider identity for cleanup relocation, not a selected
replacement of the root TU: that visibility control makes both roots466 bytes
and is rejected for root acceptance. No import or code byte is fabricated.

Likewise, constructor421FF0/422040 inline differently in this context; they
receive no new exact credit. Their ordinary call contracts and actual source
bodies are retained. The real scratch initializer435110 separately matches67.
This checkpoint does not assert a fully byte-identical link of every emitted
provider, nor promote any nonexact helper.

## Reproduction and scope

scripts/repo-python scripts/build.py --unit exact-first-weather-effect-pool-acquire
--compare --json

The canonical body gate is unchanged. Actual source and known typed relocations
reproduce every byte of each complete root.

No existing shared source or header changes. Existing exact receipts therefore
remain valid; only this new unit is rebuilt. The two origin rows use the existing
canonical baseline after acceptance; unchanged rules are not cold-replayed.
Progress and tracking are regenerated and CI gates the local commit. No push.

## Unsigned token storage, November 10, 2026

Both acquire paths now write the low slot word and high generation word through
byte copies, then read the generation from the actual unsigned token. This
removes the unrelated `EffectObjectHandle` lvalue over the caller's unsigned
storage. The two native stores, their order, and the post-allocation or
post-erasure generation reload remain unchanged.

Fresh VC8 builds preserve both complete 463-byte roots. All 389 non-debug
sections and 676 relocations are identical before and after, including the
constructors and cleanup providers. The shared 35-byte cleanup/handler and
36-byte FuncInfo plus 8-byte unwind map also compare directly with the target.
The manifest's include closure contains only this unit; no shared source,
ledger, input pin or Factory acceptance changes were made.

A preliminary short-copy read emitted a redundant zero extension and made each root
six bytes longer. Reading the unsigned token's high word avoids that conversion.
Copying the source words directly, rather than converting through short temporaries,
preserves the native word loads.
