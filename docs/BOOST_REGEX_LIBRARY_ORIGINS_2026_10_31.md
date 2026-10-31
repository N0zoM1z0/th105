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
