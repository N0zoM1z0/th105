# Original Xiph codebook decoder and owned switch table

One formerly unresolved function is now independently classified as third-party:
681C70, _vorbis_book_decodev_add from the original official Ogg/Vorbis Win32
SDK 1.0.1 codebook.obj. No authored exact bytes or source functions are added.

## Why the old fingerprint correctly stopped

The inventory code extent is 880 bytes. The original object has a 912-byte
COMDAT: complete code followed by eight relocatable jump-table dwords.
The old relocated-Xiph gate forbids relocations or non-padding after the
inventory extent. It correctly rejected this body. That gate and its thresholds
are unchanged. The table cannot be discarded or treated as padding.

## Independent complete-payload proof

The new narrow xiph_owned_switch_origins.py path re-extracts the original object
from SDK SHA256
fead50bbdf6a17e695b8b628f4ebe2c64a8f589ca6b983909484f4f361afbfcc.
Extracted codebook.obj SHA256:
f70aa97711fd91987cf0778fc4c6b34467c09ad26ebc336214ed4cdc2d8f9af8.

All 912 bytes compare canonically with zero masks and zero differences:
ebefcd8712dfe0c21deada5ce4f13aca08e4872168fef3fb1abcdb4c58f057f5.
The complete 880-byte code hash is
00e6067bc215c6ba5ac26c384060ce36292a0495fa2738e54c09ebff47d6f22c.
All 322 decoded instructions are reachable. The table begins at 681FE0,
immediately after the final RET. Its dispatch at 681F3D is guarded by
CMP EDX,7 / JA; no other edge bypasses that guard. All eight entries reach
instruction starts inside this same body.

Every relocation is owned: fourteen E8 call fields, one table-base displacement
and eight table entries. All non-link bytes are preserved. No unknown absolute
memory, call, indirect branch or escaping control-flow edge is accepted.
The only external callees are _oggpack_look 6B6B30, _oggpack_adv 6B6BE0 and
_bitreverse 681640. Their independent existing SDK origin anchors are freshly
revalidated before the names can bind to those addresses. This does not claim
that all old relocation-masked helper anchors are new canonical exact proofs.

The full inventory has exactly one complete-payload match after legitimate
address rebinding. The accepted exclusion is only the inventory's 880 code
bytes; the owned 32-byte table is verified evidence, not additional credit.

## Reproduction and limits

    taskset -c 0 nice -n 10 scripts/repo-python scripts/xiph_owned_switch_origins.py

The receipt is build/origin-anchors/xiph-owned-switch/proof.json, including
target, SDK, object and validator hashes, helper targets, complete extents,
table entries and inventory uniqueness. Private discovery is retained under
frontier-xiph-owned-switch-20261101. Twelve tests cover the full payload,
truncated/mutated suffixes, wrong/signed guards, bypass edges, wrong targets,
extra/missing relocations, unaccounted calls, non-link mutations and schema
waivers. This path has no adjustable masking or coverage controls.

The nearby 687790/514 and 688620/1497 candidates still have no complete
original-SDK witness and remain review. Short/sub-threshold SDK leads also
remain review; proximity or a plausible symbol is not provenance.

Excluded1799/review422; authored1806, source1786, mapped1813, units765 and
exact1585/449721 authored bytes are unchanged.
