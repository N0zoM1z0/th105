# Replay member cleanup boundaries

Two complete compiler-only bodies are newly qualified from the unchanged real
ReplayStorageConstructor.cpp owner:
- 42B8E0/27: original vector<ReplayStorageSlot>::_Destroy forwarding member.
- 42C950/5: implicitly emitted ProfileInputManagerExLifetime destructor.

No authored destructor, new object, caller, export or ABI directive was added.
The derived input class declares no destructor; its scalar fields add no owned
cleanup, so its complete body tail-enters409D50. That base vptr-only cleanup
now has its own full type/RTTI/scalar provenance and no authored credit.

## Independent member ownership

The actual161-byte ReplayStorage constructor pairs constructor42C930 and
cleanup42C950 at source offsets47/42. Its entire23-byte array site43F1D9
checks count2, stride104 and member offset8. The actual208-byte implicit storage
destructor uses the same cleanup in its full35-byte array site43F2FA, also
count2/stride104/member8. All five public unit comparisons are freshly exact:
161/27/208 existing owners plus27/5 new roots. Remote EH metadata is not newly
claimed exact, and no parent code is recounted.

The vector forwarding member has one genuine REL32 field17 to original range
helper42B230. That complete52-byte helper replays in the same real owner TU:
private deque at+3C, two deques at+08, record stride50h. Its actual five-byte
deque destructor callback448DE0 also replays against the separately excluded
Tidy420A80. No helper or callback is manufactured from native bytes. The
underlying52/5 providers already had positive compiler ownership.

Whole-inventory canonical scans find one physical occurrence for each new
root. The input destructor also has the stronger real paired-array witness;
this is not an exclusive original source spelling or linker ICF claim.
Unreviewed caller42C0D0 is not classified merely because it calls42B8E0.

The three actual source files and four original VC8 headers are pinned.
The existing strict implicit-parent provenance gate and independent input-base
cleanup gate freshly pass. Twelve tests and147 actual byte mutations cover
both roots, both array sites, range52 and deque callback5. No generic threshold,
mask, tail tolerance or ownership validator was weakened.

Only32 compiler bytes added: excluded2069/review303, units808. Authored
1431/443934, source-present1636 and authored1655 remain unchanged.
Private evidence: build/frontier-replay-destroy-wrapper-20261102/ and
build/origin-anchors/replay-member-cleanup/.
