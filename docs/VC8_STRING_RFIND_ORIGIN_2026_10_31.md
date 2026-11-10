# Original VC8 string reverse search

The complete165-byte body4395F0 is canonical exact from an unmodified original
VC8 std::basic_string<char> explicit instantiation. SHA-256:
aec7a62afed63afae4eab520a050f7e83055532c49890b30a13f591e29ec30f2.

Native semantics include the empty-needle position bound, length rejection,
min(position,size-count) starting point, small-string storage choice, backward
first-character/traits comparison, and npos failure. The original template
supplies all behavior; no branch-by-branch game implementation is introduced.
Canonical replay binds char_traits::compare405560 and const _Myptr401E30 and
compares every instruction/loop-alignment byte. Whole-source fingerprint
uniqueness independently passes the full4027-function inventory with the
unchanged0.70/24/no-tail contract and pinned whole-body hash.

The explicit-instantiation probe is scripts/probes/Vc8StringOrigin.cpp; unit
vc8-string-library-origin. No authored source, old unit, flag or verifier changed.
The additional standard members emitted by explicit instantiation receive no
unverified origin or matching credit.

Only one compiler exclusion is added: excluded1783/review448/units762.
Exact1578/448979, source1776/authored1796/mapped1803 remain unchanged.
