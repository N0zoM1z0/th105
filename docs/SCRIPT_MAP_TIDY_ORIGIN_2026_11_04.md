# CScript map cleanup origin

The complete 56-byte native entry `405CD0` is classified as VC8-generated map
cleanup, not authored game code. Its SHA-256 is
`ebd0b50c162abec11a631e2fcfa27ecc2374d18c98d2f274bd4925910cc2d196`.
The already-exact `CScript` destructor at `405660` calls it at `4056A8`.

The genuine, source-pinned `exact-first-script-lifecycle-linked` VC8/LTCG
build emits the `CScript` command-factory tree `_Tidy` as a unique 56-byte
compiler-owned helper. Its real exported destructor calls that exact emitted
helper at the corresponding +0x48. Both the 95-byte destructor and separate
147-byte pending cleanup are freshly compared exact. The overall unit still
reports mismatch for its separate `clear_commands` body, so no claim is made
that all members match.

After binding the source helper's two actual calls to the native tree erase
entry `405D50` and previously excluded delete alias `6898EA`, all 56 canonical
bytes match, without masking. The full target erase body is separately
hash-pinned and the source call is checked as the real same-specialization tree
`erase`; the erase implementations themselves have different sizes and are not
claimed equivalent or classified by this proof. A search across current
same-sized candidates gives one whole-body hit at `405CD0`. This is source and
call-role evidence for origin, not an authored-function or exact-byte gain.

The focused rule rebuilds the real source closure, checks accepted roots,
owner edges, callee roles, target identity, body, relocation coverage and
inventory uniqueness. Five target-independent contract tests and seven
additional target-backed corruption controls reject altered target/source
bodies, owner, erase, delete ownership, symbol or inventory. The focused proof
is `build/origin-anchors/linked-script-map-tidy/proof.json`; the controls are in
`build/frontier-script-map-tidy-origin-20261104/negative.log`. No full origin
census, arbitrary exception execution or runtime gameplay is claimed.
