# Actual CTile members in CSelect

The two native tiles at CSelect+350 and+2CD0 now use the already recovered
global CTile in both constructor/destructor-facing layouts. This removes
UiTileA4/CNumberTileLifetime storage for these members without changing their
A4 extent. The destructor-facing header no longer needs CNumberLifetime.hpp.
Other users of those legacy types are unchanged.

CSelect::render now calls the real nonvirtual CTile::render method directly;
its local SelectRenderTileView and TILE macro are removed. Constructor texture
calls bind to the real signed-argument CTile wrapper 4098B0, already canonical 37.
Actual inherited IColor identity is retained, with no manual vptr operations,
extra cleanup calls, forced inline/outline boundary or padding.

## Evidence and checks

Private ordinary-owner builds established unchanged constructor 4247/13,
destructor 845 exact and render 1497/163 before adoption. Final actual include
closure 9 units was replayed: all four accepted roots stage 890, flow 341,
binding 258 and destructor 845 remain exact. All eight bodies from the prior
owner audit retain byte-identical candidate hashes; constructor SHA remains
76c04f844fb8c2d9d30293de2e1831edc3eeb9ab2acc442138825ddf43e64d33.
Full constructor EH 461 and metadata 188 remain exact with actual CTile destructor
symbols. The implicit CSpriteEx gate adds Tile.hpp to its source pins and
passes unchanged validation rules.

The extended owner audit replays the complete global CTile RTTI graph from
the actual CSelect constructor object, including its four-slot table. It also
checks both exact ten-byte member vptr publications at 4232DD and 42348A,
writing 6C0718 to 350 and 2CD0 respectively. This proves the type is used in the
actual owner, not merely a separate copy probe. CSelect's own namespace RTTI
and full executable linkage remain outside this claim.

All four guarded render cases and 12 character cases rerun with their existing
negative controls. The render and character whole-body mismatches remain
explicit; no algorithm or exactness change is claimed. No global rebuild,
ledger change, new authored/source count or exact credit. Exact 1429/443911,
source 1636, authored 1655, mapped 1823, review 300, excluded 2072, units 812 stay.

All native work serial CPU 0/nice10, original pinned target, no IDA semantics or
push.
