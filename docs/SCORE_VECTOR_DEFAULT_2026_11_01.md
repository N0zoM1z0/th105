# Original vector default constructor in the ScoreData array

4460D0/14 is now classified as compiler-generated from the actual original
VC8 std::vector<ScoreDefaultRecord24> constructor emitted by
ScoreDataLifetime.cpp. The whole relocation-free function matches the target,
is unique over all 4027 candidates, and closes at its real RET. There is no
new authored constructor, handwritten zero-store implementation or instruction
mask. The generic 24-byte origin threshold is not lowered.

## Source and actual array ownership

The source and record-type header are pinned with LF-normalized hashes. The
original VC8 vector, xmemory and xutility headers are independently hash-pinned;
none is changed. The real parent owns 20 vectors at+198, each 16 bytes. Its
complete 31-byte call site 43E29C contains the actual constructor 4460D0 and
paired destructor 435F90, count 20, stride 16, member offset 198, existing EH-state7
publication and the real array helper 68A30C. Every source relocation has a
zero addend, and the entire site is replayed unmasked.

This is an observed template instantiation witness and a complete native
physical body. It does not assert that no other vector specializations shared
the same implementation or that the reconstructed record name was original.
The actual array role supplies independent ownership beyond a short byte match.

All six configured functions in the existing owner unit are freshly canonical
exact: authored constructor 306, implicit destructor 393, map constructor 43,
vector constructor 14, map destructor 52 and vector destructor 42. This does not
add new parent/EH/static-lifetime claims; the remote EH limits in
SCORE_OWNER_LIFETIME_2026_11_01.md remain explicit. The new 14-byte constructor
itself contains no call, exception edge or remote cleanup.

Eight tests reject short/masked code, wrong source/header review, missing array
owner or paired destructor, alternate source facade and compiler drift. All 45
actual byte corruption controls fail: each of the 14 constructor bytes and 31
caller-site bytes. The original complete-body comparison remains mandatory.

Only 14 compiler-library bytes and one exclusion are added. Source-present, authored
exact functions and authored exact bytes are unchanged. No source, standard-library
header, compiler setting or accepted function is modified.
