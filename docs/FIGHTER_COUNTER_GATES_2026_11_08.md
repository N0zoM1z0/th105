# Fighter counter and pending gate

Fighter `+0x488` is a signed short accumulated by `0x45B300`. On reaching
4800 it triggers the counter-threshold notification, advances the associated
counter and resets the accumulator. `+0x48A` is a separate 16-bit pending gate:
`0x4776C0` writes it, and `0x45E3D0` transfers a nonzero value to the gate at
`+0x48C` after decrementing the existing gate, then clears the pending value.
The target leaves the two fields independent.

Both fields now belong to the shared Fighter layout. The setter, all three
continuity functions and the two outcome-path peers remained exact in complete
Japanese TH10.5 1.06a VC8 comparisons. The two affected source-backed origin
rules were individually revalidated after the shared header changed.
