# Complete original Boost matcher lifetime scopes

This closes the explicitly retained prefix-only remote-EH limitation in
BOOST_PUBLIC_SEARCH_2026_11_01.md. The original public search instantiation and
its pinned 184-file Boost header closure are unchanged. No application source,
vendor source, compiler flag, provider binding or accounting row is changed.

## Whole original code and cleanup regions

- Public search 4440A0/235: cleanup and handler 6B9560/44, metadata 6DF420/44.
- Matcher construction 443B30/243: 6B9400/73 and 6DF334/60, three states.
- Matcher destruction 443AA0/129: 6B93C0/49 and 6DF300/52, two states.
- Match-results destruction 442F40/141: 6B92F0/35 and 6DF254/44, one state.
- Recursion-info cleanup 443020/8 and construction 443A00/44 are complete.
- Real scoped_ptr cleanup 4439E0/25, repeater_count cleanup 4422E0/12 and
  sub-match vector cleanup 435F90/42 are independently canonical support.

All seventeen disjoint regions total 1280 bytes. Each full metadata region
contains its entire unwind table followed by all nine FuncInfo words. All
previous states, action addresses, source section boundaries, relocation roles,
handler locations and named terminal E9 targets are checked. No unwinding
behavior was executed through the OS; this is static source reconstruction.

The original recursion_info has id, return address, results and repeater-stack
members and no user-declared destructor. The source matcher owns fifty entries.
Both real array sites agree: construction 443BD5/31 and destruction 443AC8/29
use count50, stride68, member offset136, cleanup443020 and constructor443A00.
The constructor's remote third cleanup repeats the real array lifetime. This
is not a generated test caller or an invented helper implementation.

## Verification

The new audit requires current source/compiler/object provenance and re-verifies
the original public instantiation and vendor inputs. It replays all five formal
library bodies plus four whole helper bodies and all four complete EH scopes.
Eight structural tests include corruption of every byte of both array sites.
A separate actual-target mutation sweep flips each of the1280 distinct bytes;
all1280 are rejected by the real audit. Do not add overlap with older proof
scopes as additional code coverage.

Run serial CPU0/nice10 using scripts/repo-python:
- scripts/build.py --unit boost-regex-iterator-search --compare --json
- scripts/audit-boost-matcher-lifetimes.py
- scripts/ci.py

Private receipts and checkpointed mutation driver are in the corresponding
build/.analysis frontier-boost-recursion-cleanup-20261102 directories.
No new inventory entries or authored exact credit:1429 functions /443911 bytes;
source1634, authored1653, excluded2072, review302, mapped1821, units808.
The8-byte callback remains support here; this audit does not silently change
its origin row, prove find/construct_init implementations, or claim the entire
regex engine is exact.
