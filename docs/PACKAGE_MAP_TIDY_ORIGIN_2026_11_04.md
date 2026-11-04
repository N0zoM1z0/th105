# Package archive map cleanup origin

The full 56-byte native entry `41C8D0` is classified as VC8-generated map
cleanup, not authored game code. Its SHA-256 is
`a61f3985aabb36db3e49b8eb44ef98f2935eb359c02585dc50a21480727b6898`.
The exact 228-byte `PackageArchiveStore` destructor at `41B980` calls it at
`41B9FF`.

The genuine source-pinned `gpt-web-package-archive-store` VC8/LTCG build emits
the matching package-index tree `_Tidy` as a unique 56-byte compiler-owned
helper. Its actual destructor calls that helper at +0x7F. Both the 163-byte
constructor and 228-byte destructor replay exact, including their already
configured cleanup EH and static object evidence.

Binding the emitted helper's two calls to the native package-tree erase entry
`41CC40` and the previously excluded delete alias `6898EA` gives all 56
canonical bytes with no masking. The native 199-byte erase body is separately
hash-pinned; the emitted call is the actual same-specialization tree `erase`.
This binds a role and does not claim the two erase implementations match or
classify the erase body. The complete replay has one same-size inventory hit,
`41C8D0`; it does not add authored-function or exact-byte credit.

The focused validator checks source closure and compiler context, both exact
owners, parent edges, source and native call roles, complete bytes, relocation
coverage and uniqueness. Five target-independent contract tests and seven
additional target-backed corruption controls reject altered target/source
bodies, owner, erase, delete ownership, symbol or inventory. Receipts are
`build/origin-anchors/linked-package-map-tidy/proof.json` and
`build/frontier-package-map-tidy-origin-20261104/negative.log`. No full origin
census, arbitrary exception execution or gameplay execution is claimed.
