# Original Boost headers replace regex boundary-only declarations

The selected connect main-state source now uses real boost::regex, boost::smatch,
boost::sub_match and boost::regex_search definitions. The local8/56-byte ABI class
declarations from the first checkpoint are gone. No Boost header is patched.
Complete444830 remains827/827, its full aligned switch payload856/856, and its
seven cleanup actions77, double-cookie handler46 and FuncInfo/unwind92 all
remain exact. Authored progress is unchanged1553 /441679 bytes.

## Reference identity, not an exclusive release claim

The target has templated named_subexpressions_base<char> RTTI, an8-byte regex
shared owner and56-byte match_results. Constructor443780 initializes the final
dword at34 and has no later singular-state byte. The original1.40 match_results
header has exactly the vector/iterator/submatch/shared-owner/last-closed-paren
members observed in the target, and its str(int) body explains442C00 directly.
The1.41 header is the same Git blob. Inspected1.36/1.39 headers lack the later
named-subexpression owner;1.42 and later inspected headers add m_is_singular.

This establishes a compatible historical implementation, not the unique exact
release or original build configuration of the shipped game. Unreviewed library
bodies are not accepted merely because these definitions agree.

Verified official references:
- [Boost1.40 superproject](https://github.com/boostorg/boost/tree/644e2135159e0b3ca535aab1a67938c27caf6ec9).
- [Regex module revision](https://github.com/boostorg/regex/tree/fa1ef1dfd4136803625e49853289ade7c2ddff0a).
- [Original match_results header](https://github.com/boostorg/regex/blob/fa1ef1dfd4136803625e49853289ade7c2ddff0a/include/boost/regex/v4/match_results.hpp),
  Git blob09dd31f009ccb286055a1712748d34793d49cb4a.

## Immutable, reproducible source package

Official modular Git trees supplied375 files, each verified against its Git blob
identity and a SHA-256. The pinned VC8 /showIncludes diagnostic then identified
the actual183-header closure. That unchanged closure plus its original license
is the selected184-file/1308111-byte package. The diagnostic does not change
compilation flags or source semantics. One unused platform header was decoded
as Latin-1 by the connector; restoring its original encoding was required to
pass the original Git-blob check. No mismatched source was silently accepted.

config/boost-regex-source-lock.json pins each immutable official repository,
commit, source path, Git blob SHA-1, byte length and SHA-256. The lock itself is
pinned to847c4101e4d3e4b91a1130f2ffc8d49e1c904457bd5910e5045f05d4d29b881a.
The headers stay in the ignored tool/source cache under their original Boost
Software License1.0, not under this repository's MIT license.

On a network-enabled development machine:

scripts/repo-python scripts/upstream_boost.py --fetch
    scripts/repo-python scripts/upstream_boost.py

Fetch is explicit, downloads only missing files from official immutable commits,
and checks bytes before writing. It never overwrites a changed existing file.
Ordinary builds never fetch: they fail before compiler execution if this package
is missing, altered, incomplete or contains unpinned extra files.

The explicit boost_regex_headers probe contract requires its sole pinned include
directory. Source digests now include external .hpp as well as .h files, the
lock, verifier and complete original package. Metadata-only graph checks may
run without downloaded, independently pinned Boost/zlib SDKs; native paths
still verify/require them. This preserves target/compiler-free CI without
weakening canonical matching or permitting arbitrary missing include folders.
Nine focused tests cover source/lock tampering, original encodings, traversal,
extra files, explicit selection, immutable fetch/write behavior, missing-package
handling and .hpp input invalidation.

## Eight complete canonical library witnesses

The same unchanged application TU, ordinary VC8 /O2 and /GS, produces full
zero-difference bodies for:
-442710: basic_regex constructor,120.
-443780: match_results constructor,46.
-444790: checked string regex_search overload,160.
-442C00: match_results::str(int),210.
-442F40: match_results destructor,141.
-442440: basic_regex/shared-owner destruction,53.
-442AB0: sub_match::str(),326.
-6A0910: checked vector<sub_match>::operator[] const,60.

All1116 bytes include full call/data relocation replay, not just fingerprints.
Their source ABI and lifetime are supplied by the actual upstream templates;
no replacement methods, register-specific declarations or optimizer barriers
are introduced. The native pattern flag0 is expressed as regex::normal to select
the genuine flags overload rather than the competing pointer-range overload.
These bodies are library evidence, not new authored matches.

## Seventeen proven non-game bodies

Two separate origin anchors recompile the real caller with verified headers and
require unique complete fingerprints across all4027 inventory rows. All have
zero omitted alignment tails and retain the existing nonrelocation thresholds.
Native full-body hashes are additionally pinned. The nine Boost bodies total
1229 bytes:442440,442710,442AB0,442C00,442F40,443780,443A00,443AA0,444790.
The eight VC8 standard-container/iterator bodies total453 bytes:
410300,4421B0,4421D0,442210,442250,442480,442FD0,6A0910.

The53-byte shared-owner destructor has several genuine source instantiations
with the same native body; it is one inventory entry, not multiple credit.
Only these17 candidates are newly excluded. Larger regex parser/search/assignment
routines and other nonmatching instances remain under review. No source-present
or authored match entries are added for library helpers.

## Focused validation

scripts/repo-python scripts/build.py --unit exact-first-connect-main-state --compare --json
    scripts/repo-python scripts/build.py --unit exact-first-replay-codec --compare --json
    scripts/repo-python scripts/ci.py

Nine functions in the connect unit pass: the827-byte application body plus eight
library witnesses. Independent full856 and root EH215 checks also pass. The only
previous external-include consumer, the real zlib replay-codec unit, is freshly
replayed at153/151 exact. Unrelated code/flags are unchanged; this is incremental
validation, not a cold corpus replay. Only the two new source-origin rules are
recompiled/materialized; no blanket origin regeneration or exactness relaxation.

Final totals: source1750, authored1770, exact1553 /441679 bytes, excluded1440,
review817, mapped1777 and units743. Local checkpoint only; no push.

## November1: bounded1.41 parser source check

The official boostorg/regex comparison from the pinned1.40 module revision to
boost-1.41.0 reports one compiled-header change, basic_regex_parser.hpp; the
other listed changes remove CMake files. Fetching that complete original1.41
header and verifying Git blob ebec35b60d98c17bb3ab40655e431a5f8d72e099 shows
one source-line difference from the selected header: added parentheses around
`(*m_position != '>') && (*m_position != '\'')` before the existing `||` term.
The same grouping already follows C++ operator precedence. No operation,
short-circuit order, state mutation, constant or template declaration changes.
This does not provide a new parser-codegen hypothesis or identify the shipped
release. No reference header, source lock, compiler flag or unit is changed;
no alternative-header build or canonical improvement is claimed.

Verified source:
https://github.com/boostorg/regex/blob/boost-1.41.0/include/boost/regex/v4/basic_regex_parser.hpp

The installed selected 184-file package remains unchanged. Do not repeat1.40/1.41
parser version trials based solely on the existing match_results compatibility
observation.
