# Complete original log10 P4 shared owner

697C6E/614 is whole canonical and inventory-unique from the original SP1
log10_pentium4.obj. The entire 656-byte source/native text section and all
2336 coefficient bytes match. Only the 614-byte shared body is newly
classified as runtime; existing public prefixes, error provider, data and
trailing storage receive no new credit. Authored exact coverage is unchanged.

The actual source entries are __CIlog10_pentium4 at offset 0,
__log10_pentium4 at 24 and shared start at 30. Both real public roots reach
all 145 instructions across 644 code bytes, including the internal denormal
retry and exceptional paths. The sole external call is to the existing named
634-byte ___libm_error_support at 694A92. No x87 fallback is fabricated.
All 21 relocation fields, including coefficient addends 16/32/48 and Infs+8,
retain the original source values. Each addend-specific literal mapping checks
the remaining original label span at destination+addend, not the base address.
The full original .rdata section is also compared, independently of samples.

## Original trailing storage is not callable credit

Text offsets 644..655 contain 8DA424000000000500000000: LEA ESP,[ESP] then
ADD EAX,0. The ADD writes flags; this sequence is not claimed semantically
neutral. These are the exact original/native trailing bytes following the
last backward JMP. No defined source text symbol points into this tail.
The source-defined public/shared code regions close without entering it.
The strict validator checks the entire source/native section, the exact
trailing sequence and instruction forms, and the separate complete reachable
graph. It does not admit arbitrary unreachable instructions or count these
12 bytes as part of the shared body. No implementation bytes are generated.

Original member SHA256:
08cd9610e83d2fcba8cfe9af1c6125ec502a264e9e3dc10669aea2d36c201760.
The unchanged pinned archive hash is checked by the original-member build.

Earlier log_pentium4.obj comparisons used the wrong mathematical function.
They are not compiler-version or patch-mismatch evidence for this log10 body.
This result does not claim the whole runtime uses one patch version.

Ten tests reject wrong function-family member, shortened or masked bodies, wrong
provider/coefficients, padding credit and generic reachability waivers. All 690
actual byte corruption controls fail: every one of 656 owner bytes, all coefficient
label boundaries, explicit nonzero-addend positions and two interior table
positions. Complete data comparison is mandatory regardless of selected mutation
samples.
