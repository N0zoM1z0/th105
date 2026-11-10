# Battle setup and camera share live fighter coordinates

The battle controller's roster replacement and initial pair setup now call the
real `GlobalBattlePairState` providers through one shared declaration. The
camera state previously lived only in its provider TU, while callers used two
undefined receiver aliases; roster replacement additionally declared all four
coordinate arguments as `int *` and recovered them with raw offsets.

Both callers now pass `&first.x_ec`, `&first.y_f0`, `&second.x_ec` and
`&second.y_f0` as `float *`. The shared header exposes the existing 0x6C state
and asserts the pointer offsets. Native `0x426B90` stores these live addresses
at +44/+4C/+48/+50 in parameter order. The camera update reads through them,
so this is a retained connection to the fighter positions, not a coordinate
snapshot. Initial pair setup `0x427320` installs the same pointer roles and
performs its established initialization/update sequence. No policy, update
ordering, global address or ownership/lifetime is changed.

## Complete comparison

Three units were rebuilt serially against the pinned Japanese 1.06a target.
All nine roots remain exact:

- Controller initialization 470880: 479 bytes; roster preparation 470A60: 337.
- Pair initialization 46AE70: 279 bytes.
- Pointer publication 426B90: 31 bytes; camera updates 426BB0/426DF0: 561/948.
- Camera initialization 427320: 106 bytes; sibling helpers 428030/465100: 55/38.

The provider's complete COFF contents and relocations are identical. Caller
objects retain every section byte; only three call relocation symbol names
and the pointer accessor's return-type debug symbol change. The three binding
entries resolve those real declarations to the same native addresses.

Evidence is in `build/frontier-battle-pair-owner-20261110/{before,after}/` and
its passing `ci.log`. The original input migration and baseline edits remain
separate and are not included in the commit. This preserves local exactness;
it adds no Factory acceptance or authored-byte credit.
