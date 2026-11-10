# The collision-list sentinel is generated STL code

The 26-byte native entry at `0x435E50` is VC8 list-sentinel allocation, not
an authored game function. The previous handwritten CollisionList routine
reproduced the bytes but did not establish their owner. Remove its mistaken
authored source/exact credit and select the actual generated provider instead.

## Two independent typed owners

Fresh builds of the existing CDesignBase and CMenuReplay lifetimes emit the
complete `_Buynode()` member for `list<UiDesignObject*>` and `list<int>`. Both
providers match all 26 canonical bytes, including the actual scalar-new call.
Their exact native constructors independently establish the receiver and role:

- `0x421839` calls it while constructing CDesignBase+0x14. The result becomes
  list+4, and list+8 is cleared. The emitted typed call is at the same offset.
  This constructor is itself already classified as implicit compiler code.
- `0x446E6D` calls it while constructing CMenuReplay+0x274, followed by the
  same sentinel/count publication. Its emitted typed call also agrees.

All seven configured owner-lifetime comparisons remain exact. The public
`cross-v106a-collision-list-sentinel` unit now compiles the real replay-menu
source and selects its generated member, which independently replays 26/26.
The complete leaf ends at its only return; there is no EH or switch payload.

## Identical bytes do not identify a unique owner

A complete inventory comparison, relocating the actual scalar-new call rather
than masking it, finds two physical entries: `0x4040B0` and `0x435E50`. The
former was already classified from typed handle-manager and font constructors.
The latter is identified by the two exact typed owners above. The earlier
assumption that identical bytes made the collision-list entry authored was
wrong; it is corrected in the current knowledge and origin rules. No matching
threshold or uniqueness requirement was relaxed.

The existing origin-rule form pins this entry's whole-body SHA-256 and both
canonical owner calls. Both affected rules pass. Native body SHA-256:
`1d4ba0f8056546355caf2c4dca8f4b8a9532f281d4a7bc817dd6deab875d5ab6`.
The broader CollisionList receiver and its retained handwritten compatibility
source are unchanged; they are not used as evidence for this exclusion.

The original Japanese 1.06a target hash remains
`56350024879199861579c11b0e1c67b9590e10a8d40cd5996b109deec9afca7e`. Pending input
work and its source pins are preserved. This corrects local ownership and
accounting, with no new Factory acceptance.
