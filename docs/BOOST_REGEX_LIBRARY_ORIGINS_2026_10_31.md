# Original Boost narrow-instance library evidence

## Scope and source identity

The original narrow-character instance translation unit from the compatible
Boost 1.40 reference supplies definitions absent from the connect-menu object.
It is compiled unmodified through scripts/probes/BoostRegexInstancesOrigin.cpp,
using the existing verified 184-file header/license package and VC8 SP1 /O2 /GS.

Official immutable source:
https://github.com/boostorg/regex/blob/fa1ef1dfd4136803625e49853289ade7c2ddff0a/src/instances.cpp

The original file is 697 bytes, Git blob
69d72ad6e15e823c1a6f1d434c69e8f437513f01, SHA-256
44e69a60e7643db548f2c7c1fdae2807d2b8409f206cd1fe80620ae6b42d5371.
Its original BOOST_REGEX_SOURCE and BOOST_REGEX_NARROW_INSTANTIATE definitions
are unchanged. No local substitute implementations, native bytes, inline
assembly, ABI forcing, or optimizer barriers are introduced.

The source stays in ignored .tools/upstream/boost-regex-1.40.0-src, with its
original license. Explicit bootstrap/check:

    scripts/repo-python scripts/upstream_boost.py --fetch --instances
    scripts/repo-python scripts/upstream_boost.py --instances

The verifier pins size, Git blob, and SHA-256 before use or write, rejects changed
existing files and escaped paths, and adds the original CPP to build input
hashes. Native builds never fetch. Header-only users retain the existing path.

## Classification evidence

A full inventory search of original-source COMDAT fingerprints selected 148
previously reviewed, uniquely located complete bodies, totaling 24,230 bytes:

- 87 Boost definitions, 12,756 bytes, third_party / boost_regex.
- 61 VC8 std or stdext definitions, 11,474 bytes, compiler_generated / std.

The checked-in anchor manifests pin original decorated symbols and complete
native sizes. The two rules also pin inventory names and native body hashes.
Both rules passed the existing generated-origin validator, including relocation
masking, inventory uniqueness, minimum non-relocated coverage 0.70 and minimum
24 non-relocated bytes. These are provenance fingerprints, not a claim of fully
resolved relocation equality for all 148 functions.

Seventeen ambiguous multi-address source shapes were not selected. Multiple
source instantiations identifying the same native body receive one census row.
At 6A91D0 (247 bytes) and 6B4250 (209 bytes), the original source section has
one trailing CC alignment byte; the corresponding following target byte was
also verified CC. The existing maximum-one-byte alignment gate is retained.
No callable instruction is truncated.

Three separate complete canonical replays pass: flags(unsigned) setter
6A0CC0 / 25 bytes, parse_all 6A0D50 / 26 bytes, and is_bad_repeat
6A10F0 / 69 bytes. The latter resolves the actual __allshl destination 6B6D00,
already independently classified as VC8 runtime. These 120 bytes are library
witnesses, not authored progress.

## Boundaries and validation

The now-defined basic_regex::do_assign at 6B4430 is 466 source bytes versus
412 native bytes. It remains nonexact and unselected. A compatible historical
reference does not uniquely identify the shipped Boost release.

Only the two new rules were natively revalidated for this increment; unchanged
census evidence was retained. No cold global origin rebuild or all-unit exact
replay was performed. The affected original-header connect main-state unit was
also rebuilt and compared, alongside the new instance witness unit.

Authored exact remains 1,553 functions / 441,679 bytes; source 1,750 and authored
ownership 1,770 are unchanged. Excluded library/compiler/runtime functions
increase from 1,440 to 1,588; review decreases from 817 to 669. There are 744
match units. No authored completion credit is assigned to this classification.

Final affected replays: connect root 827 and all eight providers 1,116 bytes
pass; the three instance witnesses pass 120 bytes. Default target-independent
CI passes all 166 tests, including original-source flag and tamper checks.
Generated progress and git diff --check pass.

## Follow-up: complete equivalence groups

The initial 17 ambiguous source fingerprints are not 17 independent native
functions. Deduplicating their complete hit sets yields nine groups / 26
physical bodies / 4,047 bytes. A subsequent, separate increment selects these
only through the existing explicit equivalence-group validator:

- VC8 std tree erase: 740 bytes at 43D980 and 6A88E0.
- VC8 std tree insert: 185 bytes at 43DD10 and 6AE090.
- VC8 std tree find: 122 bytes at 455A00, 6A5630, 6A58B0.
- Boost exception clone construction: 177 bytes at 6A66F0, 6A79C0, 6B4F00.
- Boost shared-count construction: 142 bytes at 6A5380, 6B1B00, 6B3CF0.
- Boost throw_exception: 96 bytes at 6A9710, 6ACCD0, 6B52E0.
- Boost error-info-injector destruction: 87 bytes at 6A4CA0, 6A4EE0, 6B4C90.
- Boost enable_error_info: 67 bytes at 6A73E0, 6A8720, 6B51B0.
- Boost enable_current_exception: 31 bytes at 6A8770, 6A96F0, 6B5200, 6B5440.

Each group must reproduce the entire hit set across all 4,027 inventory rows.
Selecting only its first address would fail. This establishes library family
ownership, not the precise concrete template argument at every address.
The representative symbols remain genuine original-source implementations;
no RTTI identity is invented from relocation-masked similarity.

The 142-byte and 96-byte source shapes have one original trailing CC, and all
six target following bytes were independently verified CC. Their manifest
uses the same maximum-one-CC gate as the prior increment. The other shapes
have no tail. Coverage and minimum-byte gates are unchanged. Each target full
body hash and current inventory name is pinned.

Both new group rules passed native validation; unchanged prior rules were
retained, not globally rebuilt. This adds 7 std bodies / 2,216 bytes and 19
Boost bodies / 1,831 bytes to exclusions. Final census: authored 1,770,
excluded 1,614, review 643. Exact authored remains 1,553 / 441,679 bytes;
source 1,750 and match units 744 are unchanged.
