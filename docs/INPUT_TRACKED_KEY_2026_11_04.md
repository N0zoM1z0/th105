# Input tracked-key registration

The Japanese TH105 1.06a `InputStateTableStorage::add_tracked_key` body at
`0x0040A6C0` is 202 bytes (SHA-256
`d216475e7dc02c57563922b36657dd6c8c3d58912cea295102f81b1b839f7839`).
It scans the checked byte vector and appends a key only when no matching key
exists. Scene bootstrap calls it repeatedly; two native call sites are pinned.

The existing shared source now has a focused ordinary VC8 comparison unit.
Its complete 199-byte body has SHA-256
`fa9003d09a87e2a094f18194f995e48242dcf7557bd77cd400aace4ca3da994d`.
It is nonexact from the entry: the native body aligns its stack while the
ordinary source does not. No padding, fake local or special register directive
is used, and no exact credit is awarded. The separately selected input-state
update remains exact in its real CIL unit.

A bounded x86 observer checks six valid vectors with spare capacity: empty,
existing and new keys, including byte values 0 and 255. Native and source
produce the same vector and stack cleanup; a duplicate-gate mutation is
detected. Four additional full-capacity fixtures check the native and source call-site
arguments and return behavior against a modeled insertion helper, including an
empty vector and a duplicate that must not call insert. The model does not
execute the real insertion or allocator. Allocation failure, invalid vectors
and full-game behavior remain untested.

A separate real-source CIL diagnostic builds this method with the actual input
unit and CRT. Its comparison stops at a newly inlined private vector insertion
helper whose native destination is not established. It does not justify a
fabricated binding, exact credit or a claim about the shipped full-program link.

## Actual insertion execution, 2026-11-04

`scripts/audit-input-add-key-real-growth.py` now builds the genuine input
source CIL graph and executes its actual emitted insertion body alongside the
original target registration and insertion bodies. Six bounded full-capacity
cases cover empty and nonempty vectors, growth factors including 4 to 6 and
6 to 9, and duplicate suppression. The resulting bytes, size, capacity,
allocation/copy/free events and stack cleanup agree with an independent model.
A mutated duplicate gate is detected. The allocator and CRT memory operations
are still mocked; allocation failure, invalid vectors, concurrent use and
full-game execution remain untested. This execution evidence does not resolve
the native/source helper relocation binding or make either body byte-exact.
