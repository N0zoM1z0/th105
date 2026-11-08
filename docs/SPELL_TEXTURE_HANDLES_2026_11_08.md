# Spell record texture handles

The spell CSV loaders store texture handle values in each record: `+0x40` is
the shared composite-texture handle and `+0x44` is the optional card-texture
handle. The former is published to batched name rendering; the latter is used
by the spell-sequence and deck-preview sprites. The handles originate from the
title texture manager and are tracked separately for release.

These two fields now use unsigned 32-bit handle values rather than `void *`,
removing pointer/integer casts at their producers and consumers. The resource
parser, display callback, lookup, CSV wrappers, load selector, clear and
existing exact sequence peer remained exact under the pinned Japanese 1.06a
VC8 profile. The prepare, filtered parser, deck rendering/display and shuffle
candidates retained their prior nonexact hashes. In particular, the clearer
handle type did not resolve the optional-texture scheduling difference in
`0x45DC90`.
