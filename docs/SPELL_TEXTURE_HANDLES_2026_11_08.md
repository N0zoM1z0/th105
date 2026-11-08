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

The resource parser builds name-atlas rows in CSV order at 16-pixel intervals,
then assigns the resulting texture handle to the `batch_count` largest keys in
the destination map. Those are not necessarily the rows just read if keys are
out of order or repeated. Strictly increasing, unique new keys greater than
existing keys are sufficient for the two orders to agree; the actual resource
files' ordering has not been established here.

The filtered loader receives the owner's deque of short spell IDs, rather than
an unspecified mode pointer. Its selector and wrapper remain exact; the
filtered parser retains its prior nonexact candidate hash.
