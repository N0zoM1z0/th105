# Five original CRT data-address accessors

Five complete six-byte bodies are now canonical and inventory-unique from
original pinned SP1 archive members:
-68D059: ___iob_func returns the actual __iob array at6F7B50.
-692481: ___daylight returns the __daylight cell at6F86E4.
-692487: ___dstbias returns the __dstbias cell at6F86E8.
-69248D: ___timezone returns the __timezone cell at6F86E0.
-692493: ___tzname returns the __tzname pointer array at6F8770.
Names above are the original decorated COFF symbols. Each body has exactly
one zero-addend DIR32 field and a complete ordinary RET. No instruction mask,
partial extent or generic minimum-byte exception is used.

## Complete initialized owners

Original _file.obj owns the entire640-byte initialized __iob section. Its only
two data relocations are the initial stdin pointer/base fields, both to __bufin.
Every other byte is compared, including the original flags and explicit4096
buffer capacity in the first record. Both code/data bindings retain the real
source relocation roles; an address binding is not substituted for data proof.

Original timeset.obj owns all152 initialized bytes: three scalar cells,
alignment, two complete64-byte timezone-name arrays and their two pointers.
The actual labels at0/4/8/16/80/144 and both pointer identities are checked.
The full source/native data section matches after only those two original
pointer relocations. These are initial-image facts, not a claim that the CRT
keeps these writable variables immutable after startup or that their initial
timezone describes the user's location.

## Real common storage, not raw BSS bytes

_file.obj declares __bufin as an external COFF common symbol: section0,
value4096, type0, storage class2 and no auxiliary record. It is not an undefined
zero-size external and not an initialized section symbol. Native703A00..704A00
is entirely inside writable, non-executable PE virtual zero-fill. The whole
4096-byte extent is checked against both raw-data end and virtual-section end.
The actual stdin record explicitly carries that same4096 capacity.

No raw read is attempted on absent BSS storage, no COFF header bytes are
misrepresented as buffer contents, and no synthetic BSS-byte mutation count
is reported. Buffer tests instead reject partial extents, raw-backed regions,
virtual-end crossings and wrong access flags.

Original member hashes:
- _file.obj:935bb014351a6bdcb3a82106822af15ff2ebc9d51cec5b3aaeddf46c6d032e68.
- timeset.obj:55559252e1be98ced21a48d4ee6ee7e97a45ccac131751ebc455c913bbab4781.

Twelve tests pass. All822 actual initialized-byte corruption controls fail:
30 code bytes and all792 initialized data bytes. Both public units freshly
compare every selected whole function exact. Only30 runtime bytes and five
exclusions are added; data, BSS, initializer and authored-code totals get no
credit. No implementation source, vendor object or target bytes are edited.

Evidence: build/origin-anchors/vc8-data-accessors/proof.json and
build/frontier-crt-data-accessors-20261101/mutations.json. The private scope
also retains the original-member discovery and rejects unrelated guessed
locale-accessor identities; the accepted four functions are timezone accessors.
