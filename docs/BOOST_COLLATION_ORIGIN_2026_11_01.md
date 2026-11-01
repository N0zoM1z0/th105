# Original Boost collation lookup and complete pointer tables

lookup_default_collate_name6B4820 now has a complete canonical455-byte proof,
SHA256 ff6e7325d2a0a13ba20376201248fe6ce3ff0556a3dfcf5539fd966d5f9c889e.
All168 instructions are reachable within the body, with three RET0 endpoints
at6B496D,6B49C5 and6B49E6. No indirect calls, outside branches, unreachable
suffixes or masked fields are accepted.

## Source and data ownership

The exact original regex_traits_defaults.cpp is part of the separately verified
Boost source package. Its unmodified NDEBUG wrapper is freshly compiled with
the pinned compiler and both checked immutable source/header packages. No game
code, table initializer or library implementation is handwritten to fit bytes.

The two original mutable pointer arrays have these native initial images:

-def_coll_names at6F9840:129 pointers/516 bytes, hash
 1a12db2ba1c1df5534fcd06073702633091b0776a5c8afb45bb6d4017c878300.
-def_multi_coll at6F9A48:22 pointers/88 bytes, hash
 0d6773ede394a65488f2d08f2bcb49cf06626cd1f8edf639b95f8fe6f97c5613.

Every source initializer string is parsed from the pinned original declaration;
there is exactly one final empty sentinel per array. Every emitted COFF cell
must have its actual DIR32 literal relocation, and both source literal bytes
and native pointed-to bytes must equal that complete original NUL-terminated
string in readonly storage. All151 pointers and strings are verified, not a
representative prefix. The arrays themselves are initialized writable .data,
as in the original C++ declaration; this proof does not claim runtime immutability.

## Narrow full canonical comparison

The ordinary DIR32 map intentionally expects the same pinned value at every
allowlisted addend. It cannot honestly encode this nonuniform base/base+4 case.
That public comparator and its validation are unchanged. No shorter common
byte pin, zero-length witness, fictitious global alias or mask was substituted.

boost_collation_origins.py is a separate bounded original-source contract for
this one function and these two complete tables. It requires allnine actual
COFF relocation records, including both observed array offsets0/4 and allfour
named calls (char_traits comparison twice, string copy and string constructor).
After normal relocation resolution every one of455 code bytes must equal the
attested target. The fully canonical body, not a masked fingerprint, must be
unique across the candidate inventory. The complete CFG must also close.

The604 bytes of pointer metadata and all literal strings are supporting evidence
only. They receive no authored or extra code-byte credit. No target bytes are
patched, copied into source or executed. No generic address/ABI gate is relaxed.

## Replay and accounting

    scripts/repo-python scripts/boost_collation_origins.py

The fresh proof is build/origin-anchors/boost-collation/proof.json, with compiler,
source/object provenance, validator/anchor digests, full code hash, CFG and both
complete table/string hashes. Eight synthetic tests cover complete cell ownership,
both literal sides, readonly strings, final sentinels, relocation completeness,
base+4 resolution and closed CFGs; they contain no target instruction fixture.

Only455 moves review to third_party/boost_regex/exclude. Excluded1986/review386;
exact authored1431/443916, source1635/authored1655/mapped1820/units776 unchanged.
The previous15-function1391-byte batch remains separate. No all-exact rebuild
or push.
