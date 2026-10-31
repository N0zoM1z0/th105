# Effect group lifetime: two complete authored matches

The target remains original Japanese TH105 v1.06a, SHA-256
56350024879199861579c11b0e1c67b9590e10a8d40cd5996b109deec9afca7e.

## Accepted bodies

- EffectResourceGroup constructor422AE0:131/131 exact, SHA-256
  c239bf82be8b37b1b979760712cecabf841b0c7001bf1685819ec3dd63ffa24c.
- EffectResourceGroup destructor422660:135/135 exact, SHA-256
  659c36e18d9cd9aad6357657e888c17261c1aafd4e61e786834f76d73b362fbf.
- Existing complete effect loader437EC0:2528/2528 freshly remains exact.

The32-byte group contains the recovered vector<FrameData> at+4, byte flag14,
and previous/next pointers18/1C. The current target RTTI names it PatternData:
vtable6C0998, zero-offset COL6D7888, type descriptor6E64A4. The existing
scalar-deleting-destructor origin evidence pins its first entry4226F0 and
the direct call to422660. The application loader independently uses both
lifetimes. Original C++ nominal spelling remains unknown.

Both source bodies explicitly call frames_04.clear(). Constructor code first
constructs an empty vector then executes its checked erase path; destructor
executes checked erase before the member's ordinary _Tidy. These extra explicit
clear operations are not default compiler-generated lifetime glue. The original
VC8 STL naturally emits all register allocation, guards and stack/EH prologues;
no inline directives, ABI changes, assembly, fake locals or modified headers
are involved.

EffectResourceGroup.hpp extracts the existing shared declaration and size check.
The loader includes only this declaration, preserving provider visibility.
EffectResourceGroupLifetime.cpp supplies the two actual definitions.

## Comparison scope

Unit exact-first-effect-group-lifetime compares both complete bodies. The
canonical comparator resolves actual vector erase4221E0 and _Tidy422260,
invalid-parameter and cookie-check providers. New address bindings pin the
actual first vtable entry and the complete27-byte handler entry through its
terminal jump for each root:6B72BB and6B723B. No relocation bytes are ignored.

This is the established complete COFF-function contract. It does not additionally
claim that all remote EH metadata has a separate linked replay. The new entry
bindings preserve full observed handler bytes instead of only a prefix.

The declaration extraction's only old accepted source consumer is
exact-first-effect-resources, freshly exact2528. Private initial comparisons
were followed by the formal public manifest builds before ledger promotion.
Receipts: build/frontier-effect-group-lifetime-20261031/formal.json and loader.json.

Authored exact totals gain two whole functions and266 bytes:
1558 functions /444502 bytes. Source1755, authored1775, mapped1782,
excluded1655, review597, units750. Scalar deletion, implicit copy and STL
providers receive no new authored credit.
