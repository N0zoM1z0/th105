# Animation block wrap and advance

Character PAT groups and effect resource groups store a byte at offset 0x14
that suppresses the frame-wrap signal when nonzero. Both `0x45C1A0` and
`0x4739F0` advance the frame index modulo the block's frame count, apply the
frame, and return true only when the resulting index is zero and the current
block's byte is zero. The byte does not stop the frame index from wrapping.

The character timer at `0x4351C0` calls the next-block virtual only when the
next-frame virtual reports true. Explicit block selection is independent of
this signal. The next-block routines `0x45C220` and `0x473A70` follow the
block's `next` link and identify a return to the chain root through its null
`previous` link. The effect loader `0x437EC0` reads the byte from the resource
and builds these links; the fighter loader follows the same observed pattern.

These observations apply to Japanese TH10.5 1.06a and retain the byte as an
unsigned byte rather than assuming the file only contains 0 or 1. The shared
name `suppress_wrap_signal_14` describes its observed role, not an original
source name. Rebuilt character and effect sequence methods, PAT group lifetime,
and effect loader matched their complete target extents. The fighter loader
remained nonexact with the same candidate bytes as before this naming change.
