# BG04 and BG02 constructors after the sprite-owner correction

BG04 constructor468570 is canonical exact335/335:
7e8e894512a29ffb68aa59284c75ffc38db49b31516f10e808462da6ed1a6b73.
BG02 constructor467F90 has complete selected924-byte source but remains
nonexact; its77 differing byte positions receive no exact credit.

## Ownership and boundaries

The independent0xE8 CEffectSprite correction is documented in
EFFECT_SPRITE_OWNER_2026_10_29.md. Both constructors use vector assign rather
than resize, with that actual sprite type. Existing RTTI/vtables6C3360/6C33D4
and exact factory467380 identify the0x68 BG02/BG04 owners. The factory calls
BG02 at467423 and BG04 at46747B. All normal paths through each bounded root
were decoded; the full lengths are924 and335, not selected prefixes.

BG04 initializes common stage4 tiles, assigns one secondary handle/sprite,
loads data/background/BG04/cloud2.bmp, installs a640x192 region with320/80
pivot, and clears state64. The fill's lifetime ends before texture loading.
The same real handle output is used for the initial zero fill and loader.
The scoped dimensions contain two actual loader outputs, height then width;
no unused pad member or forced alignment is added. Their original source
aggregate spelling remains unknown. Ordinary separate scalar locals produce
another stack coloring; the paired output object preserves the native offsets.
The old vptr mismatch disappears through the real class type, not an alias.
The shared SpriteTextureSetupView ABI is used unchanged.

BG02 initializes common stage2 tiles, assigns48 secondary slots, and loads16
frames of left/a, center/b, and right/c textures. It preserves each checked
handle/sprite access and uses the actual returned width/height without adding
null guards absent from the target. The path buffer belongs to the loop body,
allowing the earlier sprite-fill storage to be reused. Keeping it in the
outer scope incorrectly produced a214-byte frame rather than12C. Directly
reading the returned handle value preserves target left-hand checked-address
evaluation before loading the texture; an implicit class conversion instead
reordered those operations and shortened the body.

Selected BG02 has298/298 decoded instructions and all924 bytes present.
The first difference is+383 at46810F: native reloads the handle into EBP after
the two bounds checks, while the candidate uses EDX and changes nearby
argument/address scheduling. Similar scheduling differences recur in the other
two texture lanes. Full selected hash:
3403fad6ea0b16013974840bd90cb4ee540e0be4958d2951f90e4e7eb53f8eec.
Target hash:
b2d2eb2748fc07c5f07ad07d36d95e7924eb8270cbc8a4f4d65268297e275ce8.
Named handle-reference and shared texture-interface controls were byte-neutral.
No register annotation, padding, copied bytes or fake barrier is introduced.

## Focused receipts

scripts/repo-python scripts/build.py --unit exact-first-bg04-constructor --compare --json
scripts/repo-python scripts/build.py --unit exact-first-bg02-constructor --compare --json
scripts/repo-python scripts/build.py --unit cross-v106a-battle-object-dispatch --compare --json

Reports are under build/frontier-background-constructors-20261029/. BG04 and
its existing986-byte factory pass; BG02 is explicitly a mismatch. Shared
headers are unchanged in this batch, so the preceding321-function affected
replay remains the incremental baseline. Only335 authored bytes are added.
