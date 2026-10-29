# Selected-card display, JP1.06a

448B40 has complete439-byte source ownership, but remains nonexact440/439,
first difference+95 at448B9F. It receives no exact credit.

Native SHA256:d3105e9da72389275d687b46368b0c349f479923857b91dc177c295895e24a6c.
Whole source SHA256:c82f599f727ed3759fedc4f8c2f8052b566ed8942659acc37890f00fdfe18957.
The shorter formal compared-prefix hash is not the full candidate hash.

Exact category selector449E90 calls this helper at44A397. Native null handling,
record texture/description, color value and UI category policy establish
authored ownership. All three RET4 paths are retained; there is no exception
tail beyond448CF6.

The new source uses the actual SpellRecordView, a real eight-slot sprite
virtual interface established by CSprite RTTI, and the existing class-return
text-texture API. It replaces the old private raw access/manual-vtable model
without inventing object construction. No shared runtime header changed.

A null record disables objects17,5,6,12,13,14,15,16 in that order. A nonnull
record releases the previous text texture, conditionally binds optional card
texture+44, renders its description string into a220x256 text texture and binds
the text sprite with native anchors(-70,-26). Card image anchors are(-5,-5).
The shared globals6FA6C4/6FA6C0 provide the native image dimensions.

The low byte of record value1E becomes color3E0. Selector1 enables exactly the
matching color0..4 icon, hides category icons and number display, and resets
color to1. Other selectors show the number; selector2 chooses the second
category icon, otherwise the first; all five color icons are hidden.

The residual is unchanged from the historical probe: the compiler retains the
optional texture handle after testing it, while native reloads it after vtable
and dimension preparation. Typed virtual dispatch and the actual class return
do not resolve the optimization difference. The new whole candidate has302
unequal byte positions including length, not merely one. Do not repeat
pointer/DWORD spelling or artificial liveness/volatile controls.

Focused build:
scripts/repo-python scripts/build.py --unit exact-first-profile-deck-display --compare --json

Full raw disassembly, private complete-relocation comparison and formal receipt
are in build/frontier-profile-deck-display-20261029/. This is source selection
and positive ownership only. Existing accepted filter and update receipts are
unchanged; default CI validates the final ledgers and progress.
