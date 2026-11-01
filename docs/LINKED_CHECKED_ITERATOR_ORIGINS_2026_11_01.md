# Complete checked-tree increment provenance in genuine CIL contexts

Two original VC8 checked-tree iterator increment bodies now have fresh complete
canonical97-byte witnesses, separately classified as compiler-generated:

- Package41D2B0:
  17e2cdf3e83981c53d803c51a6590a4442eeb8ca82a70b0c2b10a6d65f240edb.
- Network4143E0:
  8b0ef744e805d51e25015455559a4d8b48d1dcb3651567a13d859666609f91b8.

No C++ source, header, compiler flag, private receiver declaration or export
set changes. Original VC8 templates in the existing package-store and UDP
lifetime sources naturally produce their private receiver convention.
The identical network integer-map specialization is another source witness,
not a second physical native function or proof of unique nominal type.

## Complete control flow and error helper

The iterator verifies its owner/node before following right/left/parent links.
The two real address fields are an E8 call at+5 and an E9 error exit at+19,
both to __invalid_parameter_noinfo68A143. All other bytes are retained.
The named source helper must be uniquely owned by libcmt:invarg.obj, and its
entire16-byte wrapper equals the pinned native body, SHA256:
cd349dae43dbf63016fe6ea9339dab15c59041e3224e48cf8a53004224b45e77.
The preceding source entry is independently named __invalid_parameter in the
same original runtime object. No new authored/helper credit is inferred.

The separate checked-iterator validator accepts only the reviewed97-byte
_Inc tree family. It requires a unique actual source-CIL symbol, forbids a
forced export, checks complete source/native CFGs including the one named
external error exit, rejects other calls, HIGHLOW/data/segmented references,
resolves both real fields, and compares every canonical byte. Rebinding across
the full candidate inventory must produce exactly one native occurrence.
There are zero masks and zero unequal bytes.

The old relocation-free pure-container validator remains unchanged; it still
rejects calls and external tails. This is a separate stronger call-identity
contract, not permission to apply arbitrary callee mappings to masked leads.

## Fresh roots and reproducibility

Each rule performs a fresh pinned normal CIL build and verifies existing exact
roots first:
- Package41B8C0/163 and41B980/228.
- Network413820/98 and413780/145.

The previous pure package/network rotations also freshly pass in this scope.
The larger UDP owner and other nonexact neighbors are not promoted.

    taskset -c 0 nice -n 10 scripts/repo-python scripts/linked_checked_iterator_origins.py vc8-linked-checked-package-iterator-106a
    taskset -c 0 nice -n 10 scripts/repo-python scripts/linked_checked_iterator_origins.py vc8-linked-checked-network-iterator-106a

Per-rule reports are under build/origin-anchors, using the anchor manifest's
stem plus -linked.json. They include target/source image/MAP/build receipt,
validator and anchor hashes, full exact-root reports and both iterator proofs.
Scope receipts:build/frontier-linked-tree-increment-20261101.

Twelve synthetic regression tests cover full comparison, forced exports,
wrong CIL/runtime ownership, incomplete/changed helper, wrong error target,
extra calls, HIGHLOW data, full-inventory duplicates and schema/size waivers.
They contain no native or proprietary compiler instruction fixtures.
Default CI312 passes; no broad native replay is performed.

Excluded1804/review416; authored1807/source1787/mapped1814/units766 and
exact1585/449721 authored bytes remain unchanged.
