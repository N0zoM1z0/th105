# Complete original pow shared owner

68C28D/453 is whole canonical and inventory-unique from original pow.obj.
The full x87 owner650 and P4 owner2912 both match, together with every byte
of the P4 coefficient section14656. Only453 shared runtime bytes are newly
classified. Public prefixes, the already owned P4 implementation, integer
helper40, common helpers, data and alignment receive no new credit. Authored
exact coverage remains unchanged.

## Real entrypoints and exits

The actual x87 source entries are _pow at0, __CIpow at64, __CIpow_default
at123, __pow_default at148, start at157 and _test_whether_TOS_is_int at610.
The ordinary and CI dispatchers reach the actual P4 entries698109/6980F0.
Both complete implementations participate in the proof; no external JMP or
conditional exit is excused by a generic allowlist. P4 has one actual libm
error-support call. The x87 path uses the named pow helper and real one-/two-
argument error handlers.

Five complete original common helpers are independently compared: twoToTOS21,
load_CW23, fload_withFB67, fast_exit13 and check_range_exit163. All eight
relocations in the last helper have their actual source names and zero
addends. Its original constants belong to the independently verified complete
common data section. The existing SSE-selector allocation, initializer and
x87 control-word protocol are freshly replayed through the sine/sqrt gates.
From the two x87 public roots, all939 instructions across3833 code bytes are
reachable. There are no unaccounted code bytes or invented public ABIs.

The complete12-byte pow data section contains half8 and the four-byte operation
name. Extended infinity is a complete10-byte object beginning at the actual
87tran.obj __infinity label and ending at __minfinity. Its original bytes,
native initialized writable storage and exact position are verified. Its
external reference uses an address binding backed by that independent owner;
it is not misrepresented as a locally defined literal in pow.obj.

The original x87 separator is NOP1. P4 ends with two exact LEA ESP,[ESP]
instructions and NOP1, totaling15 bytes. Both source/native sections include
these bytes in the comparison, but the callable graph and new credit exclude
them. No source text label enters the P4 alignment region.

## Provenance and tests

pow.obj SHA256:
d1f7040f292405e4ee8a96b41c61e8a7d4bf534037bf70df49f288fb772461ef.
pow_pentium4.obj SHA256:
95319da2ff9158e4a9b5a8e4f62805ec342325d03cd2db911b74ddbd9d09d8c1.
87tran.obj SHA256:
d65ab10b5044fa429c963e3d95cf4461fd6f85d69d1b8e5cc123dd759622b35c.
All come from the pinned unchanged SP1 archive. No assembly implementation or
native byte payload is authored.

Ten tests reject partial bodies/masks, integer-helper double credit, wrong
member/provider/data bindings, broken selector protocol and generic padding or
external-tail waivers. All3919 actual byte mutation controls fail: every byte of
both owners and the five helpers, half/name/infinity data, all P4 coefficient label
boundaries and two interior table points. Full coefficient comparison remains
mandatory, independent of the mutation sample selection. Mutation runs were serial
CPU0/nice10 and resumed from saved results.
