# Genuine VC8 repeated-character string helpers

The recently recovered connect main-state caller exposes the whole-match string
conversion boundary. Its library conversion442AB0 calls442A00, which is the
actual VC8 std::string::append(count,char) body, not another application method.
A minimal public probe takes the genuine member address from the pinned xstring
header. It contains no replacement implementation, custom guard or copied code.

The fresh native COMDATs reproduce:
-442A00:166-byte append(count,char), canonical SHA
 43a79358d92314332171087f5963641968d862d5f6ae4ba816aba3259e2ec12e.
-410270:88-byte _Chassign, canonical SHA
 80347ce19e21c97552f26b48717daaeaaf1b3f1c58834214e12d62fd8602aec5.

The origin gate recompiles the source and searches the entire4027-candidate
inventory. Each complete-length fingerprint hits only its declared address.
Coverage is150/166 and84/88 nonrelocation bytes, with zero omitted tail bytes.
The separate ordinary comparison unit also replays every REL32 field and matches
all254 bytes, including both _Xlen calls665AF4, _Copy402430, _Chassign410270 and
memset68A440. The generic fingerprint gate's one-occurrence optional call-map
restriction is unchanged; append's repeated _Xlen operands are instead covered
by the full canonical comparison and pinned complete native body hash.

Pinned compiler SHA:
71c93ca5bddc9b2816d0e053cac2b952f926f6b9321fab6b1ab6e8603621324c.
Pinned xstring SHA:
c1a068968165290d000d554340d9c4e7e123c47ea619ad05d1c8f4e719c05922.

Only these two helpers are newly excluded. The larger _Copy402430 and the regex
conversion routines are not promoted by association. The genuine header bodies
retain all overflow guards, reserve/copy behavior, repeated-character fill and
SSO terminator publication. No authored matching or source ledger entries are
added for the probe or its helpers.

Reproduction:

    scripts/repo-python scripts/build.py --unit vc8-string-count-append-origin --compare --json

The new origin rule is independently validated with its existing full-inventory
anchor validator; unchanged rules are retained incrementally. Evidence is under
build/frontier-string-append-origin-20261031 and its .analysis counterpart.
Source1750/authored1770/exact1553/441679 bytes remain unchanged. Excluded1423,
review834 and units743. CI and whitespace checks gate the local commit; no push.
