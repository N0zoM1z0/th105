# Boost recursion-info cleanup origin

The target is the pinned Japanese 1.06a executable. `0x00443020` is the
8-byte compiler-emitted implicit destructor of the original Boost regex
`recursion_info`, not an additional authored game function.

The source is the unchanged original Boost public iterator-search
instantiation and its verified header closure. A fresh VC8 compilation
reconstructs all 8 bytes, including the actual tail jump to `match_results`
destruction. The real matcher constructor and destructor each identify this
callback for the same array of 50 elements, stride 68, at member offset 136.
The existing complete lifetime audit replays those owner bodies, both array
sites, original constructor and destructor, and all four full remote exception
scopes. Thus the parent roles identify this small callback; byte equality of
an eight-byte fragment alone would not establish its ownership.

The origin gate invokes the full audit and checks the exact target, source,
compiler and object provenance. This moves one candidate from review to
third-party exclusion. It adds no authored exact function or byte credit, does
not establish the full regex engine, and does not execute exception handling.
See `BOOST_MATCHER_COMPLETE_LIFETIMES_2026_11_02.md` for scope and prior tests.

A separate pre-existing census rule for the Youmu deque had accidentally
retained a three-function/395-byte count despite selecting four anchors totaling
615 bytes. The four original generated fingerprints were revalidated; its
count was corrected to four/615 without changing any of those four origin
rows. A regression test now checks the count against the anchor and ledger.
A scoped census materialization found no overlap or other count errors and
changed only the recursion callback row. Other rules' expensive evidence
validators were not all rerun in that scoped pass.

The scoped callback validator passed with all five original matcher bodies
freshly rebuilt, and the four Youmu anchors passed their generated-origin
validator. Target-independent CI passed 1,024 tests and generated-progress
checks. A full origin-census evidence replay exceeded the 300-second command
limit and is not claimed as completed; its scoped selection/count/overlap pass
and both directly affected evidence validators did pass.
