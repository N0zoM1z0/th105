# Original vector default constructor in the ScoreData array

4460D0/14 is now classified as compiler-generated from the actual original
VC8 std::vector<ScoreDefaultRecord24> constructor emitted by
ScoreDataLifetime.cpp. The whole relocation-free function matches the target,
is unique over all4027 candidates, and closes at its real RET. There is no
new authored constructor, handwritten zero-store implementation or instruction
mask. The generic24-byte origin threshold is not lowered.

## Source and actual array ownership

The source and record-type header are pinned with LF-normalized hashes. The
original VC8 vector, xmemory and xutility headers are independently hash-pinned;
none is changed. The real parent owns20 vectors at+198, each16 bytes. Its
complete31-byte call site43E29C contains the actual constructor4460D0 and
paired destructor435F90, count20, stride16, member offset198, existing EH-state7
publication and the real array helper68A30C. Every source relocation has a
zero addend, and the entire site is replayed unmasked.

This is an observed template instantiation witness and a complete native
physical body. It does not assert that no other vector specializations shared
the same implementation or that the reconstructed record name was original.
The actual array role supplies independent ownership beyond a short byte match.

All six configured functions in the existing owner unit are freshly canonical
exact: authored constructor306, implicit destructor393, map constructor43,
vector constructor14, map destructor52 and vector destructor42. This does not
add new parent/EH/static-lifetime claims; the remote EH limits in
SCORE_OWNER_LIFETIME_2026_11_01.md remain explicit. The new14-byte constructor
itself contains no call, exception edge or remote cleanup.

Eight tests reject short/masked code, wrong source/header review, missing array
owner or paired destructor, alternate source facade and compiler drift. All45
actual byte corruption controls fail: each of the14 constructor bytes and31
caller-site bytes. The original complete-body comparison remains mandatory.

Only14 compiler-library bytes and one exclusion are added. Source-present,
authored exact functions and authored exact bytes are unchanged. No source,
standard-library header, compiler setting or accepted function is modified.

Evidence: build/origin-anchors/score-vector-default/proof.json and
build/frontier-score-vector-default-20261101/{positive,mutations}.json.
Private scripts are under .analysis/frontier-score-vector-default-20261101/.
