# ReimuObject word-selector owner and joint runtime context

Selected change: the two local `select_sequence` declarations in
`src/characters/ReimuObjectOwnerView.hpp` now take `short`, consistently with
the initializer and staging views. The complete native update payload and its
accepted counter remain byte-identical. No large-root exact credit is added.

## Target observations and declaration choice

Only original Japanese1.06a SHA256
`56350024879199861579c11b0e1c67b9590e10a8d40cd5996b109deec9afca7e`
is used. Preflight target/status/tracking checks pass; IDA rejects its other
image and supplies no semantics. ReimuObject vtable6C40A4 has selector45C390
at+0C and initializer4A1CE0 at+3C. The selector consumes the signed low word
of a four-byte argument slot. The existing complete202-byte provider witness
and initializer call preparations support the word-facing declaration.
They do not uniquely establish every original C++ parameter/return declaration.

The selected update owner had retained an `int` parameter, while the initializer
and staging views already used `short`. Fresh private rebasing puts the complete
initializer on the selected update's primary sprite/motion/float storage,
retaining a field view for unresolved storage. A short interface reproduces
its entire5440-byte payload; the same owner with int gives113 differing bytes
instead of14. Conversely, changing only the update owner to short preserves
every byte of its45696-byte native payload. No owner is constructed, and no
nominal hierarchy, lifecycle, unused380 type or global selector API is promoted.

Fresh public build: `gpt-web-reimu-object-action-state` remains nonexact+0x1F;
the complete66-byte `0x4963A0` counter remains exact. The header is included by
that source only, so this is the affected accepted-unit replay. Current header
SHA256 is `a8603fd542e9c19dcfef3009e50283b3aef42acde72768ae1a735192b01911fa`.
Update CPP35b06db0 and initializer CPP3803a002 are unchanged.

## Complete joint native source and actual LTCG result

A private joint TU defines update and initializer on the same word-facing
runtime owner, with consistent float lookup declarations. Real field accesses
retain the observed storage widths; no return, local or behavior is fabricated.
All three independently bounded native results reproduce existing payloads:

| Address | Complete native bytes | Canonical SHA256 prefix | Result |
| --- | ---: | --- | --- |
|496540|45696|4b565d71|Still nonexact+0x1F|
|4963A0|66|ad12b782|Entire accepted counter exact|
|4A1CE0|5440|65298d36|4892 callable bytes,14 differences;548 metadata bytes equal|

The same joint source then compiles with `/GL` and links with `/LTCG`,20 real
native provider objects and pinned static CRT/SDK inputs. Four attested
nonexecutable globals use ABS data bindings. Method aliases retain the same
receiver/argument protocol and point to real source bodies, without return-type
aliases or executable ABS providers. Private float lookup definitions agree
with both consumers; this does not prove their original return type or exactness.

The first attempt correctly rejects an old596370 source pin. A fresh configured
build supplies its now-accepted323/323 continuation, replacing that historical
nonexact provider. The linked image is not executed.

Independent initializer replay qualifies its full4892+548 envelope, rather than
a distance to the next MAP symbol. All247 owned fields close:66 REL32 edges
(65 calls and the596370 tail),85 immutable numeric references,9 metadata
addresses and87 internal code pointers. All181 PE HIGHLOW fields agree with
the DIR32 inventory. Real MAP destinations, provider ownership and literal
bytes/widths are checked before canonicalization. No register mask is used.
The complete linked initializer equals native65298d36 and still differs from
target at14 callable bytes, first+0x1140/4A2E20; metadata is unchanged.
The linked counter remains66/66. The linked update has an aligned EBP frame
and differs at+0; no complete linked-update replay is claimed.

This closes one coherent caller/init context, not the original partition or an
LTCG impossibility. The remaining906/999 register/preparation differences need
a different lead. Do not repeat this fixed context as if it were new evidence.

## Other controls and retained evidence

A real SP1 `/Zi` object and PDB now compile using the isolated PDB/NTLM setup
from the [Aya refresh](AYA_ENTRY_SEQUENCE_WORD_ABI_2026_10_19.md#exact-first-refresh-2026-10-23).
The complete initializer remains65298d36. This supersedes the earlier C1902
failure as a current-source codegen observation. Nine full dispatch/state-flow
controls are also payload-identical: typed slot calls, real post-selection
state returns, a comma expression, void result and whole999 inlining. A member
pointer instead introduces an unbound virtual thunk; no mapping is invented.

Recipes: `.analysis/reimu-entry-exact-first-20261023/`. Receipts and retained
inputs: `build/reimu-entry-exact-first-20261023/`; start with `owner.json`,
`public-update-word.json`, `joint-native.json`, `zi-isolated.json` and
`joint-link/{receipt,entry-audit}.json`. The link receipt SHA256 is
`a6b39cc4695cc6d3708a68176dca026eb6fcd313c751a3a56568d3ebb83baa40`.
Completed controls are compressed with per-member hash verification. No match
ledger, callable boundary, configured profile or unit partition changes; no
aggregate cold replay or new native matrix is claimed. Existing native scoped
observations retain the identical complete update payload as their input.
