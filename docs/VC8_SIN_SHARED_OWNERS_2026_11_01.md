# Coupled original x87 and SSE sin owners

Two shared runtime bodies are now whole canonical and inventory-unique:
68B6C8/145 in original sin.obj, and694E3E/425 in original sin_pentium4.obj.
Their570 bytes are the only new runtime credit. They are physical shared
bodies, not invented standalone public ABIs.

## Complete owners and real fallback

The proof compares both entire original text sections: sin297 bytes at68B630
and P4 sin456 bytes at694E20. Actual source symbols fix all public and shared
entry positions. The P4 tail returns to the real x87 __sin_default entry at
68B6BF, rather than an arbitrary same-shaped routine or the ordinary dispatch
entry that would restart feature selection.

The original one-byte NOP at sin source offset63 separates public entries;
the P4 section's last byte is another original NOP. Both bytes compare exactly
and receive no callable credit. The code regions are split only at actual
original source entry labels. With five complete previously proved common
helpers, the two actual sin/__CIsin public roots reach every one of242
instructions across920 code bytes. All cross-region branches enter declared
source entries. No generic indirect-jump, conditional-exit or unreachable-byte
rule is relaxed. Public prefixes, helpers and padding get no new credit.

## Entire data, selector and initialization

All2208 bytes of the original P4 readonly coefficient section at6CDC70 match,
including every table, named constant and source padding span. No numeric
rounding or approximation is used. The complete seven-byte operation-name data
section and the existing common control-word, extended constants, indefinite
value and floating-point flag proof also pass. Per-unit literal keys prevent
same-named constants in other objects from being overwritten.

The source SSE selector is not an initialized or .bss section symbol:
mathfcns.obj declares a four-byte external COFF common block. Its record type,
size and storage class are checked, along with native PE zero-fill at7039C4.
The complete real initializer69098F/20 canonically clears and writes this same
address, calling the independently owned get_sse2_info routine. The proof does
not assume the selector remains zero after initialization or simplify either
branch of the runtime dispatch.

## Validation and limits

All original members are extracted from the unchanged SHA-pinned SP1 archive;
the exact member hashes are recorded in the proof. Two formal shared-body
comparisons pass. The preceding complete sqrt/common proof is freshly replayed,
as is the original18-byte std::sin(float) wrapper gate. The still-nonexact
Tenshi giant receives no extra credit from that helper regression.

Nine focused tests reject changed source/member, wrong fallback, incomplete constant
bindings, missing owner/common support and padding-as-code claims. All811 actual
mutation controls fail: every owner byte, every selector- initializer and
operation-name byte, plus all named coefficient-span boundaries and an interior
table point. Complete2208-byte data comparison is mandatory, not replaced by
selected mutation samples. The narrow origin rule passes before both review rows are
reclassified.
