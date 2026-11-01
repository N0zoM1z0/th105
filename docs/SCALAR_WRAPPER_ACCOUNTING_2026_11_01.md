# Scalar deleting wrapper accounting correction

## Result

141 compiler-generated scalar deleting wrappers, totaling 4,691 bytes across
50 existing ordinary VC8 owner units, have been removed from authored source
and exact totals. Every complete canonical witness remains reproducible.
This corrects historical attribution; it does not remove reconstructed code.

Corrected ledger: 1,445 authored exact functions / 445,336 bytes; 1,647
source-present; 1,667 authored candidates; 1,949 excluded; 411 review;
1,815 mapped functions; 768 units. Historical totals including these wrappers
are superseded, including the earlier 1,586 / 450,027 checkpoint.

## Evidence

The pinned Japanese v1.06a target and pinned VC8 SP1 compiler were verified.
Every one of the 50 actual owner units was freshly compiled serially on CPU0
at nice10. The selected actual emitted COFF symbol must start with `??_G`;
legacy descriptive selectors are not themselves accepted as ownership proof.
The full emitted function section tail and canonical native body must have
identical size and SHA-256, with no partial-byte credit or masks. Native bodies
end in RET4. All observed primary RTTI owners are recorded, including shared
bodies and the DirectSound second-slot cases following their initializers.

The initial audit found 107 explicit selectors and 11 legacy aliases. A new
tracking guard caught another 23 entries whose manifest addresses used different
hex spelling. Numeric address matching recovered these, producing the final
141 / 4,691 set. All 50 units were then rebuilt again with the final pinned
anchor manifest and validator. No intermediate total is an accepted checkpoint.

`config/vc8-scalar-wrapper-origin-anchors.toml` records every extent, digest,
unit, emitted selector and native RTTI/vtable witness. The separate validator
`scripts/scalar_wrapper_origins.py` requires current compiler/object/input
provenance, complete canonical comparisons and valid native owner structures.
Receipts live under `build/origin-anchors/scalar-wrappers/`. The origin rule
`vc8-scalar-deleting-wrappers-106a` selects exactly 141 bodies / 4,691 bytes
and passed its full evidence replay after ledger correction.

## Accounting and regression protection

Only these wrappers move from matching/authored to identified/compiler-generated
excluded. Source files, match units, reccmp names and relocation bindings remain.
`implemented.csv` and `matches.csv` no longer confer authored credit on them.
`validate-tracking.py` rejects scalar/vector deleting compiler selectors in the
authored exact ledger. Fourteen synthetic tests cover selector aliases, numeric
address spelling, pins, complete extents, actual probe profiles, readonly RTTI,
primary ownership, slot order, canonical reports and stale provenance.

Reproduce a fresh selected owner with:

    taskset -c 0 nice -n 10 scripts/repo-python scripts/scalar_wrapper_origins.py --unit UNIT

Recheck all current receipts without an implicit native rebuild:

    taskset -c 0 nice -n 10 scripts/repo-python scripts/scalar_wrapper_origins.py --check

No native source changes, global exact rebuild, progress padding or push.
