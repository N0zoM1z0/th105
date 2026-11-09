# One Title scene class across construction and lifetime

The scene factory, constructor, destructor, update, render and scene hooks now
use one `CTitle` declaration in `TitleScene.hpp`. The constructor-only class and
the factory's opaque 0x28C substitute are removed. The class contains the shared
sprite, tile, design and cursor types, with two four-byte texture-handle values.
Its previously undefined fourth virtual slot now has the native empty body.

## Native identity and member lifetime

The original primary table at `0x6C0CEC` has six slots: deleting destructor
`426060`, update `425990`, render `425740`, empty method `41F890`, entry `4256D0`
and exit `425720`. Its COL and full hierarchy establish CTitle over CSceneBase
and IScene, all at offset zero. The emitted class has those same virtual roles
and complete hierarchy geometry. Namespace-qualified source names, including
its class-spelled IScene, are retained; native type-name bytes are not presented
as identical.

The 0x28C allocation and constructor accesses establish handle cells +8/+A0,
sprites +0x0C/+0xA4, tile +0x138, design +0x1DC and cursor +0x210. The constructor
now initializes the actual cursor fields and calls the actual design provider.
The factory's named constructor call resolves to that same source class.

Both lifetime bodies require a consistent source model. The existing
DesignTextureHandle value type preserves the native member-initialization order;
release reads its `value` explicitly. In bounded controls, primitive handles
with member initializers kept the destructor exact but changed constructor
scheduling at +61. Implicit value conversion kept the constructor exact but
changed the destructor at +70. Explicit value extraction preserves both full
bodies. These controls do not establish unique original source spelling.

## Complete focused verification

The actual include closure of TitleScene.hpp is eight configured units. All nine
previously exact roots remain exact. The renderer remains the same nonexact
417-byte candidate, first differing at +232; its byte equality with its previous
candidate is checked, rather than inferred from equal length.

Owned extents include constructor 616 bytes, update 940 and factory 1064, with
all trailing switch data. The constructor's nine table targets and the factory's
21 table targets stay inside their callable bodies. The factory retains all
sixteen allocation-cleanup states. Complete EH for Title construction,
destruction, update, the factory and both design-member lifetimes matches all
1,105 code/metadata bytes. The design lifetimes and sprite/tile ownership proofs
also pass. The 30-byte Title deleting-wrapper origin gate is freshly replayed.
The one-byte empty slot is shared existing code, not a new authored function.

Keeping the class in its focused header avoids introducing STL library directives
and data into unrelated consumers of Title.hpp. That legacy header changes only
from the old class definition to a forward declaration. The update, renderer,
texture-loader and legacy design-helper controls preserve 24 non-debug COFF
sections and their relocations. The renderer drops only an unreferenced seven-byte
legacy forwarding helper; its complete callable remains unchanged.

Evidence is under `build/frontier-title-outer-owner-20261109/`, including the
formal unit reports, `member-verification.json`, `outer-verification.json`,
`unchanged-sections.json` and `scalar-origin.log`. Private controls are in the
matching `.analysis/` directory. Tracking, lightweight CI and the diff check pass.
No source pin, comparison rule, authored count or input migration change is made.
