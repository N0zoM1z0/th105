# Original inverse-square-root interpolation and exact legacy literals

6897D0/77 (_vorbis_invsqlook) is now whole canonical and inventory-unique from
original SDK lsp.obj. Its entire80-byte section, including three original NOPs,
compares exactly. Only77 third-party code bytes are newly classified.

The six DIR32 fields use three floating constants and the actual inverse-
square-root table at6F77D8. Table references use both addend0 and addend4;
the existing per-symbol/addend override mechanism gives each its exact resolved
element bytes. The generic data model is unchanged. All1176 initialized data
bytes of original lsp.obj remain checked by the preceding table-getter proof,
not just two selected elements. The old12-byte getter stays exact too.

## Original SDK floating symbol format

The original object uses explicit-width extended symbols such as
__real@4@40058000000000000000, whereas the modern VC8 source units use direct
32/64-bit IEEE names. Previously the literal checker rejected the older syntax
as malformed. It now recognizes the distinct4/8-byte-plus20-hex-digit form and
converts its signed exponent/significand using integer arithmetic only.

The decoder accepts only finite values exactly representable at the declared
IEEE width, including signed zero and exact subnormals. It rejects precision
loss, overflow, underflow-to-zero, extended special/pseudo values and malformed
sizes. It never rounds. Encoded value, original initialized COFF bytes, mapped
literal bytes and native bytes must all agree, with zero addend and literal
validation. Existing modern-format checks and errors stay in force.

The actual three literals are exact64.0f,32.0f and0.5 double. Source encodings
and both complete target/source byte sequences agree. No symbol renaming,
object patching, approximate float comparison or address-only real validation
is used.

## Strict acceptance and regressions

The generic relocated-library70% nonrelocation coverage rule remains unchanged.
This77-byte function has53 nonrelocation bytes; its narrow original-source
proof instead closes every relocation and complete data dependency. No masked
or partial function is accepted.

Sixteen literal-format tests cover values, signed zero, subnormal/maximum
boundaries, forbidden rounding and invalid mappings. Seven root tests protect
source/member, extent, table addends and all constants. All106 actual code,
padding, literal and table corruption controls fail. The prior two table-getter
proofs freshly pass. Two existing authored VC8 flight functions4FC7C0/4FC900,
which use modern32/64-bit literals, are freshly rebuilt and remain exact.
No cold corpus replay is claimed or needed for this disjoint format addition.

Evidence: build/origin-anchors/xiph-invsq.json and
build/frontier-sdk-invsq-20261101/. Private scripts are under
.analysis/frontier-sdk-invsq-20261101/. No authored, padding or data-byte credit
is added.
