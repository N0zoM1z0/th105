# Practice menu update hypothesis

The `CMenuPractice` RTTI vtable owns the complete 381-byte update at
`0x00445D90`. The raw boundary audit reaches all 125 instructions. The compiling
source hypothesis uses the established real owner and describes cursor movement,
settings publication, confirm/cancel handling and option colors. It remains
unselected in the source-presence ledger pending complete comparison.

The current pinned VC8 object emits a separate local `vector::size` helper,
while the target inlines those size checks. Strict comparison consequently
stops at an unbound local helper; no target address is invented and no complete
byte mismatch count, exact credit or runtime equivalence is claimed.
